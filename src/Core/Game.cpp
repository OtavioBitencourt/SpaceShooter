#include "Core/Game.hpp"
#include "Utils/Math.hpp"

#include <iostream>
#include <random>


//============================================================
// Game
// -----------------------------------------------------------
// Implementação responsável pela coordenação do ciclo principal
// do jogo e pela integração entre seus diferentes sistemas.
//============================================================


//------------------------------------------------------------
// Construtor
//------------------------------------------------------------

Game::Game()
    : m_Window(sf::VideoMode({1280, 720}), "Space Shooter"),
      m_AsteroidSpawnTimer(1.5f),
      m_CurrentAsteroidSpawnTimer(0.f)
{
    // Define a taxa máxima de atualização da janela.
    m_Window.setFramerateLimit(144);

    // Cria o Player antes do início do loop principal.
    m_EntityManager.SpawnPlayer();


    // Registra um callback para reagir à destruição de entidades.
    //
    // O EntityManager apenas informa qual tipo de entidade foi
    // destruído. A decisão sobre o efeito dessa destruição,
    // neste caso a pontuação, permanece sob responsabilidade
    // do Game/ScoreManager.
    m_EntityManager.SetOnEntityDestroyedCallback(
        [this](EntityType type)
        {
            switch (type)
            {
                case EntityType::Enemy:
                    // Cada inimigo destruído adiciona 100 pontos.
                    m_ScoreManager.AddScore(100);
                    break;

                case EntityType::Asteroid:
                    // Cada asteroide destruído adiciona 25 pontos.
                    m_ScoreManager.AddScore(25);
                    break;

                default:
                    // Outras entidades não alteram a pontuação.
                    break;
            }
        });


    // Inicializa os recursos e elementos visuais do HUD.
    //
    // Caso a inicialização falhe, o erro é informado no console.
    if (!m_HUDManager.Initialize())
    {
        std::cout << "Erro ao inicializar o HUDManager!"
                  << std::endl;
    }


    // Inicializa o sistema de Waves.
    m_WaveManager.Start();
}


//------------------------------------------------------------
// Run
//------------------------------------------------------------

void Game::Run()
{
    // Mantém o jogo em execução enquanto a janela estiver aberta.
    while (m_Window.isOpen())
    {
        ProcessEvents();
        Update();
        Render();
    }
}


//------------------------------------------------------------
// ProcessEvents
//------------------------------------------------------------

void Game::ProcessEvents()
{
    // Processa todos os eventos pendentes da janela.
    while (const std::optional event = m_Window.pollEvent())
    {
        // Fecha a aplicação quando o usuário solicita o
        // fechamento da janela.
        if (event->is<sf::Event::Closed>())
        {
            m_Window.close();
        }
    }
}


//------------------------------------------------------------
// Update
//------------------------------------------------------------

void Game::Update()
{
    // Calcula o tempo transcorrido desde o último frame.
    //
    // O deltaTime é utilizado para tornar os movimentos e
    // temporizadores independentes da taxa de frames.
    float deltaTime = m_Clock.restart().asSeconds();


    //--------------------------------------------------------
    // Entrada / controle do Player
    //--------------------------------------------------------

    // Obtém a posição atual do mouse na janela.
    sf::Vector2i mousePosition =
        sf::Mouse::getPosition(m_Window);

    // Converte a posição inteira do mouse para coordenadas
    // de ponto flutuante utilizadas pelo jogo.
    sf::Vector2f worldPosition(
        static_cast<float>(mousePosition.x),
        static_cast<float>(mousePosition.y));


    // Obtém uma referência ao Player gerenciado pelo
    // EntityManager.
    Player* player = m_EntityManager.GetPlayer();

    if (player != nullptr)
    {
        // Atualiza o alvo de movimento do Player.
        player->SetTargetPosition(worldPosition);

        // Informa aos inimigos a posição atual do Player,
        // permitindo que eles o utilizem como alvo.
        m_EntityManager.SetEnemiesTargetPosition(
            player->GetPosition());
    }


    //--------------------------------------------------------
    // Atualização das entidades
    //--------------------------------------------------------

    // Atualiza todas as entidades gerenciadas pelo
    // EntityManager, incluindo movimentação, colisões e
    // ciclo de vida.
    m_EntityManager.Update(deltaTime);


    //--------------------------------------------------------
    // Sistema de Waves
    //--------------------------------------------------------

    // Atualiza os temporizadores e estados internos do
    // WaveManager.
    m_WaveManager.Update(deltaTime);


    // Verifica se a Wave atual terminou.
    //
    // A conclusão só pode ocorrer quando:
    //
    // - não estamos aguardando a próxima Wave;
    // - não existe uma Wave aguardando início;
    // - não existem inimigos ativos.
    //
    // Essa condição evita que CompleteWave() seja chamado
    // repetidamente durante vários frames.
    if (!m_WaveManager.IsWaitingNextWave() &&
        !m_WaveManager.ShouldStartWave() &&
        m_EntityManager.GetEntityCount() == 0)
    {
        m_WaveManager.CompleteWave();
    }


    // Inicia uma nova Wave quando o WaveManager sinaliza
    // que ela está pronta para começar.
    if (m_WaveManager.ShouldStartWave())
    {
        StartCurrentWave();
    }


    //--------------------------------------------------------
    // Spawn de Asteroides
    //--------------------------------------------------------

    // Atualiza o temporizador responsável pelo próximo
    // surgimento de um asteroide.
    m_CurrentAsteroidSpawnTimer -= deltaTime;

    if (m_CurrentAsteroidSpawnTimer <= 0.f)
    {
        // Escolhe aleatoriamente uma das quatro bordas
        // da área de jogo.
        int side = std::rand() % 4;

        sf::Vector2f spawnPosition;

        switch (side)
        {
            // Topo
            case 0:
                spawnPosition = {
                    static_cast<float>(std::rand() % 1280),
                    -100.f
                };
                break;

            // Baixo
            case 1:
                spawnPosition = {
                    static_cast<float>(std::rand() % 1280),
                    820.f
                };
                break;

            // Esquerda
            case 2:
                spawnPosition = {
                    -100.f,
                    static_cast<float>(std::rand() % 720)
                };
                break;

            // Direita
            case 3:
                spawnPosition = {
                    1380.f,
                    static_cast<float>(std::rand() % 720)
                };
                break;
        }


        // Gera um ponto aleatório dentro da área de jogo
        // para servir como alvo do asteroide.
        sf::Vector2f target(
            static_cast<float>(std::rand() % 1280),
            static_cast<float>(std::rand() % 720));


        // Calcula a direção do movimento a partir da posição
        // de surgimento até o alvo escolhido.
        sf::Vector2f direction =
            Math::Normalize(target - spawnPosition);


        // Solicita ao EntityManager a criação do asteroide.
        m_EntityManager.SpawnAsteroid(
            spawnPosition,
            direction);


        // Reinicia o temporizador até o próximo asteroide.
        m_CurrentAsteroidSpawnTimer =
            m_AsteroidSpawnTimer;
    }


    //--------------------------------------------------------
    // Atualização do HUD
    //--------------------------------------------------------

    // Atualiza a pontuação exibida na interface.
    m_HUDManager.SetScore(
        m_ScoreManager.GetScore());


    // Atualiza a vida do Player, caso ele ainda exista.
    if (player != nullptr)
    {
        m_HUDManager.SetValue(
            "Health",
            player->GetHealth());
    }


    // Acumula o tempo total da partida.
    m_GameTime += deltaTime;

    // Exibe o tempo em segundos inteiros.
    m_HUDManager.SetValue(
        "Time",
        static_cast<int>(m_GameTime));


    // Exibe a quantidade atual de inimigos.
    m_HUDManager.SetValue(
        "Enemies",
        m_EntityManager.GetEntityCount());


    // Exibe o número da Wave atual.
    m_HUDManager.SetValue(
        "Wave",
        m_WaveManager.GetCurrentWave());
}


//------------------------------------------------------------
// Render
//------------------------------------------------------------

void Game::Render()
{
    // Limpa o conteúdo do frame anterior.
    m_Window.clear();

    // Renderiza as entidades do jogo.
    m_EntityManager.Render(m_Window);

    // Renderiza os elementos da interface sobre a cena.
    m_HUDManager.Render(m_Window);

    // Apresenta o frame final na janela.
    m_Window.display();
}


//------------------------------------------------------------
// GenerateEnemySpawnPosition
//------------------------------------------------------------

sf::Vector2f Game::GenerateEnemySpawnPosition()
{
    // O gerador aleatório é criado apenas uma vez e reutilizado
    // entre chamadas para evitar reconstruí-lo a cada spawn.
    static std::random_device rd;
    static std::mt19937 gen(rd());


    // Escolhe aleatoriamente uma das quatro bordas.
    std::uniform_int_distribution<int> sideDistribution(0, 3);

    // Define as possíveis coordenadas internas da área de jogo.
    std::uniform_real_distribution<float> xDistribution(
        0.f,
        1280.f);

    std::uniform_real_distribution<float> yDistribution(
        0.f,
        720.f);


    int side = sideDistribution(gen);

    switch (side)
    {
        // Topo
        case 0:
            return {
                xDistribution(gen),
                -50.f
            };

        // Baixo
        case 1:
            return {
                xDistribution(gen),
                770.f
            };

        // Esquerda
        case 2:
            return {
                -50.f,
                yDistribution(gen)
            };

        // Direita
        case 3:
            return {
                1330.f,
                yDistribution(gen)
            };
    }


    // Retorno de segurança caso nenhum caso esperado seja
    // selecionado.
    return {0.f, 0.f};
}


//------------------------------------------------------------
// StartCurrentWave
//------------------------------------------------------------

void Game::StartCurrentWave()
{
    // Solicita ao WaveManager a quantidade de inimigos definida
    // para a Wave atual e cria cada um deles.
    for (int i = 0;
         i < m_WaveManager.GetEnemiesToSpawn();
         ++i)
    {
        m_EntityManager.SpawnEnemy(
            GenerateEnemySpawnPosition());
    }


    // Informa ao WaveManager que a Wave foi efetivamente
    // iniciada, evitando que ela seja criada novamente.
    m_WaveManager.NotifyWaveStarted();
}