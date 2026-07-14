#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Entities/Player.hpp"
#include "Core/EntityManager.hpp"
#include "Entities/Asteroid.hpp"


class Game
{
public:
    Game();
    void Run();

private: 
    void ProcessEvents();
    void Update();
    void Render();
    
    sf::Vector2f GenerateEnemySpawnPosition();

private: 
    sf::RenderWindow m_Window;
    EntityManager m_EntityManager;


    sf::Clock m_Clock;

    float m_EnemySpawnTimer;
    float m_EnemySpawnInterval;

    //asteroides
    float m_AsteroidSpawnTimer;
    float m_CurrentAsteroidSpawnTimer;

    


};