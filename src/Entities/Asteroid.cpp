#include "Entities/Asteroid.hpp"
#include <iostream>

Asteroid::Asteroid(const sf::Vector2f& position, const sf::Vector2f& direction)
    : m_Direction(direction),
      m_Speed(250.f)
{
    m_Shape.setRadius(40.f);
    m_Shape.setPointCount(8);
    m_Shape.setFillColor(sf::Color(120, 120, 120));
    m_Shape.setOrigin({40.f, 40.f});
    m_Shape.setPosition(position);
}

void Asteroid::Update(float deltaTime)
{
    m_Shape.move(m_Direction * m_Speed * deltaTime);
}


void Asteroid::Render(sf::RenderWindow& window)
{
    window.draw(m_Shape);
}


sf::Vector2f Asteroid::GetPosition() const
{
    return m_Shape.getPosition();
}


float Asteroid::GetRadius() const
{
    return m_Shape.getRadius();
}

void Asteroid::OnCollision(Entity* other)
{
    Destroy();
}

EntityType Asteroid::GetType() const
{
    return EntityType::Asteroid;
}