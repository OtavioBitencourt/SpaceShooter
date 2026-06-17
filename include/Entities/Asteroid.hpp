#pragma once

#include <SFML/Graphics.hpp>
#include "Entities/Entity.hpp"

class Asteroid : public Entity
{
    CLASS_NAME(Asteroid)

public: 
    Asteroid(const sf::Vector2f& position, const sf::Vector2f& direction);

    void Update(float deltaTime);
    void Render(sf::RenderWindow& window); 

    sf::Vector2f GetPosition() const override;
    float GetRadius() const override;

    void OnCollision(Entity* other) override;

    EntityType GetType() const override;

private: 
    sf::CircleShape m_Shape;
    sf::Vector2f m_Direction; 
    float m_Speed;
    
};