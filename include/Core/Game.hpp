#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Entities/Player.hpp"
#include "Core/EntityManager.hpp"
#include "Entities/Asteroid.hpp"
#include "Core/ScoreManager.hpp"
#include "Core/HUDManager.hpp"
#include "Core/WaveManager.hpp"

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

    void StartCurrentWave();

private: 
    sf::RenderWindow m_Window;
    EntityManager m_EntityManager;


    sf::Clock m_Clock;

    float m_EnemySpawnTimer;
    float m_EnemySpawnInterval;

    //Asteroides
    float m_AsteroidSpawnTimer;
    float m_CurrentAsteroidSpawnTimer;

    //Score
    ScoreManager m_ScoreManager;

    //HUD
    HUDManager m_HUDManager;
    float m_GameTime = 0.f;

    //WAVE
    WaveManager m_WaveManager;
    
    


};