#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Object.hpp"
#include "Entities/EntityType.hpp"

class Entity : public Object
{
    CLASS_NAME(Entity)

public: 
    virtual ~Entity() = default;

    virtual void Update(float deltaTime) = 0; 

    virtual void Render(sf::RenderWindow& window) = 0;

    virtual void OnCollision(Entity* other);

    virtual sf::Vector2f GetPosition() const;
    virtual float GetRadius() const;
    
    virtual EntityType GetType() const = 0;

    void Destroy();
    bool IsPendingDestroy() const;



private:
    bool m_IsPendingDestroy = false;
    
};