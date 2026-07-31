#include "Entities/Player.hpp"
#include "Utils/Math.hpp"

#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdlib>

#include "Core/EntityManager.hpp"


//============================================================
// Player
// -----------------------------------------------------------
// Implementação responsável pelo comportamento do jogador,
// incluindo:
//
// - Movimento em direção ao alvo.
// - Rotação da nave.
// - Disparo de projéteis.
// - Controle do cooldown de tiro.
// - Gerenciamento da própria vida.
// - Recebimento de dano.
//============================================================


//------------------------------------------------------------
// Construtor
//------------------------------------------------------------

Player::Player(EntityManager* entityManager)
    : m_Speed(400.f),
      m_Health(100),
      m_ShootCooldown(0.1f),
      m_CurrentShootCooldown(0.f),
      m_EntityManager(entityManager)
{
    // Define a nave como uma forma triangular.
    m_Shape.setPointCount(3);

    // Define o tamanho da nave.
    m_Shape.setRadius(30.f);

    // Define a cor utilizada para desenhar o Player.
    m_Shape.setFillColor(sf::Color::Cyan);

    // Centraliza a origem da forma para facilitar o cálculo
    // de posição e rotação.
    m_Shape.setOrigin({30.f, 30.f});

    // Posiciona o jogador no centro inicial da tela.
    m_Shape.setPosition({640.f, 360.f});


    // Inicializa a semente utilizada pelas funções de geração
    // aleatória da biblioteca padrão.
    std::srand(
        static_cast<unsigned>(
            std::time(nullptr)));


    // Define a direção inicial do Player como apontando para cima.
    m_Forward = sf::Vector2f(0.f, -1.f);
}


//------------------------------------------------------------
// Update
//------------------------------------------------------------

void Player::Update(float deltaTime)
{
    // Obtém a posição atual da nave.
    sf::Vector2f currentPosition =
        m_Shape.getPosition();

    // Calcula o vetor que aponta da posição atual até o alvo.
    sf::Vector2f direction =
        m_TargetPosition - currentPosition;


    // Calcula a distância entre o jogador e seu alvo.
    float distance = Math::Length(direction);


    // Evita movimentações muito pequenas quando o jogador
    // já está próximo do alvo.
    if (distance > 5.f)
    {
        // Converte o vetor de movimento em um vetor unitário,
        // mantendo apenas sua direção.
        direction = Math::Normalize(direction);


        // Armazena a direção atual para que ela também possa
        // ser utilizada como direção do próximo disparo.
        m_Forward = direction;


        // Move a nave proporcionalmente à velocidade e ao
        // tempo transcorrido desde o último frame.
        m_Shape.move(
            direction * m_Speed * deltaTime);


        // Calcula o ângulo da direção atual em radianos.
        float angle =
            std::atan2(direction.y, direction.x);


        // Converte o ângulo de radianos para graus para utilizar
        // na API de rotação da SFML.
        float angleDegress =
            angle * 180.f / 3.14159265f;


        // Rotaciona a nave para que ela aponte na direção do alvo.
        //
        // O deslocamento de 90 graus compensa a orientação
        // inicial do triângulo.
        m_Shape.setRotation(
            sf::degrees(angleDegress + 90.f));
    }


    //--------------------------------------------------------
    // Controle do disparo
    //--------------------------------------------------------

    // Reduz o tempo restante do cooldown do disparo.
    m_CurrentShootCooldown -= deltaTime;


    // Permite disparar somente quando o botão esquerdo do mouse
    // estiver pressionado e o cooldown tiver terminado.
    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Button::Left) &&
        m_CurrentShootCooldown <= 0.f)
    {
        // Solicita ao EntityManager a criação de um projétil
        // na posição atual do Player e utilizando sua direção
        // atual como direção inicial da bala.
        m_EntityManager->SpawnBullet(
            m_Shape.getPosition(),
            m_Forward);


        // Reinicia o cooldown até que um novo disparo seja permitido.
        m_CurrentShootCooldown =
            m_ShootCooldown;
    }
}


//------------------------------------------------------------
// Render
//------------------------------------------------------------

void Player::Render(sf::RenderWindow& window)
{
    // Desenha a representação visual do Player.
    window.draw(m_Shape);
}


//------------------------------------------------------------
// GetType
//------------------------------------------------------------

EntityType Player::GetType() const
{
    // Retorna o tipo utilizado pelo EntityManager para
    // identificar esta entidade como Player.
    return EntityType::Player;
}


//------------------------------------------------------------
// GetPosition
//------------------------------------------------------------

sf::Vector2f Player::GetPosition() const
{
    // Retorna a posição atual do Player.
    return m_Shape.getPosition();
}


//------------------------------------------------------------
// GetRadius
//------------------------------------------------------------

float Player::GetRadius() const
{
    // Retorna o raio da forma utilizado pelo sistema de colisões.
    return m_Shape.getRadius();
}


//------------------------------------------------------------
// TakeDamage
//------------------------------------------------------------

void Player::TakeDamage(int amount)
{
    // Reduz a vida do Player de acordo com o dano recebido.
    m_Health -= amount;


    // Exibe a vida atual no console para fins de acompanhamento
    // e depuração durante o desenvolvimento.
    std::cout
        << "Player HP: "
        << m_Health
        << std::endl;


    // Quando a vida chega a zero ou abaixo disso,
    // o Player é marcado para destruição.
    //
    // A remoção efetiva não acontece imediatamente; o
    // EntityManager realiza essa etapa posteriormente.
    if (m_Health <= 0)
    {
        Destroy();
    }
}


//------------------------------------------------------------
// SetTargetPosition
//------------------------------------------------------------

void Player::SetTargetPosition(
    const sf::Vector2f& position)
{
    // Armazena a posição que será utilizada como alvo
    // de movimentação no próximo Update().
    m_TargetPosition = position;
}