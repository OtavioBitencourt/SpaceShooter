#pragma once

#include <string>

//============================================================
// CLASS_NAME
// -----------------------------------------------------------
// Macro utilizada pelas classes derivadas de Object para
// disponibilizar informações básicas sobre o nome da classe.
//
// Gera:
//
// - StaticClassName() → retorna o nome da classe sem depender
//   de uma instância.
//
// - GetClassName() → retorna o nome da classe através de uma
//   instância.
//
// Exemplo:
//
// CLASS_NAME(Entity)
//
// permite:
//
// Entity::StaticClassName()  -> "Entity"
// entity.GetClassName()      -> "Entity"
//============================================================

#define CLASS_NAME(name)                    \
public:                                     \
    static std::string StaticClassName()    \
    {                                       \
        return #name;                       \
    }                                       \
                                            \
    virtual std::string GetClassName() const\
    {                                       \
        return #name;                       \
    }


//============================================================
// Object
// -----------------------------------------------------------
// Classe base para objetos que precisam fornecer uma
// identificação textual de seu tipo.
//
// A classe fornece uma interface virtual para obtenção do nome
// da classe, permitindo que classes derivadas sobrescrevam esse
// comportamento.
//
// Também possui um destrutor virtual para garantir a destruição
// correta de objetos derivados através de ponteiros para Object.
//============================================================

class Object
{
public:

    // Destrutor virtual necessário para garantir a destruição
    // correta de objetos derivados através de um ponteiro Object.
    virtual ~Object() = default;


    // Retorna o nome da classe.
    //
    // Para Object, o nome padrão retornado é "Object".
    // Classes derivadas podem sobrescrever esse comportamento
    // utilizando o macro CLASS_NAME.
    virtual std::string GetClassName() const
    {
        return "Object";
    }
};