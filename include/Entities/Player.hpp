#pragma once

#include <SFML/Graphics.hpp>

#include "Entities/Entity.hpp"
#include "Entities/IDamageable.hpp"


class EntityManager;


//============================================================
// Player
// -----------------------------------------------------------
// Representa o jogador controlado pelo usuário.
//
// O Player é responsável por:
//
// - Atualizar seu movimento.
// - Controlar sua posição e direção.
// - Processar a entrada de movimento recebida pelo Game.
// - Controlar o disparo de projéteis.
// - Gerenciar sua própria vida.
// - Receber dano através da interface IDamageable.
// - Fornecer informações utilizadas por outros sistemas.
//
// O Player utiliza o EntityManager para solicitar a criação
// de projéteis sem precisar gerenciar diretamente o armazenamento
// dessas entidades.
//
// A lógica de armazenamento, colisão e ciclo de vida das entidades
// continua sendo responsabilidade do EntityManager.
//============================================================

class Player : public Entity,
               public IDamageable
{
    CLASS_NAME(Player)

public:

    // Cria o jogador e associa o EntityManager responsável
    // pelo gerenciamento das entidades do jogo.
    Player(EntityManager* entityManager);


    // Atualiza o estado do jogador a cada frame.
    //
    // Controla movimento, direção e demais comportamentos
    // relacionados à atualização do jogador.
    void Update(float deltaTime) override;


    // Renderiza a representação visual do jogador na janela.
    void Render(sf::RenderWindow& window) override;


    // Retorna o tipo da entidade.
    // Utilizado pelo EntityManager para identificar o Player.
    EntityType GetType() const override;


    // Retorna a posição atual do jogador.
    sf::Vector2f GetPosition() const override;


    // Retorna o raio utilizado para as verificações de colisão.
    float GetRadius() const override;


    // Reduz a vida do jogador conforme a quantidade de dano recebida.
    void TakeDamage(int amount) override;


    // Define a posição que o jogador deve utilizar como alvo
    // para controlar seu movimento.
    void SetTargetPosition(const sf::Vector2f& position);


    // Retorna a quantidade atual de vida do jogador.
    //
    // O valor é somente leitura; a alteração da vida deve ocorrer
    // através da lógica responsável pelo recebimento de dano.
    int GetHealth() const
    {
        return m_Health;
    }


private:

    // Representação visual do jogador.
    sf::CircleShape m_Shape;

    // Velocidade de movimento do jogador.
    float m_Speed;

    // Direção atual de movimento do jogador.
    sf::Vector2f m_Forward;

    // Quantidade atual de vida do jogador.
    int m_Health;

    // Posição utilizada como alvo para o movimento do jogador.
    sf::Vector2f m_TargetPosition;


    //========================================================
    // Disparo
    //========================================================

    // Intervalo mínimo entre disparos consecutivos.
    float m_ShootCooldown;

    // Tempo restante até que um novo disparo possa ocorrer.
    float m_CurrentShootCooldown;


    //========================================================
    // EntityManager
    //========================================================

    // Referência utilizada pelo Player para solicitar a criação
    // de projéteis através do EntityManager.
    EntityManager* m_EntityManager;
};