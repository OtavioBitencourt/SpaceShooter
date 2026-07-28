#include "Core/HUDManager.hpp"
#include <iostream>

HUDManager::HUDManager()
    : m_Score(0)
{
}

bool HUDManager::Initialize()
{
    if (!m_Font.openFromFile("assets/fonts/arial.ttf"))
    {
        std::cout << "Erro ao carregar fonte! " << std::endl;
        return false;
    }

    CreateText("Score", "Score: 0", {15.f, 15.f});

    return true;
}



void HUDManager::CreateText(const std::string& id, const std::string& text, const sf::Vector2f& position, unsigned int characterSize)
{
   auto newText = std::make_unique<sf::Text>(m_Font, text, characterSize);

   newText->setPosition(position);

   m_Texts[id] = std::move(newText);
}



void HUDManager::SetScore(int score)
{
    if(score == m_Score)
    {
        return;
    }
    
    m_Score = score;
    
    SetText("Score", "Score: " + std::to_string(m_Score));

}


void HUDManager::SetText(const std::string& id, const std::string& text)
{
    auto it = m_Texts.find(id);

    if (it == m_Texts.end())
    {
        return;
    }

    it->second->setString(text);
}


void HUDManager::Render(sf::RenderWindow& window)
{
   for (const auto& [id, text] : m_Texts)
   {
        window.draw(*text);
   }
}

