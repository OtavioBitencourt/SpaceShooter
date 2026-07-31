#pragma once

//============================================================
// ScoreManager
// -----------------------------------------------------------
// Responsável exclusivamente pelo gerenciamento da pontuação
// atual do jogador.
//
// Responsabilidades:
// - Armazenar a pontuação atual.
// - Adicionar pontos.
// - Fornecer a pontuação para outros sistemas.
//
// O ScoreManager não é responsável pela representação visual
// da pontuação. A exibição dos valores é responsabilidade do
// HUDManager.
//
// Dessa forma, a lógica da pontuação permanece separada da
// interface gráfica.
//============================================================

class ScoreManager
{
public:

    // Inicializa a pontuação com seu valor inicial.
    ScoreManager();


    // Adiciona a quantidade informada à pontuação atual.
    void AddScore(int amount);


    // Retorna a pontuação atual do jogador.
    int GetScore() const;


private:

    // Pontuação atual do jogador.
    int m_Score;
};