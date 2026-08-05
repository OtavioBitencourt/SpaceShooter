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

namespace
{
    constexpr float BODY_HEIGHT = 30.f;
    constexpr float BODY_HALF_WIDTH = 20.f;

    constexpr float COCKPIT_RADIUS = 8.f;

    constexpr sf::Vector2f PLAYER_START_POSITION = { 640.f, 360.f };
}




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
    // Inicializa a forma visual do Player.
    InitializeShape();


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
        m_Body.getPosition();

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
        m_Body.move(
            direction * m_Speed * deltaTime);
            
        // Atualiza a rotação da nave para que ela aponte
        // na direção do alvo.
        UpdateRotation(direction);
    
        // Repociona todas as peças da nave de acordo 
        // com a nova posição e rotação.
        UpdatePartsPosition();
            
            
    }


    //--------------------------------------------------------
    // Controle do disparo
    //--------------------------------------------------------

    // Reduz o tempo restante do cooldown do disparo.
    m_CurrentShootCooldown -= deltaTime;

    // Executa a lógica de disparo, caso o jogador esteja pressionando
    // o botão esquerdo do mouse e o cooldown tenha terminado.
    Shoot();


   
}


//------------------------------------------------------------
// Render
//------------------------------------------------------------

void Player::Render(sf::RenderWindow& window)
{

    window.draw(m_LeftWing);
    window.draw(m_RightWing);

    window.draw(m_Body);
    window.draw(m_Cockpit);

    window.draw(m_LeftEngine);
    window.draw(m_RightEngine);

    window.draw(m_Flame);
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
    return m_Body.getPosition();
}


//------------------------------------------------------------
// GetRadius
//------------------------------------------------------------

float Player::GetRadius() const
{
    // Retorna um raio aproximado utilizado nas verificações
    // de colisão da nave.
    return 30.f;
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



//------------------------------------------------------------
// InitializeShape
//------------------------------------------------------------

void Player::InitializeShape()
{
  
   InitializeBody();
   InitializeCockpit();
   InitializeWings();
   InitializeEngines();
   InitializeFlame();

   UpdatePartsPosition();
}



//------------------------------------------------------------
// UpdateRotation
//------------------------------------------------------------

void Player::UpdateRotation(const sf::Vector2f& direction)
{
  
    // Calcula o ângulo da direção atual em radianos.
    float angle =
    std::atan2(direction.y, direction.x);


    // Converte o ângulo de radianos para graus para utilizar
    // na API de rotação da SFML.
    float angleDegress = angle * 180.f / 3.14159265f;


    // Rotaciona a nave para que ela aponte na direção do alvo.
    //
    // O deslocamento de 90 graus compensa a orientação
    // inicial do triângulo.
    m_Body.setRotation(sf::degrees(angleDegress + 90.f));
}


//------------------------------------------------------------
// Shoot
//------------------------------------------------------------

void Player::Shoot()
{
    // Permite disparar somente quando o botão esquerdo do mouse
    // estiver pressionado e o cooldown tiver terminado.
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
        m_CurrentShootCooldown <= 0.f)
    {
        // Solicita ao EntityManager a criação de um projétil
        // na posição atual do Player e utilizando sua direção
        // atual como direção inicial da bala.
        m_EntityManager->SpawnBullet(
            m_Body.getPosition(),
            m_Forward);


        // Reinicia o cooldown até que um novo disparo seja permitido.
        m_CurrentShootCooldown = m_ShootCooldown;
    }
}


//------------------------------------------------------------
// RotateOffset
//------------------------------------------------------------
sf::Vector2f Player::RotateOffset(const sf::Vector2f& offset) const
{
    float angle = m_Body.getRotation().asRadians();

    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);

    return 
    {
        offset.x * cosAngle - offset.y * sinAngle, 
        offset.x * sinAngle + offset.y * cosAngle
    };
}


//------------------------------------------------------------
// UpdatePartsPosition
//------------------------------------------------------------

void Player::UpdatePartsPosition()
{
    sf::Vector2f position = m_Body.getPosition();
    sf::Angle rotation = m_Body.getRotation();

    m_Cockpit.setPosition(position + RotateOffset({0.f, -18.f}));

    m_LeftWing.setPosition(position + RotateOffset({-18.f, 4.f}));
    m_RightWing.setPosition(position + RotateOffset({18.f, 4.f}));

    m_LeftEngine.setPosition(position + RotateOffset({-9.f, 22.f}));
    m_RightEngine.setPosition(position + RotateOffset({9.f, 22.f}));

    m_Flame.setPosition(position + RotateOffset({0.f, 35.f}));

    m_Cockpit.setRotation(rotation);
    m_LeftWing.setRotation(rotation);
    m_RightWing.setRotation(rotation);
    m_LeftEngine.setRotation(rotation);
    m_RightEngine.setRotation(rotation);
    m_Flame.setRotation(rotation);
}


//------------------------------------------------------------
// InitializeBody
//------------------------------------------------------------
void Player::InitializeBody()
{
    m_Body.setPointCount(3);

    // Triângulo apontando para cima.
    m_Body.setPoint(0, { 0.f, -BODY_HEIGHT });
    m_Body.setPoint(1, { -BODY_HALF_WIDTH, 20.f });
    m_Body.setPoint(2, { BODY_HALF_WIDTH, 20.f });

    m_Body.setFillColor(sf::Color(40, 170, 255));

    // Contorno metálico.
    m_Body.setOutlineThickness(3.f);
    m_Body.setOutlineColor(sf::Color(170, 170, 170));

    m_Body.setOrigin({0.f, 0.f});
    m_Body.setPosition({640.f, 360.f});
}



//------------------------------------------------------------
// InitializeCockpit
//------------------------------------------------------------
void Player::InitializeCockpit()
{
    m_Cockpit.setRadius(8.f);
    m_Cockpit.setFillColor(sf::Color(180, 240, 255));
    m_Cockpit.setOrigin({8.f, 8.f});
}



//------------------------------------------------------------
// InitializeWings
//------------------------------------------------------------
void Player::InitializeWings()
{
    m_LeftWing.setSize({12.f, 28.f});
    m_RightWing.setSize({12.f, 28.f});

    m_LeftWing.setFillColor(sf::Color(90, 90, 90));
    m_RightWing.setFillColor(sf::Color(90, 90, 90));

    m_LeftWing.setOrigin({6.f, 14.f});
    m_RightWing.setOrigin({6.f, 14.f});


}



//------------------------------------------------------------
// InitializeEngines
//------------------------------------------------------------
void Player::InitializeEngines()
{
    m_LeftEngine.setSize({8.f, 12.f});
    m_RightEngine.setSize({8.f, 12.f});

    m_LeftEngine.setFillColor(sf::Color(60, 60, 60));
    m_RightEngine.setFillColor(sf::Color(60, 60, 60));

    m_LeftEngine.setOrigin({4.f, 6.f});
    m_RightEngine.setOrigin({4.f, 6.f});
}



//------------------------------------------------------------
// InitializeFlame
//------------------------------------------------------------
void Player::InitializeFlame()
{
    m_Flame.setPointCount(3);

    m_Flame.setPoint(0, { 0.f, 12.f });
    m_Flame.setPoint(1, { -6.f, 0.f });
    m_Flame.setPoint(2, { 6.f, 0.f });

    m_Flame.setFillColor(sf::Color(255, 120, 20));

    m_Flame.setOrigin({0.f, 0.f});
}