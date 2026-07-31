#pragma once

#include <SFML/Graphics.hpp>

#include "Entities/Entity.hpp"
#include "Entities/IDamageable.hpp"

//============================================================
// Enemy
// -----------------------------------------------------------
// Representa um inimigo controlado pelo jogo.
//
// O Enemy é responsável por:
//
// - Atualizar seu movimento em direção ao alvo definido.
// - Renderizar sua representação visual.
// - Controlar sua própria vida.
// - Receber e processar dano.
// - Reagir a colisões.
// - Fornecer informações utilizadas pelo EntityManager.
//
// O Enemy implementa IDamageable, permitindo que sistemas de
// combate e colisão causem dano sem depender da implementação
// específica do inimigo.
//
// O gerenciamento do ciclo de vida do Enemy permanece sob
// responsabilidade do EntityManager.
//============================================================

class Enemy : public Entity,
              public IDamageable
{
    CLASS_NAME(Enemy)

public:

    // Cria um inimigo na posição especificada.
    Enemy(const sf::Vector2f& position);


    // Atualiza o movimento e o estado do inimigo a cada frame.
    void Update(float deltaTime) override;


    // Renderiza o inimigo na janela informada.
    void Render(sf::RenderWindow& window) override;


    // Retorna o tipo da entidade.
    EntityType GetType() const override;


    // Define a posição que será utilizada como alvo
    // para o movimento do inimigo.
    void SetTargetPosition(
        const sf::Vector2f& targetPosition);


    // Aplica dano à vida do inimigo.
    //
    // A implementação determina como o inimigo reage ao dano
    // e quando deve ser marcado para destruição.
    void TakeDamage(int amount) override;


    // Retorna o raio utilizado nas verificações de colisão.
    float GetRadius() const override;


    // Retorna a posição atual do inimigo.
    sf::Vector2f GetPosition() const override;


    // Trata colisões envolvendo o inimigo.
    void OnCollision(Entity* other) override;


private:

    // Representação visual do inimigo.
    sf::CircleShape m_Shape;

    // Velocidade de movimento do inimigo.
    float m_Speed;

    // Quantidade atual de vida do inimigo.
    int m_Health;

    // Posição utilizada como alvo para o movimento do inimigo.
    sf::Vector2f m_TargetPosition;
};