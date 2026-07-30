#pragma once

class WaveManager
{
public:

    // Construtor responsável por inicializar o estado do sistema de Waves.
    WaveManager();

    // Reinicia o sistema de Waves para o estado inicial.
    // Deve ser chamado sempre que um novo jogo começar.
    void Start();

    // Atualiza a lógica das Waves.
    // Controla o tempo de espera entre uma Wave e outra.
    void Update(float deltaTime);

    // Retorna o número da Wave atual.
    int GetCurrentWave() const;

    // Informa ao WaveManager que todos os inimigos da Wave atual foram derrotados.
    void CompleteWave();

    // Indica se o jogo ainda está aguardando o tempo para iniciar a próxima Wave.
    bool IsWaitingNextWave() const;

    // Retorna a quantidade de inimigos que deverão ser criados na Wave atual.
    int GetEnemiesToSpawn() const;

    // Indica se uma nova Wave está pronta para ser iniciada.
    bool ShouldStartWave() const;

    // Informa ao WaveManager que a Wave já foi iniciada,
    // evitando que os inimigos sejam criados mais de uma vez.
    void NotifyWaveStarted();

    // Prepara o estado da próxima Wave
    void StartNextWave();

private:

    // Quantidade inicial de inimigos da primeira Wave.
    static constexpr int INITIAL_ENEMIES = 5;

    // Tempo de espera entre o fim de uma Wave e o início da próxima.
    static constexpr float NEXT_WAVE_DELAY = 2.f;

    // Progressão de waves
    static constexpr int ENEMIES_INCREMENT = 3; 

    // Número da Wave atual.
    int m_CurrentWave;

    // Quantidade de inimigos que deverão ser criados na Wave atual.
    int m_EnemiesToSpawn;

    // Indica se o sistema está aguardando para iniciar a próxima Wave.
    bool m_WaitingNextWave;

    // Contador utilizado durante o tempo de espera entre Waves.
    float m_NextWaveTimer;

    // Indica ao Game que uma nova Wave deve ser criada.
    bool m_ShouldStartWave;
};