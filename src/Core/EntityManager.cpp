#include "Core/EntityManager.hpp"
#include "Utils/Math.hpp"
#include <algorithm>

void EntityManager::SpawnBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    m_Bullets.emplace_back(position, direction);
}

void EntityManager::SpawnAsteroid(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    m_Asteroids.emplace_back(position, direction);
}

void EntityManager::Update(float deltaTime)
{
    for (Bullet& bullet : m_Bullets)
    {
        bullet.Update(deltaTime);
    }

    for (Asteroid& asteroid : m_Asteroids)
    {
        asteroid.Update(deltaTime);
    }

    CheckCollisions();
}

void EntityManager::Render(sf::RenderWindow& window)
{
    for (Bullet& bullet : m_Bullets)
    {
        bullet.Render(window);
    }

    for (Asteroid& asteroid : m_Asteroids)
    {
        asteroid.Render(window);
    }
    
}

void EntityManager::CheckCollisions()
{
    for(size_t bulletIndex = 0; bulletIndex < m_Bullets.size(); bulletIndex++)
    {
        Bullet& bullet = m_Bullets[bulletIndex];
        
        if (bullet.IsPendingDestroy())
        {
            continue;
        }

        for(size_t asteroidIndex = 0; asteroidIndex < m_Asteroids.size(); asteroidIndex++)
        {
            Asteroid& asteroid = m_Asteroids[asteroidIndex];

            if (asteroid.IsPendingDestroy())
            {
                continue;
            }


            float distance = Math::Distance(bullet.GetPosition(), asteroid.GetPosition());
            float radiusSum = bullet.GetRadius() + asteroid.GetRadius();

            if (distance < radiusSum)
            {
               bullet.OnCollision(&asteroid);
               asteroid.OnCollision(&bullet);

                return;
            }
        }
    }
}


void EntityManager::CleanupDestroyedEntities()
{
    m_Bullets.erase(
        std::remove_if(
            m_Bullets.begin(),
            m_Bullets.end(),
            [](const Bullet& bullet)
            {
                return bullet.IsPendingDestroy();
            }),
        m_Bullets.end());



    m_Asteroids.erase(
        std::remove_if(
            m_Asteroids.begin(),
            m_Asteroids.end(),
            [](const Asteroid& asteroid)
            {
                return asteroid.IsPendingDestroy();
            }),
            m_Asteroids.end());
}