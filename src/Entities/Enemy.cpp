#include "Entities/Enemy.hpp"
#include "Utils/Math.hpp"

#include <iostream>


//============================================================
// Enemy
// -----------------------------------------------------------
// Implementação responsável pelo comportamento dos inimigos,
// incluindo:
//
// - Movimento em direção ao Player.
// - Renderização.
// - Gerenciamento de vida.
// - Recebimento de dano.
// - Reação a colisões.
//============================================================


//------------------------------------------------------------
// Construtor
//------------------------------------------------------------

Enemy::Enemy(const sf::Vector2f& position)
    : m_Speed(150.f),
      m_Health(100)
{
    // Define o raio utilizado para representar o inimigo.
    m_Shape.setRadius(20.f);

    // Ajusta a origem da forma para facilitar seu posicionamento.
    m_Shape.setOrigin({25.f, 25.f});

    // Define a cor utilizada para representar o inimigo.
    m_Shape.setFillColor(sf::Color::Red);

    // Posiciona o inimigo no ponto recebido pelo construtor.
    m_Shape.setPosition(position);
}


//------------------------------------------------------------
// Update
//------------------------------------------------------------

void Enemy::Update(float deltaTime)
{
    // Obtém a posição atual do inimigo.
    sf::Vector2f currentPosition =
        m_Shape.getPosition();


    // Move o inimigo gradualmente em direção ao alvo.
    //
    // A função MoveTowards calcula a direção até o alvo e
    // aplica a velocidade considerando o tempo transcorrido.
    m_Shape.setPosition(
        Math::MoveTowards(
            currentPosition,
            m_TargetPosition,
            m_Speed,
            deltaTime));
}


//------------------------------------------------------------
// SetTargetPosition
//------------------------------------------------------------

void Enemy::SetTargetPosition(
    const sf::Vector2f& targetPosition)
{
    // Armazena a posição que será utilizada como alvo
    // durante a atualização do inimigo.
    m_TargetPosition = targetPosition;
}


//------------------------------------------------------------
// Render
//------------------------------------------------------------

void Enemy::Render(sf::RenderWindow& window)
{
    // Desenha a representação visual do inimigo.
    window.draw(m_Shape);
}


//------------------------------------------------------------
// TakeDamage
//------------------------------------------------------------

void Enemy::TakeDamage(int amount)
{
    // Reduz a vida do inimigo de acordo com o dano recebido.
    m_Health -= amount;


    // Quando a vida chega a zero ou abaixo disso,
    // o inimigo é marcado para destruição.
    //
    // A remoção física será realizada posteriormente pelo
    // EntityManager.
    if (m_Health <= 0)
    {
        Destroy();
    }
}


//------------------------------------------------------------
// GetPosition
//------------------------------------------------------------

sf::Vector2f Enemy::GetPosition() const
{
    // Retorna a posição atual do inimigo.
    return m_Shape.getPosition();
}


//------------------------------------------------------------
// GetRadius
//------------------------------------------------------------

float Enemy::GetRadius() const
{
    // Retorna o raio utilizado pelo sistema de colisões.
    return m_Shape.getRadius();
}


//------------------------------------------------------------
// GetType
//------------------------------------------------------------

EntityType Enemy::GetType() const
{
    // Retorna o tipo utilizado pelo EntityManager para
    // identificar esta entidade como Enemy.
    return EntityType::Enemy;
}


//------------------------------------------------------------
// OnCollision
//------------------------------------------------------------

void Enemy::OnCollision(Entity* other)
{
    // Tenta interpretar a entidade atingida como uma entidade
    // que pode receber dano.
    //
    // O dynamic_cast garante que o ponteiro só será convertido
    // quando o objeto realmente implementar IDamageable.
    IDamageable* damageable =
        dynamic_cast<IDamageable*>(other);


    // Atualmente, o Enemy causa dano apenas quando colide
    // diretamente com o Player.
    if (damageable != nullptr &&
        other->GetType() == EntityType::Player)
    {
        // Mensagem de depuração para acompanhar o dano
        // aplicado ao Player durante o desenvolvimento.
        std::cout
            << "Aplicando dano ao Player"
            << std::endl;


        // Aplica 25 pontos de dano ao Player.
        damageable->TakeDamage(25);


        // Após atingir o Player, o Enemy é destruído.
        Destroy();
    }
}