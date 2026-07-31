#pragma once

//============================================================
// EntityType
// -----------------------------------------------------------
// Identifica os tipos de entidades existentes no jogo.
//
// O EntityManager utiliza essa informação para diferenciar
// entidades e aplicar comportamentos específicos, como:
//
// - Regras de colisão.
// - Pontuação.
// - Contagem de inimigos.
// - Regras de destruição fora dos limites.
//
// Sempre que um novo tipo de entidade for criado, ele deve
// ser adicionado a este enum.
//============================================================

enum class EntityType
{
    // Jogador controlado pelo usuário.
    Player,

    // Projétil disparado pelo jogador.
    Bullet,

    // Asteroide presente no cenário.
    Asteroid,

    // Inimigo controlado pelo jogo.
    Enemy
};