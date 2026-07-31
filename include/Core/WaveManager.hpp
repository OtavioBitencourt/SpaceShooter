#pragma once

//============================================================
// WaveManager
// -----------------------------------------------------------
// Responsável por controlar a progressão das Waves do jogo.
//
// Responsabilidades:
// - Controlar a Wave atual.
// - Definir a quantidade de inimigos por Wave.
// - Controlar o intervalo entre Waves.
// - Informar quando uma nova Wave deve ser iniciada.
//
// Não é responsabilidade desta classe:
// - Criar ou remover entidades.
// - Atualizar entidades.
// - Renderizar informações na tela.
//============================================================

class WaveManager
{
public:

    // Inicializa o sistema com os valores padrão da primeira Wave.
    WaveManager();

    // Reinicia o sistema de Waves para o estado inicial.
    void Start();

    // Atualiza os temporizadores e estados relacionados às Waves.
    void Update(float deltaTime);

    // Retorna o número da Wave atualmente ativa.
    int GetCurrentWave() const;

    // Informa ao WaveManager que todos os inimigos da Wave atual
    // foram eliminados e inicia o processo de transição.
    void CompleteWave();

    // Informa se o sistema está aguardando o início da próxima Wave.
    bool IsWaitingNextWave() const;

    // Retorna a quantidade de inimigos que devem ser criados
    // para a Wave atual.
    int GetEnemiesToSpawn() const;

    // Informa ao Game que uma nova Wave está pronta para começar.
    bool ShouldStartWave() const;

    // Confirma que o Game iniciou a Wave atual e limpa o sinal
    // utilizado para impedir que a mesma Wave seja iniciada mais
    // de uma vez.
    void NotifyWaveStarted();

private:

    // Avança para a próxima Wave e prepara seu estado para início.
    void StartNextWave();

    // Quantidade inicial de inimigos da primeira Wave.
    static constexpr int INITIAL_ENEMIES = 5;

    // Tempo de espera entre o final de uma Wave e o início da próxima.
    static constexpr float NEXT_WAVE_DELAY = 2.f;

    // Quantidade adicionada ao número de inimigos a cada nova Wave.
    static constexpr int ENEMIES_INCREMENT = 3;

    // Número da Wave atualmente ativa.
    int m_CurrentWave;

    // Quantidade de inimigos que devem ser criados na Wave atual.
    int m_EnemiesToSpawn;

    // Indica se o sistema está aguardando o término do intervalo
    // entre Waves.
    bool m_WaitingNextWave;

    // Temporizador utilizado durante o intervalo entre Waves.
    float m_NextWaveTimer;

    // Indica ao Game que existe uma nova Wave pronta para ser iniciada.
    bool m_ShouldStartWave;
};