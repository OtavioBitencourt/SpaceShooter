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

    CreateText("Score", "Score", {15.f, 15.f});
    CreateText("Health", "Vida", {15.f, 45.f});
    CreateText("Time", "Tempo", {15.f, 75.f});
    CreateText("Enemies", "Inimigos", {15.f, 105.f});
    CreateText("Wave", "Wave", {15.f, 135.f});

    return true;
}



void HUDManager::CreateText(const std::string& id, const std::string& label, const sf::Vector2f& position, unsigned int characterSize)
{
   HUDItem item;

   item.Label = label;
   item.Text = std::make_unique<sf::Text>(m_Font, label + ": 0", characterSize);
   item.Text->setPosition(position);

   m_Texts[id] = std::move(item);
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

    it->second.Text->setString(text);
}



void HUDManager::SetValue(const std::string& id, int value)
{
    auto it = m_Texts.find(id);

    if (it == m_Texts.end())
    {
        return;
    }

    it->second.Text->setString(it->second.Label + ": " + std::to_string(value));
}



void HUDManager::Render(sf::RenderWindow& window)
{
   for (const auto& [id, item] : m_Texts)
   {
        window.draw(*item.Text);
   }
}

