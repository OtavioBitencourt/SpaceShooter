#pragma once

#include <SFML/Graphics.hpp>
#include "Entities/IDamageable.hpp"
#include "Entities/Entity.hpp"

class Enemy : public Entity, 
              public IDamageable
{
    CLASS_NAME(Enemy)

public: 
    Enemy(const sf::Vector2f& position);

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    
    EntityType GetType() const override;
    void SetTargetPosition(const sf::Vector2f& targetPosition);


    void TakeDamage(int amount) override;

    float GetRadius() const override;
    sf::Vector2f GetPosition() const override;


private:
    sf::CircleShape m_Shape;
    
    float m_Speed; 
    int m_Health;

    sf::Vector2f m_TargetPosition;

};