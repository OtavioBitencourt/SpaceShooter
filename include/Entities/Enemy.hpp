#pragma once

#include <SFML/Graphics.hpp>
#include "Entities/Entity.hpp"

class Enemy : public Entity
{
    CLASS_NAME(Enemy)

public: 
    Enemy(const sf::Vector2f& position);

    void Update(float deltaTime) override;
    void SetTargetPosition(const sf::Vector2f& targetPosition);

    void Render(sf::RenderWindow& window) override;

    void TakeDamage(int amount);

    float GetRadius() const override;
    sf::Vector2f GetPosition() const override;

    EntityType GetType() const override;

private:
    sf::CircleShape m_Shape;
    
    float m_Speed; 
    int m_Health;

    sf::Vector2f m_TargetPosition;

};