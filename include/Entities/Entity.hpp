#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Object.hpp"
#include "Entities/EntityType.hpp"

//============================================================
// Entity
// -----------------------------------------------------------
// Classe base abstrata para todas as entidades presentes no jogo.
//
// Uma Entity representa qualquer objeto do jogo que possua
// comportamento próprio, posição e possibilidade de interação
// com outras entidades.
//
// Exemplos:
// - Player
// - Enemy
// - Bullet
// - Asteroid
//
// A classe define uma interface comum para atualização,
// renderização, colisão, posição, tamanho e identificação
// do tipo da entidade.
//
// O EntityManager utiliza essa interface para armazenar e
// manipular diferentes tipos de entidades de forma polimórfica.
//
// Não é responsabilidade desta classe:
// - Controlar a criação das entidades.
// - Gerenciar o armazenamento das entidades.
// - Implementar comportamentos específicos de cada tipo.
//============================================================

class Entity : public Object
{
    CLASS_NAME(Entity)

public:

    // Destrutor virtual necessário para permitir a destruição
    // correta de objetos derivados através de um ponteiro Entity.
    virtual ~Entity() = default;


    // Atualiza o estado da entidade com base no tempo transcorrido
    // desde o último frame.
    //
    // Cada classe derivada deve implementar seu próprio comportamento.
    virtual void Update(float deltaTime) = 0;


    // Renderiza a entidade na janela informada.
    //
    // Cada classe derivada define como sua representação visual
    // deve ser desenhada.
    virtual void Render(sf::RenderWindow& window) = 0;


    // Trata uma colisão com outra entidade.
    //
    // A implementação padrão pode ser sobrescrita pelas classes
    // derivadas quando elas possuírem um comportamento específico
    // ao colidir.
    virtual void OnCollision(Entity* other);


    // Retorna a posição atual da entidade no mundo.
    virtual sf::Vector2f GetPosition() const;


    // Retorna o raio utilizado para representar aproximadamente
    // o tamanho da entidade nas verificações de colisão.
    virtual float GetRadius() const;


    // Retorna o tipo específico da entidade.
    //
    // O EntityManager utiliza essa informação para aplicar regras
    // específicas de colisão, pontuação e ciclo de vida.
    virtual EntityType GetType() const = 0;


    // Marca a entidade para ser destruída.
    //
    // A entidade não é removida imediatamente do armazenamento.
    // A remoção é realizada posteriormente pelo EntityManager
    // durante a etapa segura de limpeza.
    void Destroy();


    // Indica se a entidade foi marcada para destruição.
    bool IsPendingDestroy() const;


private:

    // Indica se a entidade está aguardando remoção pelo
    // EntityManager.
    bool m_IsPendingDestroy = false;
};