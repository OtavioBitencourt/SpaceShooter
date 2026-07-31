#include "Entities/Bullet.hpp"
#include "Entities/IDamageable.hpp"
#include "Entities/EntityType.hpp"




//============================================================
// Bullet
// -----------------------------------------------------------
// Implementação responsável pelo movimento, renderização e
// comportamento de colisão dos projéteis.
//============================================================


//------------------------------------------------------------
// Construtor
//------------------------------------------------------------

Bullet::Bullet(
    const sf::Vector2f& position,
    const sf::Vector2f& direction)
    : m_Direction(direction),
      m_Speed(1000.f)
{
    // Define o tamanho visual do projétil.
    m_Shape.setRadius(5.f);

    // Define a cor utilizada para representar o projétil.
    m_Shape.setFillColor(sf::Color::Red);

    // Centraliza a origem da forma para facilitar o posicionamento.
    m_Shape.setOrigin({5.f, 5.f});

    // Posiciona o projétil no ponto de origem informado.
    m_Shape.setPosition(position);
}


//------------------------------------------------------------
// Update
//------------------------------------------------------------

void Bullet::Update(float deltaTime)
{
    // Move o projétil de acordo com sua direção, velocidade
    // e tempo transcorrido desde o último frame.
    //
    // O uso de deltaTime mantém o movimento independente
    // da taxa de frames.
    m_Shape.move(
        m_Direction *
        m_Speed *
        deltaTime);
}


//------------------------------------------------------------
// Render
//------------------------------------------------------------

void Bullet::Render(sf::RenderWindow& window)
{
    // Desenha o projétil na janela.
    window.draw(m_Shape);
}


//------------------------------------------------------------
// GetPosition
//------------------------------------------------------------

sf::Vector2f Bullet::GetPosition() const
{
    // Retorna a posição atual do projétil.
    return m_Shape.getPosition();
}


//------------------------------------------------------------
// GetRadius
//------------------------------------------------------------

float Bullet::GetRadius() const
{
    // Retorna o raio utilizado nas verificações de colisão.
    return m_Shape.getRadius();
}


//------------------------------------------------------------
// OnCollision
//------------------------------------------------------------

void Bullet::OnCollision(Entity* other)
{
    // Asteroides não implementam IDamageable atualmente.
    // Portanto, sua destruição é tratada diretamente quando
    // o projétil colide com um deles.
    if (other->GetType() == EntityType::Asteroid)
    {
        other->Destroy();
    }


    // Tenta verificar se a entidade atingida implementa
    // a interface IDamageable.
    //
    // Isso permite que a Bullet aplique dano sem precisar
    // conhecer diretamente a classe concreta da entidade.
    IDamageable* damageable =
        dynamic_cast<IDamageable*>(other);


    if (damageable != nullptr)
    {
        // Aplica 25 pontos de dano à entidade atingida.
        //
        // A própria entidade decide como esse dano afeta
        // sua vida e se deve ser destruída.
        damageable->TakeDamage(25);
    }


    // Independentemente do tipo de entidade atingida,
    // o projétil é destruído após a colisão.
    Destroy();
}


//------------------------------------------------------------
// GetType
//------------------------------------------------------------

EntityType Bullet::GetType() const
{
    // Retorna o tipo utilizado pelo EntityManager para
    // identificar esta entidade como Bullet.
    return EntityType::Bullet;
}