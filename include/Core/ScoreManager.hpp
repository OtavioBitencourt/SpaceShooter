#pragma once

#include <SFML/Graphics.hpp> 
#include <memory>

class ScoreManager
{
public:

    ScoreManager();

    void AddScore(int amount);

    int GetScore() const;

private:

    int m_Score;
};