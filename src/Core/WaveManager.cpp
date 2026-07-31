#include "Core/WaveManager.hpp"

//============================================================
// WaveManager
// -----------------------------------------------------------
// Implementação responsável pelo controle do ciclo de vida
// das Waves, incluindo:
//
// - Wave atual.
// - Quantidade de inimigos por Wave.
// - Intervalo entre Waves.
// - Sinalização para início de uma nova Wave.
//============================================================


//------------------------------------------------------------
// Construtor
//------------------------------------------------------------

WaveManager::WaveManager()
    : m_CurrentWave(1),
      m_EnemiesToSpawn(INITIAL_ENEMIES),
      m_WaitingNextWave(false),
      m_NextWaveTimer(0.f),
      m_ShouldStartWave(true)
{
    // A primeira Wave fica marcada como pronta para iniciar.
    // O Game utilizará esse sinal para criar os inimigos iniciais.
}


//------------------------------------------------------------
// Start
//------------------------------------------------------------

void WaveManager::Start()
{
    // Reinicia o número da Wave para o estado inicial.
    m_CurrentWave = 1;
}


//------------------------------------------------------------
// Update
//------------------------------------------------------------

void WaveManager::Update(float deltaTime)
{
    // Enquanto não houver uma transição entre Waves,
    // não existe nenhuma contagem de tempo a ser processada.
    if (!m_WaitingNextWave)
    {
        return;
    }


    // Atualiza o tempo restante até o início da próxima Wave.
    m_NextWaveTimer -= deltaTime;


    // Quando o intervalo termina, prepara a próxima Wave.
    if (m_NextWaveTimer <= 0.f)
    {
        m_WaitingNextWave = false;

        StartNextWave();
    }
}


//------------------------------------------------------------
// GetCurrentWave
//------------------------------------------------------------

int WaveManager::GetCurrentWave() const
{
    // Retorna o número da Wave atualmente configurada.
    return m_CurrentWave;
}


//------------------------------------------------------------
// GetEnemiesToSpawn
//------------------------------------------------------------

int WaveManager::GetEnemiesToSpawn() const
{
    // Retorna a quantidade de inimigos que o Game deve criar
    // para a Wave atual.
    return m_EnemiesToSpawn;
}


//------------------------------------------------------------
// CompleteWave
//------------------------------------------------------------

void WaveManager::CompleteWave()
{
    // Marca que a Wave atual terminou e inicia o intervalo
    // antes da próxima.
    m_WaitingNextWave = true;

    // Define o tempo que deve ser aguardado antes da próxima Wave.
    m_NextWaveTimer = NEXT_WAVE_DELAY;
}


//------------------------------------------------------------
// IsWaitingNextWave
//------------------------------------------------------------

bool WaveManager::IsWaitingNextWave() const
{
    // Indica se o sistema está atualmente no intervalo
    // entre duas Waves.
    return m_WaitingNextWave;
}


//------------------------------------------------------------
// ShouldStartWave
//------------------------------------------------------------

bool WaveManager::ShouldStartWave() const
{
    // Informa ao Game se existe uma Wave pronta para ser criada.
    return m_ShouldStartWave;
}


//------------------------------------------------------------
// NotifyWaveStarted
//------------------------------------------------------------

void WaveManager::NotifyWaveStarted()
{
    // Consome o sinal de início da Wave para impedir que o Game
    // crie a mesma Wave novamente nos frames seguintes.
    m_ShouldStartWave = false;
}


//------------------------------------------------------------
// StartNextWave
//------------------------------------------------------------

void WaveManager::StartNextWave()
{
    // Avança para a próxima Wave.
    m_CurrentWave++;

    // Aumenta a quantidade de inimigos de acordo com a regra
    // de progressão definida para o jogo.
    m_EnemiesToSpawn += ENEMIES_INCREMENT;

    // Informa ao Game que a nova Wave está pronta para começar.
    m_ShouldStartWave = true;
}