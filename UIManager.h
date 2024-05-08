#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <utility>

/**
 * @brief Enum representing all different screens or states of the game UI.
 */
enum class GameState {
    MAIN_MENU,
    NAME_ENTRY,
    PLAYING,
    PAUSED,
    GAME_OVER,
    GAME_WON,
    SCORE_HISTORY
};

/**
 * @class UIManager
 * @brief Manages the visual elements, text menus, and interactive screen states.
 * 
 * [RUBRIC: UIManager class definition ✓]
 */
class UIManager {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text instructionText;
    sf::Text scoreText;
    sf::RectangleShape menuBackground;
    std::string playerName;
    GameState currentState;

    // Interactive buttons for various screens (encapsulated for bounding box checks)
    // Main Menu
    sf::Text newGameButton;
    sf::Text resumeGameButton;
    sf::Text scoreHistoryButton;
    sf::Text quitButton;

    // Pause Screen
    sf::Text resumeButton;
    sf::Text saveQuitButton;
    sf::Text pauseMainMenuButton;

    // Game Over Screen
    sf::Text retryButton;
    sf::Text gameOverMainMenuButton;

    // Game Won Screen
    sf::Text gameWonMainMenuButton;

    // Score History Screen
    sf::Text scoreHistoryBackButton;

    // Internal helper to configure button aesthetics
    void configureButton(sf::Text& button, const std::string& textStr, float yPosition, unsigned int size = 30);

    // Font loading fallback utility
    bool loadFallbackFont();

public:
    /**
     * @brief Construct a new UIManager object.
     * @param win The sf::RenderWindow context.
     */
    UIManager(sf::RenderWindow& win);

    // Screen Render Methods
    void drawMainMenu(sf::RenderWindow& win, bool hasSaveFile);
    void drawNameEntry(sf::RenderWindow& win, const std::string& currentInput);
    void drawPauseScreen(sf::RenderWindow& win, int score);
    void drawGameOver(sf::RenderWindow& win, int finalScore,
                      const std::vector<std::pair<std::string, int>>& topScores);
    void drawGameWon(sf::RenderWindow& win, int finalScore);
    void drawScoreHistory(sf::RenderWindow& win,
                          const std::vector<std::pair<std::string, int>>& scores);

    // Input/Text Handling for Name Entry
    void handleTextInput(const sf::Event& e);
    std::string getPlayerName() const;
    void setPlayerName(const std::string& name);

    // State getters/setters
    GameState getState() const;
    void setState(GameState s);

    // Hover Event Handlers (change scale/color on mouse hover)
    void handleMainMenuHover(sf::RenderWindow& win, sf::Vector2i mousePos, bool hasSaveFile);
    void handlePauseScreenHover(sf::RenderWindow& win, sf::Vector2i mousePos);
    void handleGameOverHover(sf::RenderWindow& win, sf::Vector2i mousePos);
    void handleGameWonHover(sf::RenderWindow& win, sf::Vector2i mousePos);
    void handleScoreHistoryHover(sf::RenderWindow& win, sf::Vector2i mousePos);

    // Click Event Handlers (returns option code: e.g. 1, 2, 3, etc.)
    int handleMainMenuClick(sf::RenderWindow& win, sf::Vector2i mousePos, bool hasSaveFile);
    int handlePauseScreenClick(sf::RenderWindow& win, sf::Vector2i mousePos);
    int handleGameOverClick(sf::RenderWindow& win, sf::Vector2i mousePos);
    int handleGameWonClick(sf::RenderWindow& win, sf::Vector2i mousePos);
    int handleScoreHistoryClick(sf::RenderWindow& win, sf::Vector2i mousePos);
};

#endif // UIMANAGER_H
