#include "Entities/Asteroid.hpp"
#include "Entities/IDamageable.hpp"




//============================================================
// Asteroid
// -----------------------------------------------------------
// Implementação responsável pelo movimento, renderização e
// comportamento de colisão dos asteroides.
//============================================================


//------------------------------------------------------------
// Construtor
//------------------------------------------------------------

Asteroid::Asteroid(
    const sf::Vector2f& position,
    const sf::Vector2f& direction)
    : m_Direction(direction),
      m_Speed(250.f)
{
    // Define o tamanho do asteroide.
    m_Shape.setRadius(40.f);

    // Utiliza oito pontos para aproximar visualmente um
    // formato de asteroide.
    m_Shape.setPointCount(10);

    // Define a cor utilizada para representar o asteroide.
    m_Shape.setFillColor(
        sf::Color(110, 110, 110));

    // Centraliza a origem da forma para facilitar o
    // posicionamento.
    m_Shape.setOrigin({40.f, 40.f});

    // Posiciona o asteroide no ponto inicial informado.
    m_Shape.setPosition(position);

    // Adiciona um contorno para destacar visualmente o asteroide.
    m_Shape.setOutlineThickness(3.f);

    // Define a cor do contorno utilizada para aumentar a percepção
    // de profundidade e separação do fundo.
    m_Shape.setOutlineColor(sf::Color(170, 170, 170));
}


//------------------------------------------------------------
// Update
//------------------------------------------------------------

void Asteroid::Update(float deltaTime)
{
    // Move o asteroide utilizando sua direção, velocidade
    // e o tempo transcorrido desde o último frame.
    //
    // O uso de deltaTime mantém a velocidade independente
    // da taxa de frames.
    m_Shape.move(
        m_Direction *
        m_Speed *
        deltaTime);
}


//------------------------------------------------------------
// Render
//------------------------------------------------------------

void Asteroid::Render(sf::RenderWindow& window)
{
    // Desenha o asteroide na janela.
    window.draw(m_Shape);
}


//------------------------------------------------------------
// GetPosition
//------------------------------------------------------------

sf::Vector2f Asteroid::GetPosition() const
{
    // Retorna a posição atual do asteroide.
    return m_Shape.getPosition();
}


//------------------------------------------------------------
// GetRadius
//------------------------------------------------------------

float Asteroid::GetRadius() const
{
    // Retorna o raio utilizado nas verificações de colisão.
    return m_Shape.getRadius();
}


//------------------------------------------------------------
// OnCollision
//------------------------------------------------------------

void Asteroid::OnCollision(Entity* other)
{
    // Verifica se a entidade atingida implementa
    // IDamageable.
    //
    // Dessa forma, o Asteroid pode causar dano sem conhecer
    // diretamente a classe concreta da entidade atingida.
    IDamageable* damageable =
        dynamic_cast<IDamageable*>(other);


    if (damageable != nullptr)
    {
        // Aplica 5 pontos de dano à entidade atingida.
        //
        // A própria entidade decide como esse dano será
        // processado internamente.
        damageable->TakeDamage(5);
    }


    // Após a colisão, o asteroide é marcado para destruição.
    //
    // A remoção efetiva será realizada posteriormente pelo
    // EntityManager.
    Destroy();
}


//------------------------------------------------------------
// GetType
//------------------------------------------------------------

EntityType Asteroid::GetType() const
{
    // Retorna o tipo utilizado pelo EntityManager para
    // identificar esta entidade como Asteroid.
    return EntityType::Asteroid;
}