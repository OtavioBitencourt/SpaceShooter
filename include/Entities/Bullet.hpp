#pragma once

#include <SFML/Graphics.hpp>

#include "Entities/Entity.hpp"

//============================================================
// Bullet
// -----------------------------------------------------------
// Representa um projétil disparado pelo jogador.
//
// A Bullet é responsável por:
//
// - Controlar seu movimento a partir de uma direção.
// - Renderizar sua representação visual.
// - Informar sua posição e tamanho para o sistema de colisões.
// - Reagir a colisões.
// - Identificar seu tipo para o EntityManager.
//
// O ciclo de vida da Bullet é controlado pelo EntityManager.
// Quando uma colisão ou outra regra determina que o projétil
// deve deixar de existir, ele é marcado para destruição e
// posteriormente removido pelo EntityManager.
//============================================================

class Bullet : public Entity
{
    CLASS_NAME(Bullet)

public:

    // Cria um projétil na posição especificada e define
    // a direção inicial de seu movimento.
    Bullet(
        const sf::Vector2f& position,
        const sf::Vector2f& direction);


    // Atualiza a posição do projétil a cada frame.
    void Update(float deltaTime) override;


    // Renderiza o projétil na janela informada.
    void Render(sf::RenderWindow& window) override;


    // Retorna a posição atual do projétil.
    sf::Vector2f GetPosition() const override;


    // Retorna o raio utilizado nas verificações de colisão.
    float GetRadius() const override;


    // Trata colisões envolvendo o projétil.
    //
    // Dependendo do tipo da entidade atingida, a colisão pode
    // resultar em dano e/ou destruição do próprio projétil.
    void OnCollision(Entity* other) override;


    // Retorna o tipo da entidade.
    EntityType GetType() const override;


private:

    // Representação visual do projétil.
    sf::CircleShape m_Shape;

    // Direção atual de movimento do projétil.
    sf::Vector2f m_Direction;

    // Velocidade de movimento do projétil.
    float m_Speed;
};