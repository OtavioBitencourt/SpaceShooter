#include "Entities/Entity.hpp"


//============================================================
// Entity
// -----------------------------------------------------------
// Implementação dos comportamentos comuns fornecidos pela
// classe base das entidades.
//
// A classe Entity fornece principalmente o mecanismo de
// destruição diferida e comportamentos padrão utilizados
// quando uma entidade derivada não precisa sobrescrever
// determinado método.
//============================================================


//------------------------------------------------------------
// Destroy
//------------------------------------------------------------

void Entity::Destroy()
{
    // Marca a entidade para destruição.
    //
    // A entidade não é removida imediatamente. O EntityManager
    // verifica essa flag posteriormente durante sua etapa de
    // limpeza e então remove o objeto de forma segura.
    m_IsPendingDestroy = true;
}


//------------------------------------------------------------
// IsPendingDestroy
//------------------------------------------------------------

bool Entity::IsPendingDestroy() const
{
    // Informa se a entidade foi marcada para destruição.
    return m_IsPendingDestroy;
}


//------------------------------------------------------------
// OnCollision
//------------------------------------------------------------

void Entity::OnCollision(Entity*)
{
    // Implementação padrão vazia.
    //
    // Nem todas as entidades precisam reagir diretamente a uma
    // colisão. As classes derivadas podem sobrescrever este método
    // quando possuírem um comportamento específico.
}


//------------------------------------------------------------
// GetPosition
//------------------------------------------------------------

sf::Vector2f Entity::GetPosition() const
{
    // Retorna uma posição padrão.
    //
    // As entidades concretas normalmente sobrescrevem este método
    // para retornar sua posição real.
    return sf::Vector2f();
}


//------------------------------------------------------------
// GetRadius
//------------------------------------------------------------

float Entity::GetRadius() const
{
    // Retorna um raio padrão.
    //
    // As entidades concretas devem sobrescrever este método
    // quando participarem das verificações de colisão.
    return 0.f;
}