#pragma once

#include <SFML/System/Vector2.hpp>

#include <cmath>

//============================================================
// Math
// -----------------------------------------------------------
// Namespace que reúne funções matemáticas auxiliares utilizadas
// pelo jogo para trabalhar com vetores e cálculos espaciais.
//
// As funções são implementadas como inline porque são pequenas,
// independentes de estado e podem ser utilizadas diretamente a
// partir do header.
//
// Funções disponíveis:
// - Length()      → calcula o comprimento de um vetor.
// - Normalize()   → transforma um vetor em um vetor unitário.
// - Distance()    → calcula a distância entre dois pontos.
// - MoveTowards() → movimenta um ponto em direção a um alvo.
//
// Essas funções são utilizadas principalmente para movimentação,
// direção e cálculos relacionados ao espaço do jogo.
//============================================================

namespace Math
{
    // Retorna o comprimento (magnitude) do vetor informado.
    //
    // Para um vetor (x, y), o comprimento é calculado a partir
    // da distância desse vetor até a origem.
    inline float Length(const sf::Vector2f& vector)
    {
        return std::sqrt(
            vector.x * vector.x +
            vector.y * vector.y);
    }


    // Retorna o vetor normalizado, mantendo sua direção e
    // fazendo com que seu comprimento seja igual a 1.
    //
    // Caso o vetor tenha comprimento zero, retorna um vetor
    // nulo para evitar divisão por zero.
    inline sf::Vector2f Normalize(const sf::Vector2f& vector)
    {
        float length = Length(vector);

        if (length == 0.f)
        {
            return {};
        }

        return vector / length;
    }


    // Retorna a distância entre dois pontos no espaço 2D.
    inline float Distance(
        const sf::Vector2f& a,
        const sf::Vector2f& b)
    {
        return Length(b - a);
    }


    // Move um ponto atual em direção a um ponto alvo,
    // respeitando a velocidade e o tempo transcorrido.
    //
    // O deslocamento é calculado a partir da direção entre
    // current e target, multiplicada pela velocidade e pelo
    // deltaTime.
    inline sf::Vector2f MoveTowards(
        const sf::Vector2f& current,
        const sf::Vector2f& target,
        float speed,
        float deltaTime)
    {
        sf::Vector2f direction = target - current;

        direction = Normalize(direction);

        return current + direction * speed * deltaTime;
    }
}