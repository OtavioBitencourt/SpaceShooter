#include "Entities/Player.hpp"
#include "Utils/Math.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Core/EntityManager.hpp"

Player::Player(EntityManager* entityManager)
    : m_EntityManager(entityManager),
      m_Speed(400.f),
      m_ShootCooldown(0.1f),
      m_CurrentShootCooldown(0.f),
      m_AsteroidSpawnTimer(1.5f),
      m_CurrentAsteroidSpawnTimer(0.f)

{
    m_Shape.setPointCount(3);
    m_Shape.setRadius(30.f);

    m_Shape.setFillColor(sf::Color::Cyan);
    m_Shape.setOrigin({30.f, 30.f}); 
    m_Shape.setPosition({640.f, 360.f});

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    m_Forward = sf::Vector2f(0.f, -1.f);
}


void Player::Update(float deltaTime, const sf::Vector2f& targetPosition)
{
    sf::Vector2f currentPosition = m_Shape.getPosition(); 

    sf::Vector2f direction = targetPosition - currentPosition;

    float distance = Math::Length(direction); 

    if (distance > 5.f)
    {
        direction = Math::Normalize(direction); 

        m_Forward = direction; 

        m_Shape.move(direction * m_Speed * deltaTime);


        float angle = std::atan2(direction.y, direction.x);
        float angleDegress = angle * 180.f / 3.14159265f;
        m_Shape.setRotation(sf::degrees(angleDegress + 90.f));
    }



    m_CurrentShootCooldown -= deltaTime;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_CurrentShootCooldown <= 0.f)
    {
        m_EntityManager->SpawnBullet( m_Shape.getPosition(), m_Forward);

        m_CurrentShootCooldown = m_ShootCooldown;
    }



    //Asteroids

    m_CurrentAsteroidSpawnTimer -= deltaTime; //Atualiza o temporizador de spawn

    if (m_CurrentAsteroidSpawnTimer <= 0.f) 
    {

        int side = std::rand() % 4; //Escolhe uma borda aleatória

        sf::Vector2f spawnPosition;

        switch (side) 
        {
            //TOPO
            case 0: 
                spawnPosition = {static_cast<float>(std::rand() % 1280), -100.f};
                break; 

            
            //BAIXO
            case 1: 
                spawnPosition = {static_cast<float>(std::rand() % 1280), 820.f};
                break;


            //ESQUERDA
            case 2: 
                spawnPosition = {-100.f, static_cast<float>(std::rand() % 720)};
                break;

            //DIREITA
            case 3: 
                spawnPosition = {1380.f, static_cast<float>(std::rand() % 720)};
                break;
        }

        //Ponto aleatório da tela - direação do asteroide
        sf::Vector2f target (static_cast<float>(std::rand() % 1280), static_cast<float>(std::rand() % 720)); 

        //Vetor que aponta do spawn até o alvo
        sf::Vector2f direction = Math::Normalize(target - spawnPosition);

        //Cria o asteroide
        m_EntityManager->SpawnAsteroid(spawnPosition, direction);

        //Reinicia o temporizador
        m_CurrentAsteroidSpawnTimer = m_AsteroidSpawnTimer;
    }

   




    // for(size_t bulletIndex = 0; bulletIndex < m_Bullets.size(); bulletIndex++)
    // {
    //     for(size_t asteroidIndex = 0; asteroidIndex < m_Asteroids.size(); asteroidIndex++)
    //     {
    //         float distance = Math::Distance(m_Bullets[bulletIndex].GetPosition(), m_Asteroids[asteroidIndex].GetPosition());
    //         float radiusSum = m_Bullets[bulletIndex].GetRadius() + m_Asteroids[asteroidIndex].GetRadius();

    //         if (distance < radiusSum)
    //         {   
    //             m_Bullets.erase(m_Bullets.begin() + bulletIndex);
    //             m_Asteroids.erase(m_Asteroids.begin() + asteroidIndex);
                
    //             break;
    //         }
    //     }
    // }
}

void Player::Render(sf::RenderWindow& window)
{
    window.draw(m_Shape);

}