#include "Entities/Entity.hpp"

void Entity::Update(float deltaTime)
{

}

void Entity::Render(sf::RenderWindow& window)
{
    
}

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

void Entity::Destroy()
{
    m_IsPendingDestroy = true;
}

bool Entity::IsPendingDestroy() const
{
    return m_IsPendingDestroy;
}

