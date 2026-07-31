#pragma once

#include <SFML/Graphics.hpp>

#include "Entities/Entity.hpp"

//============================================================
// Asteroid
// -----------------------------------------------------------
// Representa um asteroide presente no jogo.
//
// A Asteroid é responsável por:
//
// - Controlar seu movimento a partir de uma direção.
// - Renderizar sua representação visual.
// - Informar sua posição e tamanho para o sistema de colisões.
// - Reagir a colisões.
// - Identificar seu tipo para o EntityManager.
//
// O ciclo de vida do Asteroid é controlado pelo EntityManager.
// Quando uma regra do jogo determina que ele deve ser removido,
// a entidade é marcada para destruição e posteriormente removida
// pelo EntityManager.
//============================================================

class Asteroid : public Entity
{
    CLASS_NAME(Asteroid)

public:

    // Cria um asteroide na posição especificada e define
    // sua direção inicial de movimento.
    Asteroid(
        const sf::Vector2f& position,
        const sf::Vector2f& direction);


    // Atualiza a posição e o estado do asteroide a cada frame.
    void Update(float deltaTime) override;


    // Renderiza o asteroide na janela informada.
    void Render(sf::RenderWindow& window) override;


    // Retorna a posição atual do asteroide.
    sf::Vector2f GetPosition() const override;


    // Retorna o raio utilizado nas verificações de colisão.
    float GetRadius() const override;


    // Trata colisões envolvendo o asteroide.
    void OnCollision(Entity* other) override;


    // Retorna o tipo da entidade.
    EntityType GetType() const override;


private:

    // Representação visual do asteroide.
    sf::CircleShape m_Shape;

    // Direção atual de movimento do asteroide.
    sf::Vector2f m_Direction;

    // Velocidade de movimento do asteroide.
    float m_Speed;
};