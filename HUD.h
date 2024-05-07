#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class HUD
 * @brief HUD overlay displaying Score, Name, Roll number, High Score, Level, and Lives at the top.
 */
class HUD {
private:
    sf::Font font;            ///< Font asset
    sf::Text scoreText;       ///< "Score: XXXX"
    sf::Text nameText;        ///< "Player: Name"
    sf::Text rollNumText;     ///< "Roll: 23XXXXX-X"
    sf::Text highScoreText;   ///< "High: XXXX"
    sf::Text levelText;       ///< "Level: X"
    sf::Text livesText;       ///< "Lives: X"
    std::string rollNumber;   ///< User's roll number
    std::string playerName;   ///< User's name

public:
    /**
     * @brief Construct a new HUD object.
     * @param rollNum Player's roll number.
     * @param name Player's name.
     */
    HUD(const std::string& rollNum, const std::string& name);

    /**
     * @brief Update the HUD text fields.
     * @param score Current player score.
     * @param highScore Current high score.
     * @param level Current level index.
     * @param lives Remaining lives.
     */
    void update(int score, int highScore, int level, int lives);

    /**
     * @brief Render the HUD overlay to the window.
     * @param win sf::RenderWindow to draw to.
     */
    void draw(sf::RenderWindow& win);
};

#endif // HUD_H
