#pragma once

#include <vector>
#include <memory>

#include "Entities/Bullet.hpp"
#include "Entities/Asteroid.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Enemy.hpp"

class EntityManager
{
public:
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);

    void SpawnBullet(const sf::Vector2f& position, const sf::Vector2f& direction);
    void SpawnAsteroid(const sf::Vector2f& position, const sf::Vector2f& direction);

    void CleanupDestroyedEntities();

    template<typename T, typename... Args>
    void SpawnEntity(Args&&... args);

    void SpawnEnemy(const sf::Vector2f& position);
    void SetEnemiesTargetPosition(const sf::Vector2f& targetPosition);

private:
    std::vector<Bullet> m_Bullets;
    std::vector<Asteroid> m_Asteroids;

    std::vector<std::unique_ptr<Entity>> m_Entities;

    void CheckCollisions();
};


template<typename T, typename... Args>
void EntityManager::SpawnEntity(Args&&... args)
{
    m_Entities.push_back(
        std::make_unique<T>(
            std::forward<Args>(args)...));
}
