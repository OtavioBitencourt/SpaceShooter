#pragma once

//============================================================
// IDamageable
// -----------------------------------------------------------
// Interface para entidades que podem receber dano.
//
// Qualquer classe que implemente esta interface deve fornecer
// sua própria implementação de TakeDamage(), definindo como o
// dano recebido afeta seu estado.
//
// Exemplos de entidades que podem implementar esta interface:
// - Player
// - Enemy
//
// A interface permite que sistemas de colisão e combate
// causem dano sem precisar conhecer detalhes internos da
// entidade que está sendo atingida.
//============================================================

class IDamageable
{
public:

    // Destrutor virtual necessário para garantir a destruição
    // correta de classes derivadas através de um ponteiro
    // para IDamageable.
    virtual ~IDamageable() = default;

    // Aplica a quantidade de dano informada à entidade.
    //
    // Cada classe que implementa IDamageable define como o dano
    // deve ser tratado.
    virtual void TakeDamage(int amount) = 0;
};