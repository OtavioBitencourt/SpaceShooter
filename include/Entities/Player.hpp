#pragma once

#include <SFML/Graphics.hpp>
#include "Entities/Entity.hpp"
#include <vector> 
#include "Entities/Bullet.hpp"
#include "Entities/Asteroid.hpp"

class EntityManager;

class Player : public Entity
{
   CLASS_NAME(Player)
   

public: 

    Player(EntityManager* entityManager);

    void Update(float deltaTime, const sf::Vector2f& targetPosition);

    void Render(sf::RenderWindow& window) override;

   

private: 
      
   sf::CircleShape m_Shape;
   float m_Speed;
   sf::Vector2f m_Forward;

   //tiros
   float m_ShootCooldown;
   float m_CurrentShootCooldown;

   //asteroides
   float m_AsteroidSpawnTimer;
   float m_CurrentAsteroidSpawnTimer;

   //EntityManager
   EntityManager * m_EntityManager;



};