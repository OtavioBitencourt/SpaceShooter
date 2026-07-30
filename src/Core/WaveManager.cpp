#include "Core/WaveManager.hpp"

WaveManager::WaveManager()
    : m_CurrentWave(1),
      m_EnemiesToSpawn(INITIAL_ENEMIES), 
      m_WaitingNextWave(false),
      m_NextWaveTimer(0.f),
      m_ShouldStartWave(true)
{
}

void WaveManager::Start()
{
    m_CurrentWave = 1; 
}

void WaveManager::Update(float deltaTime)
{
    if (!m_WaitingNextWave)
    {
        return;
    }

    m_NextWaveTimer -= deltaTime;

    if (m_NextWaveTimer <= 0.f)
    {
        m_WaitingNextWave = false;
        
        StartNextWave();
    }

}


int WaveManager::GetCurrentWave() const
{
    return m_CurrentWave;
}


int WaveManager::GetEnemiesToSpawn() const
{
    return m_EnemiesToSpawn;
}


void WaveManager::CompleteWave()
{
    m_WaitingNextWave = true;
    m_NextWaveTimer = NEXT_WAVE_DELAY;
}


bool WaveManager::IsWaitingNextWave() const
{
    return m_WaitingNextWave;
}


bool WaveManager::ShouldStartWave() const
{
    return m_ShouldStartWave;
}

void WaveManager::NotifyWaveStarted()
{
    m_ShouldStartWave = false;
}


void WaveManager::StartNextWave()
{
    m_CurrentWave++;
    m_EnemiesToSpawn += ENEMIES_INCREMENT;
    m_ShouldStartWave = true;
}