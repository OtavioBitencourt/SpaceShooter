#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "Entities/Asteroid.hpp"
#include "Entities/Bullet.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"

//============================================================
// EntityManager
// -----------------------------------------------------------
// Responsável por gerenciar o ciclo de vida das entidades
// existentes no jogo.
//
// Responsabilidades:
// - Criar e armazenar entidades.
// - Atualizar as entidades a cada frame.
// - Renderizar as entidades.
// - Gerenciar o Player.
// - Detectar e processar colisões.
// - Identificar entidades fora dos limites do mundo.
// - Remover entidades marcadas para destruição.
// - Adiar a inserção de novas entidades quando necessário.
// - Notificar outros sistemas quando uma entidade é destruída.
//
// As entidades são armazenadas de forma polimórfica utilizando
// std::unique_ptr<Entity>, permitindo que diferentes tipos de
// entidades compartilhem o mesmo armazenamento.
//
// Não é responsabilidade desta classe:
// - Controlar a pontuação diretamente.
// - Controlar a interface do usuário.
// - Controlar a progressão das Waves.
//============================================================

class EntityManager
{
public:

    // Atualiza todas as entidades e executa as etapas necessárias
    // do ciclo de vida, incluindo colisões e limpeza.
    void Update(float deltaTime);

    // Renderiza todas as entidades ativas na janela especificada.
    void Render(sf::RenderWindow& window);


    // Cria um projétil na posição e direção informadas.
    void SpawnBullet(
        const sf::Vector2f& position,
        const sf::Vector2f& direction);

    // Cria um asteroide na posição e direção informadas.
    void SpawnAsteroid(
        const sf::Vector2f& position,
        const sf::Vector2f& direction);


    // Função genérica utilizada para criar entidades de diferentes
    // tipos através de seus construtores.
    template<typename T, typename... Args>
    void SpawnEntity(Args&&... args);

    // Cria um inimigo na posição especificada.
    void SpawnEnemy(const sf::Vector2f& position);

    // Atualiza a posição-alvo utilizada pelos inimigos para
    // acompanhar o Player.
    void SetEnemiesTargetPosition(
        const sf::Vector2f& targetPosition);


    // Cria e registra o Player no EntityManager.
    void SpawnPlayer();

    // Retorna o Player atualmente gerenciado.
    Player* GetPlayer() const;


    // Remove as entidades marcadas para destruição e executa
    // as notificações de destruição configuradas.
    void CleanupDestroyedEntities();

    // Registra uma função que será chamada quando uma entidade
    // for destruída.
    //
    // O EntityType da entidade destruída é informado ao callback,
    // permitindo que outros sistemas reajam ao evento sem que o
    // EntityManager precise conhecer suas implementações.
    void SetOnEntityDestroyedCallback(
        std::function<void(EntityType)> callback);

    // Retorna a quantidade atual de inimigos ativos no jogo.
    int GetEnemyCount() const;


private:

    // Armazena as entidades atualmente ativas no jogo.
    std::vector<std::unique_ptr<Entity>> m_Entities;

    // Armazena temporariamente entidades que aguardam inserção
    // no vetor principal.
    //
    // Essa fila permite adiar a inserção de novas entidades para
    // evitar modificações inseguras durante a atualização da
    // coleção principal.
    std::vector<std::unique_ptr<Entity>> m_PendingEntities;


    // Verifica possíveis colisões entre as entidades ativas.
    void CheckCollisions();

    // Verifica quais entidades devem ser destruídas por terem
    // ultrapassado os limites definidos do mundo.
    void CheckOutOfBounds();


    // Determina se dois tipos de entidades podem colidir.
    bool CanCollide(
        Entity* entityA,
        Entity* entityB) const;

    // Determina se uma entidade deve ser destruída ao sair
    // dos limites do mundo.
    bool ShouldDestroyOutOfBounds(Entity* entity) const;


    // Transfere as entidades pendentes para o armazenamento
    // principal em um momento seguro do ciclo de atualização.
    void MergePendingEntities();


    // Ponteiro para o Player atualmente gerenciado.
    //
    // O EntityManager mantém essa referência para permitir acesso
    // rápido ao Player sem precisar procurá-lo entre as entidades.
    Player* m_Player = nullptr;

    // Callback executado quando uma entidade é removida.
    //
    // Permite que sistemas externos reajam à destruição de uma
    // entidade sem criar uma dependência direta entre eles.
    std::function<void(EntityType)> m_OnEntityDestroyed;
};


// Cria uma entidade do tipo T utilizando os argumentos fornecidos
// e adiciona a entidade ao armazenamento principal.
template<typename T, typename... Args>
void EntityManager::SpawnEntity(Args&&... args)
{
    m_Entities.push_back(
        std::make_unique<T>(
            std::forward<Args>(args)...));
}