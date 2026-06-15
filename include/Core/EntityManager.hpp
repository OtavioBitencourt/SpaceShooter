#pragma once

#include <vector>

#include "Entities/Bullet.hpp"
#include "Entities/Asteroid.hpp"

class EntityManager
{
public: 
    void Update(float deltaTime);

    void Render(sf::RenderWindow& window);

    void SpawnBullet(const sf::Vector2f& position, const sf::Vector2f& direction);

    void SpawnAsteroid(const sf::Vector2f& position, const sf::Vector2f& direction);

    void CleanupDestroyedEntities();

private:
    std::vector<Bullet> m_Bullets;
    std::vector<Asteroid> m_Asteroids;
    
    void CheckCollisions();
};