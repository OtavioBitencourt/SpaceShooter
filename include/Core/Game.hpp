#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Entities/Player.hpp"
#include "Core/EntityManager.hpp"
#include "Entities/Asteroid.hpp"
#include "Core/ScoreManager.hpp"
#include "Core/HUDManager.hpp"
#include "Core/WaveManager.hpp"

//============================================================
// Game
// -----------------------------------------------------------
// Responsável por coordenar o funcionamento geral do jogo.
//
// O Game atua como ponto central de comunicação entre os
// diferentes sistemas do projeto, controlando:
//
// - Ciclo principal do jogo.
// - Processamento de eventos.
// - Atualização dos sistemas.
// - Renderização da cena.
// - Atualização do tempo de jogo.
// - Coordenação do sistema de Waves.
//
// A lógica específica de cada funcionalidade permanece
// delegada aos seus respectivos sistemas, como:
//
// - EntityManager → entidades, colisões e ciclo de vida.
// - ScoreManager  → pontuação.
// - HUDManager    → interface.
// - WaveManager   → progressão das Waves.
//
// Não é responsabilidade desta classe implementar diretamente
// a lógica interna desses sistemas.
//============================================================

class Game
{
public:

    // Inicializa a janela e os sistemas principais do jogo.
    Game();

    // Inicia o loop principal do jogo e mantém a aplicação
    // em execução enquanto a janela estiver aberta.
    void Run();

private:

    // Processa os eventos da janela, como fechamento da aplicação
    // e outras entradas suportadas pelo jogo.
    void ProcessEvents();

    // Atualiza o estado do jogo e coordena a execução dos
    // diferentes sistemas a cada frame.
    void Update();

    // Renderiza todos os elementos visuais do jogo na janela.
    void Render();

    // Gera uma posição aleatória nas bordas da área de jogo
    // para o surgimento de um novo inimigo.
    sf::Vector2f GenerateEnemySpawnPosition();

    // Cria todas as entidades necessárias para iniciar
    // a Wave atualmente controlada pelo WaveManager.
    void StartCurrentWave();

private:

    // Janela principal utilizada para renderização e recebimento
    // dos eventos da aplicação.
    sf::RenderWindow m_Window;

    // Gerencia todas as entidades do jogo, incluindo criação,
    // atualização, colisões e remoção.
    EntityManager m_EntityManager;

    // Relógio utilizado para calcular o deltaTime de cada frame.
    sf::Clock m_Clock;


    //========================================================
    // Asteroides
    //========================================================

    // Intervalo configurado entre os surgimentos de asteroides.
    float m_AsteroidSpawnTimer;

    // Tempo restante até o próximo surgimento de um asteroide.
    float m_CurrentAsteroidSpawnTimer;


    //========================================================
    // Pontuação
    //========================================================

    // Gerencia a pontuação atual do jogador.
    ScoreManager m_ScoreManager;


    //========================================================
    // HUD
    //========================================================

    // Gerencia os elementos visuais da interface do jogo.
    HUDManager m_HUDManager;

    // Tempo total transcorrido desde o início da partida,
    // armazenado em segundos.
    float m_GameTime = 0.f;


    //========================================================
    // Waves
    //========================================================

    // Controla a progressão das Waves e define a quantidade
    // de inimigos de cada Wave.
    WaveManager m_WaveManager;
};