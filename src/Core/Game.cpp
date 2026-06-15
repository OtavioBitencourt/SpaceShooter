#include "Core/Game.hpp"

Game::Game()
    : m_Window(sf::VideoMode({1280, 720}), "Space Shooter"), 
      m_Player(&m_EntityManager)
{
    m_Window.setFramerateLimit(144);
}

void Game::Run()
{
    while (m_Window.isOpen())
    {
        ProcessEvents();
        Update();
        Render();
    }
}

void Game::ProcessEvents()
{
    while (const std::optional event = m_Window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_Window.close();
        }
    }
}

void Game::Update()
{

    float deltaTime = m_Clock.restart().asSeconds();

    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_Window);

    sf::Vector2f worldPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    m_Player.Update(deltaTime, worldPosition);

    m_EntityManager.Update(deltaTime);
}

void Game::Render()
{
    m_Window.clear();

    m_Player.Render(m_Window);

    m_EntityManager.Render(m_Window);

    m_Window.display();
}