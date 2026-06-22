#include "Core/EntityManager.hpp"
#include "Utils/Math.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/EntityType.hpp"

#include <algorithm>
#include <iostream>


void EntityManager::SpawnBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    m_Entities.push_back(std::make_unique<Bullet>(position, direction));
}

void EntityManager::SpawnAsteroid(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    m_Entities.push_back(std::make_unique<Asteroid>(position, direction));
}

void EntityManager::Update(float deltaTime)
{
    // for (Bullet& bullet : m_Bullets)
    // {
    //     bullet.Update(deltaTime);
    // }

    // for (Asteroid& asteroid : m_Asteroids)
    // {
    //     asteroid.Update(deltaTime);
    // }

    for(auto& entity : m_Entities)
    {
        entity->Update(deltaTime);
    }

    CheckCollisions();
    CleanupDestroyedEntities();
}

void EntityManager::Render(sf::RenderWindow& window)
{
    // for (Bullet& bullet : m_Bullets)
    // {
    //     bullet.Render(window);
    // }

    // for (Asteroid& asteroid : m_Asteroids)
    // {
    //     asteroid.Render(window);
    // }

    for(auto& entity : m_Entities)
    {
        entity->Render(window);
    }
    
}

void EntityManager::CheckCollisions()
{
    for(size_t i = 0; i < m_Entities.size(); i++)
    {
        Entity* entityA = m_Entities[i].get();

        if(entityA->IsPendingDestroy())
        {
            continue;
        }

        for(size_t j = i + 1; j < m_Entities.size(); j++)
        {
            Entity* entityB = m_Entities[j].get();

            if(entityB->IsPendingDestroy())
            {
                continue;
            }

            float distance = Math::Distance(entityA->GetPosition(), entityB->GetPosition());
            float radiusSum = entityA->GetRadius() + entityB->GetRadius();

            if (distance < radiusSum)
            {
                entityA->OnCollision(entityB);
                entityB->OnCollision(entityA);
            }
        }
    }
    
}


void EntityManager::CleanupDestroyedEntities()
{
    m_Entities.erase(
        std::remove_if(m_Entities.begin(), m_Entities.end(), 
        [](const std::unique_ptr<Entity>& entity)
         {
            return entity->IsPendingDestroy();
         }), 
        m_Entities.end());
}


void EntityManager::SetEnemiesTargetPosition(const sf::Vector2f& targetPosition)
{
    for (auto& entity : m_Entities)
    {
        if (entity->GetType() == EntityType::Enemy)
        {
            Enemy* enemy = static_cast<Enemy*>(entity.get());
            enemy->SetTargetPosition(targetPosition);
        }
    }
}