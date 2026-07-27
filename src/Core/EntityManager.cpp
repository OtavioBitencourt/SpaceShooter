#include "Core/EntityManager.hpp"
#include "Utils/Math.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/EntityType.hpp"

#include <algorithm>
#include <iostream>



void EntityManager::SpawnBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    m_PendingEntities.push_back(std::make_unique<Bullet>(position, direction));
}



void EntityManager::SpawnAsteroid(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    m_PendingEntities.push_back(std::make_unique<Asteroid>(position, direction));
}


void EntityManager::Update(float deltaTime)
{

    for(auto& entity : m_Entities)
    {
        entity->Update(deltaTime);
    }

    CheckOutOfBounds();
    CheckCollisions();
    MergePendingEntities();
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

            if (!CanCollide(entityA, entityB))
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

    for (const auto& entity : m_Entities)
    {
        if (!entity->IsPendingDestroy())
        {
            continue;
        }


        if (entity.get() == m_Player && entity->IsPendingDestroy())
        {
            m_Player = nullptr;
        }


        if(m_OnEntityDestroyed)
        {
            m_OnEntityDestroyed(entity->GetType());
        }
    }

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


void EntityManager::SpawnEnemy(const sf::Vector2f& position)
{
    m_PendingEntities.push_back(std::make_unique<Enemy>(position));
}

void EntityManager::SpawnPlayer()
{
    auto player = std::make_unique<Player>(this);
    m_Player = player.get();
    m_PendingEntities.push_back(std::move(player));

}


Player* EntityManager::GetPlayer() const
{
    return m_Player;
}


void EntityManager::MergePendingEntities()
{
    for (auto& entity : m_PendingEntities)
    {
        m_Entities.push_back(std::move(entity));
    }

    m_PendingEntities.clear();
}

bool EntityManager::CanCollide(Entity* entityA, Entity* entityB) const
{
    EntityType typeA = entityA->GetType();
    EntityType typeB = entityB->GetType();

    if(typeA == EntityType::Bullet && typeB == EntityType::Player)
    {
        return false;
    }

    if(typeA == EntityType::Player && typeB == EntityType::Bullet)
    {
        return false;
    }

    return true;
}




bool EntityManager::ShouldDestroyOutOfBounds(Entity* entity) const
{
    switch (entity->GetType())
    {
        case EntityType::Bullet:
        case EntityType::Asteroid:
        case EntityType::Enemy:
            return true;
        
        case EntityType::Player:
            return false;
    }

    return false;
}


void EntityManager::CheckOutOfBounds()
{
    constexpr float minX = -150.f;
    constexpr float maxX = 1430.f;
    constexpr float minY = -150.f;
    constexpr float maxY = 870.f;

    for (auto& entity : m_Entities)
    {
        if (!ShouldDestroyOutOfBounds(entity.get()))
        {
            continue;
        }

        sf::Vector2f position = entity->GetPosition();

        if (position.x < minX || 
            position.x > maxX ||
            position.y < minY ||
            position.y > maxY)
        {
            entity->Destroy();
        }
    }

}


void EntityManager::SetOnEntityDestroyedCallback(std::function<void(EntityType)> callback)
{
    m_OnEntityDestroyed = std::move(callback);
}