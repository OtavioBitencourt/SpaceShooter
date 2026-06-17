#include "Entities/Entity.hpp"


void Entity::Destroy()
{
    m_IsPendingDestroy = true;
}

bool Entity::IsPendingDestroy() const 
{
    return m_IsPendingDestroy;
}

void Entity::OnCollision(Entity* other)
{
    
}

sf::Vector2f Entity::GetPosition() const
{
    return sf::Vector2f();
}

float Entity::GetRadius() const
{
    return 0.f;
}