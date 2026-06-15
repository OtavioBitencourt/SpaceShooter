#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Entities/Player.hpp"
#include "Core/EntityManager.hpp"

class Game
{
public:
    Game();
    void Run();

private: 
    void ProcessEvents();
    void Update();
    void Render();

private: 
    sf::RenderWindow m_Window;
    EntityManager m_EntityManager;
    Player m_Player; 
    sf::Clock m_Clock;


};