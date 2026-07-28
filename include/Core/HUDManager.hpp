#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <memory>
#include <string>

class HUDManager
{
    public:
        HUDManager();

        bool Initialize();
        void SetScore(int score);
        void Render(sf::RenderWindow& window);
        void CreateText(const std::string& id, const std::string& text, const sf::Vector2f& position, unsigned int characterSize = 24);
        void SetText(const std::string& id, const std::string& text);

    
    private: 
        sf::Font m_Font;
        std::unordered_map<std::string, std::unique_ptr<sf::Text>> m_Texts;

        int m_Score;
};