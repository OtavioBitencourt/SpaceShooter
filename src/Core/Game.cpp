#include "Core/Game.hpp"
#include <random>

Game::Game()
    : m_Window(sf::VideoMode({1280, 720}), "Space Shooter"), 
      m_Player(&m_EntityManager), 
      m_EnemySpawnTimer(0.f),
      m_EnemySpawnInterval(2.f)

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

    sf::Vector2f worldPosition(
        static_cast<float>(mousePosition.x), 
        static_cast<float>(mousePosition.y));

    m_Player.Update(deltaTime, worldPosition);
    
    m_EntityManager.SetEnemiesTargetPosition(m_Player.GetPosition());
    m_EntityManager.Update(deltaTime);

    m_EnemySpawnTimer += deltaTime;

    if(m_EnemySpawnTimer >= m_EnemySpawnInterval)
    {
        m_EntityManager.SpawnEnemy(GenerateEnemySpawnPosition());
        m_EnemySpawnTimer = 0.f;
    }

}

void Game::Render()
{
    m_Window.clear();

    m_Player.Render(m_Window);

    m_EntityManager.Render(m_Window);

    m_Window.display();
}

sf::Vector2f Game::GenerateEnemySpawnPosition()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> sideDistribution(0, 3);

    std::uniform_real_distribution<float> xDistribution(0.f, 1280.f);
    std::uniform_real_distribution<float> yDistribution(0.f, 720.f);

    int side = sideDistribution(gen);

    switch(side)
    {
        case 0: //Topo
            return { xDistribution(gen), -50.f};
        
        case 1: //Baixo   
            return { xDistribution(gen), 770.f};
        
        case 2: //Esquerda
            return {-50.f, yDistribution(gen)};
        
        case 3: //Direita
            return {1330.f, yDistribution(gen)};
    }

    return {0.f, 0.f};   
}