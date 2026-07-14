#include "Entities/Player.hpp"
#include "Utils/Math.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Core/EntityManager.hpp"

Player::Player(EntityManager* entityManager)
    : m_Speed(400.f),
      m_Health(100),
      m_ShootCooldown(0.1f),
      m_CurrentShootCooldown(0.f),
      m_EntityManager(entityManager)
{
    
    m_Shape.setPointCount(3);
    m_Shape.setRadius(30.f);

    m_Shape.setFillColor(sf::Color::Cyan);
    m_Shape.setOrigin({30.f, 30.f}); 
    m_Shape.setPosition({640.f, 360.f});

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    m_Forward = sf::Vector2f(0.f, -1.f);
}


void Player::Update(float deltaTime)
{
    sf::Vector2f currentPosition = m_Shape.getPosition();
    sf::Vector2f direction = m_TargetPosition - currentPosition;

    float distance = Math::Length(direction); 

    if (distance > 5.f)
    {
        direction = Math::Normalize(direction); 

        m_Forward = direction; 

        m_Shape.move(direction * m_Speed * deltaTime);


        float angle = std::atan2(direction.y, direction.x);
        float angleDegress = angle * 180.f / 3.14159265f;
        m_Shape.setRotation(sf::degrees(angleDegress + 90.f));
    }



    m_CurrentShootCooldown -= deltaTime;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_CurrentShootCooldown <= 0.f)
    {

        m_EntityManager->SpawnBullet( m_Shape.getPosition(), m_Forward);

        m_CurrentShootCooldown = m_ShootCooldown;
    }

}


void Player::Render(sf::RenderWindow& window)
{
    window.draw(m_Shape);
    
}


EntityType Player::GetType() const
{
    return EntityType::Player;
}


sf::Vector2f Player::GetPosition() const
{
    return m_Shape.getPosition();
}



float Player::GetRadius() const
{
    return m_Shape.getRadius();
}


void Player::TakeDamage(int amount)
{
    m_Health -= amount;

    std::cout << "Player HP: " << m_Health << std::endl;

    if (m_Health <= 0)
    {
        Destroy();
    }
}

void Player::SetTargetPosition(const sf::Vector2f& position)
{
    m_TargetPosition = position;
}