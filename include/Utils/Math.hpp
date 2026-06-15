#pragma once

#include <SFML/System/Vector2.hpp> 
#include <cmath> 

namespace Math
{
    inline float Length(const sf::Vector2f& vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    inline sf::Vector2f Normalize(const sf::Vector2f& vector)
    {
        float length = Length(vector);

        if(length == 0.f)
        {
            return {};
        }
        return vector / length;
    }

    inline float Distance(const sf::Vector2f& a, const sf::Vector2f& b)
    {
        return Length(b - a);
    }

    static sf::Vector2f MoveTowards(const sf::Vector2f& current, const sf::Vector2f& target, float speed, float deltaTime)
    {
        sf::Vector2f direction = target - current; 

        direction = Normalize(direction);

        return current + direction * speed * deltaTime;
    }
}