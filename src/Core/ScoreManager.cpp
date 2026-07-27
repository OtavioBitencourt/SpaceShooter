#include "Core/ScoreManager.hpp"
#include <iostream>

ScoreManager::ScoreManager()
    : m_Score(0)
{
    if (!m_Font.openFromFile("assets/fonts/arial.ttf"))
    {
        std::cout << "Erro ao carregar fonte !" << std::endl;
    }        

    m_Text = std::make_unique<sf::Text>(m_Font, "Score: 0", 28);
    m_Text->setFillColor(sf::Color::White);
    m_Text->setPosition({20.f, 20.f});

    UpdateText();
}


void ScoreManager::UpdateText()
{
    m_Text->setString("Score: " + std::to_string(m_Score));
}



void ScoreManager::AddScore(int amount)
{
    m_Score += amount;
    UpdateText();
}



void ScoreManager::Reset()
{
    m_Score = 0;
    UpdateText();
}



int ScoreManager::GetScore() const
{
    return m_Score;
}



void ScoreManager::Render(sf::RenderWindow& window)
{
    if (m_Text)
    {
        window.draw(*m_Text);
    }
}

