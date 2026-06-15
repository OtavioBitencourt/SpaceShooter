#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Object.hpp"

class Entity : public Object
{
    CLASS_NAME(Entity)

public: 
    virtual ~Entity() = default;

    virtual void Update(float deltaTime); 

    virtual void Render(sf::RenderWindow& window);

    void Destroy();
    virtual void OnCollision(Entity* other);
    bool IsPendingDestroy() const;

private:
    bool m_IsPendingDestroy = false;
    
};