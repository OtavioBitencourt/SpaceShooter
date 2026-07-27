#include "Core/Game.hpp"
#include "Utils/Math.hpp"

#include <random>


Game::Game()
    : m_Window(sf::VideoMode({1280, 720}), "Space Shooter"),  
      m_EnemySpawnTimer(0.f),
      m_EnemySpawnInterval(2.f),
      m_AsteroidSpawnTimer(1.5f),
      m_CurrentAsteroidSpawnTimer(0.f)

{
    m_Window.setFramerateLimit(144);
    m_EntityManager.SpawnPlayer();

    m_EntityManager.SetOnEntityDestroyedCallback([this](EntityType type) {
       switch (type)
       {
            case EntityType::Enemy:
                m_ScoreManager.AddScore(100);
                break;

            case EntityType::Asteroid:
                m_ScoreManager.AddScore(25);
                break;
            
            default:
                break;
       }
    });
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

    Player* player = m_EntityManager.GetPlayer();

    if (player != nullptr)
    {
        player->SetTargetPosition(worldPosition);
        m_EntityManager.SetEnemiesTargetPosition(player->GetPosition());
    }

    m_EntityManager.Update(deltaTime);


    // Enemy Spawn
    m_EnemySpawnTimer += deltaTime;

    if (m_EnemySpawnTimer >= m_EnemySpawnInterval)
    {
        m_EntityManager.SpawnEnemy(GenerateEnemySpawnPosition());
        m_EnemySpawnTimer = 0.f;
    }

    

    //Asteroids Spawn

    m_CurrentAsteroidSpawnTimer -= deltaTime; //Atualiza o temporizador de spawn

    if (m_CurrentAsteroidSpawnTimer <= 0.f) 
    {

        int side = std::rand() % 4; //Escolhe uma borda aleatória

        sf::Vector2f spawnPosition;

        switch (side) 
        {
            //TOPO
            case 0: 
                spawnPosition = {static_cast<float>(std::rand() % 1280), -100.f};
                break; 

            
            //BAIXO
            case 1: 
                spawnPosition = {static_cast<float>(std::rand() % 1280), 820.f};
                break;


            //ESQUERDA
            case 2: 
                spawnPosition = {-100.f, static_cast<float>(std::rand() % 720)};
                break;

            //DIREITA
            case 3: 
                spawnPosition = {1380.f, static_cast<float>(std::rand() % 720)};
                break;
        }

        //Ponto aleatório da tela - direação do asteroide
        sf::Vector2f target (static_cast<float>(std::rand() % 1280), static_cast<float>(std::rand() % 720)); 

        //Vetor que aponta do spawn até o alvo
        sf::Vector2f direction = Math::Normalize(target - spawnPosition);

        //Cria o asteroide
        m_EntityManager.SpawnAsteroid(spawnPosition, direction);

        //Reinicia o temporizador
        m_CurrentAsteroidSpawnTimer = m_AsteroidSpawnTimer;
    }

}

void Game::Render()
{
    m_Window.clear();

    m_EntityManager.Render(m_Window);

    m_ScoreManager.Render(m_Window);

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