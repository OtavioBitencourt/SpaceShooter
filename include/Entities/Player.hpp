#pragma once

#include <SFML/Graphics.hpp>
#include "Entities/Entity.hpp"
#include <vector> 
#include "Entities/Bullet.hpp"
#include "Entities/IDamageable.hpp"

class EntityManager;

class Player : public Entity, 
               public IDamageable
{
   CLASS_NAME(Player)
   

public: 

    Player(EntityManager* entityManager);

    
    void Update(float deltaTime) override;

    void Render(sf::RenderWindow& window) override;

    EntityType GetType() const override;

    sf::Vector2f GetPosition() const override;
    float GetRadius() const override;

    void TakeDamage(int amount) override;

    void SetTargetPosition(const sf::Vector2f& position);

    int GetHealth() const { return m_Health; }

   

private: 
      
   sf::CircleShape m_Shape;
   float m_Speed;
   sf::Vector2f m_Forward;
   int m_Health;
   sf::Vector2f m_TargetPosition;

   //tiros
   float m_ShootCooldown;
   float m_CurrentShootCooldown;

   //EntityManager
   EntityManager * m_EntityManager;




};