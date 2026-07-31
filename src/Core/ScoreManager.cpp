#include "Core/ScoreManager.hpp"


//============================================================
// ScoreManager
// -----------------------------------------------------------
// Implementação responsável pelo armazenamento e atualização
// da pontuação atual do jogador.
//============================================================


//------------------------------------------------------------
// Construtor
//------------------------------------------------------------

ScoreManager::ScoreManager()
    : m_Score(0)
{
    // A pontuação começa em zero a cada nova instância do
    // ScoreManager.
}


//------------------------------------------------------------
// AddScore
//------------------------------------------------------------

void ScoreManager::AddScore(int amount)
{
    // Adiciona a quantidade informada à pontuação atual.
    //
    // A decisão sobre quando e quantos pontos devem ser
    // concedidos pertence aos sistemas que utilizam o
    // ScoreManager.
    m_Score += amount;
}


//------------------------------------------------------------
// GetScore
//------------------------------------------------------------

int ScoreManager::GetScore() const
{
    // Retorna a pontuação atual sem modificar o estado
    // interno do ScoreManager.
    return m_Score;
}