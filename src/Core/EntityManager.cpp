#include "Core/EntityManager.hpp"
#include "Utils/Math.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/EntityType.hpp"

#include <algorithm>
#include <memory>


//============================================================
// EntityManager
// -----------------------------------------------------------
// Implementação responsável pelo gerenciamento do ciclo de vida
// das entidades do jogo.
//
// O EntityManager centraliza:
// - atualização;
// - renderização;
// - colisões;
// - spawn;
// - remoção;
// - controle do Player;
// - tratamento de entidades fora dos limites;
// - notificações de destruição.
//============================================================


//------------------------------------------------------------
// SpawnBullet
//------------------------------------------------------------

void EntityManager::SpawnBullet(
    const sf::Vector2f& position,
    const sf::Vector2f& direction)
{
    // A Bullet é adicionada à lista de entidades pendentes.
    //
    // A inserção não ocorre diretamente em m_Entities porque
    // novas entidades podem ser criadas durante a atualização
    // do vetor principal. A inserção imediata poderia invalidar
    // iteradores e interferir no processamento do frame atual.
    m_PendingEntities.push_back(
        std::make_unique<Bullet>(
            position,
            direction));
}


//------------------------------------------------------------
// SpawnAsteroid
//------------------------------------------------------------

void EntityManager::SpawnAsteroid(
    const sf::Vector2f& position,
    const sf::Vector2f& direction)
{
    // Assim como as demais entidades criadas durante o frame,
    // o asteroide aguarda até a etapa de merge para entrar no
    // armazenamento principal.
    m_PendingEntities.push_back(
        std::make_unique<Asteroid>(
            position,
            direction));
}


//------------------------------------------------------------
// Update
//------------------------------------------------------------

void EntityManager::Update(float deltaTime)
{
    // Atualiza primeiro todas as entidades atualmente ativas.
    for (auto& entity : m_Entities)
    {
        entity->Update(deltaTime);
    }


    // Verifica entidades que ultrapassaram os limites do mundo.
    CheckOutOfBounds();


    // Processa as colisões entre as entidades ativas.
    CheckCollisions();


    // Adiciona ao armazenamento principal as entidades que foram
    // criadas durante o frame.
    MergePendingEntities();


    // Remove as entidades marcadas para destruição.
    CleanupDestroyedEntities();
}


//------------------------------------------------------------
// Render
//------------------------------------------------------------

void EntityManager::Render(sf::RenderWindow& window)
{
    // Todas as entidades utilizam a interface comum Entity,
    // permitindo que diferentes tipos sejam renderizados através
    // do mesmo armazenamento polimórfico.
    for (auto& entity : m_Entities)
    {
        entity->Render(window);
    }
}


//------------------------------------------------------------
// CheckCollisions
//------------------------------------------------------------

void EntityManager::CheckCollisions()
{
    // Percorre as entidades utilizando dois índices para verificar
    // cada par possível apenas uma vez.
    //
    // Dessa forma:
    //
    // A x B
    //
    // é verificado, mas B x A não é processado novamente.
    for (std::size_t i = 0;
         i < m_Entities.size();
         ++i)
    {
        Entity* entityA = m_Entities[i].get();


        // Entidades já marcadas para destruição não participam
        // de novas verificações de colisão.
        if (entityA->IsPendingDestroy())
        {
            continue;
        }


        // Começa em i + 1 para evitar verificar novamente os
        // mesmos pares de entidades.
        for (std::size_t j = i + 1;
             j < m_Entities.size();
             ++j)
        {
            Entity* entityB = m_Entities[j].get();


            if (entityB->IsPendingDestroy())
            {
                continue;
            }


            // Algumas combinações de entidades não devem gerar
            // colisões. Essa regra é centralizada em CanCollide().
            if (!CanCollide(entityA, entityB))
            {
                continue;
            }


            // Calcula a distância entre os centros das entidades.
            float distance = Math::Distance(
                entityA->GetPosition(),
                entityB->GetPosition());


            // Soma dos raios utilizada para determinar a
            // sobreposição entre as entidades.
            float radiusSum =
                entityA->GetRadius() +
                entityB->GetRadius();


            // Existe colisão quando a distância entre os centros
            // é menor que a soma dos raios.
            if (distance < radiusSum)
            {
                // Cada entidade recebe a informação da colisão.
                //
                // O comportamento resultante depende da implementação
                // de OnCollision() de cada entidade.
                entityA->OnCollision(entityB);
                entityB->OnCollision(entityA);
            }
        }
    }
}


//------------------------------------------------------------
// CleanupDestroyedEntities
//------------------------------------------------------------

void EntityManager::CleanupDestroyedEntities()
{
    // Antes de remover fisicamente as entidades, percorremos
    // aquelas marcadas para destruição para realizar qualquer
    // tratamento necessário.
    for (const auto& entity : m_Entities)
    {
        if (!entity->IsPendingDestroy())
        {
            continue;
        }


        // Se o Player foi destruído, o ponteiro mantido pelo
        // EntityManager também precisa ser invalidado.
        if (entity.get() == m_Player)
        {
            m_Player = nullptr;
        }


        // Notifica sistemas externos sobre a destruição da entidade.
        //
        // O EntityManager não precisa conhecer o que será feito
        // com essa informação. No momento, o Game utiliza esse
        // callback para atualizar a pontuação.
        if (m_OnEntityDestroyed)
        {
            m_OnEntityDestroyed(entity->GetType());
        }
    }


    // Remove efetivamente da coleção todas as entidades que foram
    // marcadas para destruição.
    //
    // A remoção ocorre somente depois que as notificações foram
    // processadas, garantindo que ainda tenhamos acesso às
    // informações das entidades removidas.
    m_Entities.erase(
        std::remove_if(
            m_Entities.begin(),
            m_Entities.end(),
            [](const std::unique_ptr<Entity>& entity)
            {
                return entity->IsPendingDestroy();
            }),
        m_Entities.end());
}


//------------------------------------------------------------
// SetEnemiesTargetPosition
//------------------------------------------------------------

void EntityManager::SetEnemiesTargetPosition(
    const sf::Vector2f& targetPosition)
{
    // Procura apenas entidades do tipo Enemy.
    for (auto& entity : m_Entities)
    {
        if (entity->GetType() == EntityType::Enemy)
        {
            // Neste ponto sabemos que a entidade é um Enemy,
            // portanto podemos acessar seu comportamento específico.
            Enemy* enemy =
                static_cast<Enemy*>(entity.get());

            enemy->SetTargetPosition(targetPosition);
        }
    }
}


//------------------------------------------------------------
// SpawnEnemy
//------------------------------------------------------------

void EntityManager::SpawnEnemy(
    const sf::Vector2f& position)
{
    // O inimigo aguarda na fila de entidades pendentes para ser
    // inserido no armazenamento principal posteriormente.
    m_PendingEntities.push_back(
        std::make_unique<Enemy>(
            position));
}


//------------------------------------------------------------
// SpawnPlayer
//------------------------------------------------------------

void EntityManager::SpawnPlayer()
{
    // O Player precisa ser criado dinamicamente porque o
    // EntityManager mantém um ponteiro para acessá-lo diretamente.
    auto player = std::make_unique<Player>(this);

    // Guarda o endereço do Player antes de transferir sua posse
    // para a lista de entidades pendentes.
    m_Player = player.get();


    // Transfere a propriedade para a coleção de entidades pendentes.
    m_PendingEntities.push_back(
        std::move(player));
}


//------------------------------------------------------------
// GetPlayer
//------------------------------------------------------------

Player* EntityManager::GetPlayer() const
{
    return m_Player;
}


//------------------------------------------------------------
// MergePendingEntities
//------------------------------------------------------------

void EntityManager::MergePendingEntities()
{
    // Move todas as entidades criadas durante o frame para o
    // armazenamento principal.
    //
    // std::move transfere a propriedade dos unique_ptrs sem
    // realizar uma cópia dos objetos.
    for (auto& entity : m_PendingEntities)
    {
        m_Entities.push_back(
            std::move(entity));
    }


    // A coleção de entidades pendentes pode ser reutilizada
    // no próximo frame.
    m_PendingEntities.clear();
}


//------------------------------------------------------------
// CanCollide
//------------------------------------------------------------

bool EntityManager::CanCollide(
    Entity* entityA,
    Entity* entityB) const
{
    EntityType typeA = entityA->GetType();
    EntityType typeB = entityB->GetType();


    // O projétil do jogador não deve atingir o próprio Player.
    if (typeA == EntityType::Bullet &&
        typeB == EntityType::Player)
    {
        return false;
    }


    // A verificação inversa é necessária porque os tipos podem
    // aparecer em qualquer ordem durante a análise dos pares.
    if (typeA == EntityType::Player &&
        typeB == EntityType::Bullet)
    {
        return false;
    }


    // Todas as demais combinações são consideradas válidas
    // pelo sistema atual.
    return true;
}


//------------------------------------------------------------
// ShouldDestroyOutOfBounds
//------------------------------------------------------------

bool EntityManager::ShouldDestroyOutOfBounds(
    Entity* entity) const
{
    // Define quais tipos de entidade podem ser removidos
    // automaticamente quando saem dos limites do mundo.
    switch (entity->GetType())
    {
        case EntityType::Bullet:
        case EntityType::Asteroid:
        case EntityType::Enemy:
            return true;

        case EntityType::Player:
            return false;
    }


    // Retorno de segurança para tipos não tratados.
    return false;
}


//------------------------------------------------------------
// CheckOutOfBounds
//------------------------------------------------------------

void EntityManager::CheckOutOfBounds()
{
    // Define uma margem além da área visível da janela.
    //
    // A margem permite que entidades criadas fora da tela tenham
    // tempo para entrar na área visível antes de serem removidas.
    constexpr float minX = -150.f;
    constexpr float maxX = 1430.f;
    constexpr float minY = -150.f;
    constexpr float maxY = 870.f;


    for (auto& entity : m_Entities)
    {
        // Algumas entidades, como o Player, não devem ser
        // destruídas apenas por sair dos limites do mundo.
        if (!ShouldDestroyOutOfBounds(entity.get()))
        {
            continue;
        }


        sf::Vector2f position =
            entity->GetPosition();


        // Se a entidade ultrapassou qualquer um dos limites,
        // ela é marcada para destruição.
        //
        // A remoção física será realizada posteriormente por
        // CleanupDestroyedEntities().
        if (position.x < minX ||
            position.x > maxX ||
            position.y < minY ||
            position.y > maxY)
        {
            entity->Destroy();
        }
    }
}


//------------------------------------------------------------
// SetOnEntityDestroyedCallback
//------------------------------------------------------------

void EntityManager::SetOnEntityDestroyedCallback(
    std::function<void(EntityType)> callback)
{
    // Armazena a função que será executada quando uma entidade
    // for destruída.
    //
    // std::move transfere o objeto função para o membro da classe
    // sem criar uma cópia desnecessária.
    m_OnEntityDestroyed = std::move(callback);
}


//------------------------------------------------------------
// GetEntityCount
//------------------------------------------------------------

int EntityManager::GetEntityCount() const
{
    int count = 0;


    // Atualmente, apesar do nome genérico do método,
    // a função conta especificamente entidades do tipo Enemy.
    for (const auto& entity : m_Entities)
    {
        if (entity->GetType() == EntityType::Enemy)
        {
            count++;
        }
    }


    return count;
}