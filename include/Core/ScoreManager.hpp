#pragma once

#include <SFML/Graphics.hpp> 
#include <memory>

class ScoreManager
{
    public:
        ScoreManager();

        void AddScore(int amount);
        void Reset();

        int GetScore() const;

        void Render(sf::RenderWindow& window);

        
    
    private:
        void UpdateText();

        int m_Score;
        
        sf::Font m_Font;
        std::unique_ptr<sf::Text> m_Text;
};