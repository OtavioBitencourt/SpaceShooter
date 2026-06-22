#include "Entities/Bullet.hpp"
#include "Entities/IDamageable.hpp"
#include "Entities/EntityType.hpp"
#include <iostream>

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& direction) 
: m_Direction(direction), m_Speed(1000.f)
{
    m_Shape.setRadius(5.f);
    m_Shape.setFillColor(sf::Color::Red);
    m_Shape.setOrigin({5.f, 5.f});
    m_Shape.setPosition(position);
}

void Bullet::Update(float deltaTime)
{
    m_Shape.move(m_Direction * m_Speed * deltaTime);
}


void Bullet::Render(sf::RenderWindow& window)
{
    window.draw(m_Shape);
}


sf::Vector2f Bullet::GetPosition() const
{
    return m_Shape.getPosition();
}



float Bullet::GetRadius() const
{
    return m_Shape.getRadius();
}



void Bullet::OnCollision(Entity* other)
{
    if (other->GetType() == EntityType::Asteroid)
    {
        other->Destroy();
    }

    IDamageable* damageable = 
        dynamic_cast<IDamageable*>(other);
    
    if(damageable != nullptr)
    {
        damageable->TakeDamage(25);
    }

    Destroy();
}

EntityType Bullet::GetType() const
{
    return EntityType::Bullet;
}