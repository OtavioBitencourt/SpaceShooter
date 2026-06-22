#include "Entities/Enemy.hpp"
#include "Utils/Math.hpp"

Enemy::Enemy(const sf::Vector2f& position)
   : m_Speed(150.f)
   , m_Health(100)
{
    m_Shape.setRadius(20.f);
    m_Shape.setOrigin({25.f, 25.f});
    m_Shape.setFillColor(sf::Color::Red);
    m_Shape.setPosition(position);
}

void Enemy::Update(float deltaTime)
{
    sf::Vector2f currentPosition = m_Shape.getPosition();

    m_Shape.setPosition(Math::MoveTowards(currentPosition, m_TargetPosition, m_Speed, deltaTime));
}



void Enemy::SetTargetPosition(const sf::Vector2f& targetPosition)
{
    m_TargetPosition = targetPosition;
}



void Enemy::Render(sf::RenderWindow& window)
{
    window.draw(m_Shape);
}


void Enemy::TakeDamage(int amount)
{
    m_Health -= amount;

    if(m_Health <= 0)
    {
        Destroy();
    }
}



sf::Vector2f Enemy::GetPosition() const
{
    return m_Shape.getPosition();
}



float Enemy::GetRadius() const
{
    return m_Shape.getRadius();
}

EntityType Enemy::GetType() const
{
    return EntityType::Enemy;
}