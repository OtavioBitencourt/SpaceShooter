#include "Core/ScoreManager.hpp"

ScoreManager::ScoreManager()
    : m_Score(0)
{
}

void ScoreManager::AddScore(int amount)
{
    m_Score += amount;
}

int ScoreManager::GetScore() const
{
    return m_Score;
}