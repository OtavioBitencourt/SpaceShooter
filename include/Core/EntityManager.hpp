#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "Entities/Bullet.hpp"
#include "Entities/Asteroid.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

class EntityManager
{
public:
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);

    void SpawnBullet(const sf::Vector2f& position, const sf::Vector2f& direction);
    void SpawnAsteroid(const sf::Vector2f& position, const sf::Vector2f& direction);


    template<typename T, typename... Args>
    void SpawnEntity(Args&&... args);

    void SpawnEnemy(const sf::Vector2f& position);
    void SetEnemiesTargetPosition(const sf::Vector2f& targetPosition);

    void SpawnPlayer();
    Player* GetPlayer() const;

    
    void CleanupDestroyedEntities();

    void SetOnEntityDestroyedCallback(std::function<void(EntityType)> callback);

    int GetEntityCount() const;


private:

    std::vector<std::unique_ptr<Entity>> m_Entities;
    std::vector<std::unique_ptr<Entity>> m_PendingEntities;

    void CheckCollisions();
    void CheckOutOfBounds();
    
    bool CanCollide(Entity* entityA, Entity* entityB) const;
    bool ShouldDestroyOutOfBounds(Entity* entity) const;

    void MergePendingEntities();

   

    Player* m_Player = nullptr;

    std::function<void(EntityType)> m_OnEntityDestroyed;
};



template<typename T, typename... Args>
void EntityManager::SpawnEntity(Args&&... args)
{
    m_Entities.push_back(
        std::make_unique<T>(
            std::forward<Args>(args)...));
}
