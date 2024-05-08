#include "UIManager.h"
#include <iostream>

UIManager::UIManager(sf::RenderWindow& win)
    : currentState(GameState::MAIN_MENU),
      playerName("") {
    
    // Load font with fallback chain (SFML 2.x uses loadFromFile)
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/calibri.ttf")) {
            if (!font.loadFromFile("C:/Windows/Fonts/segoeui.ttf")) {
                if (!font.loadFromFile("C:/Windows/Fonts/cour.ttf")) {
                    std::cerr << "[WARNING]: All standard Windows fonts failed to load. Text rendering will fail!\n";
                }
            }
        }
    }

    // Set fonts for all text elements
    titleText.setFont(font);
    instructionText.setFont(font);
    scoreText.setFont(font);
    newGameButton.setFont(font);
    resumeGameButton.setFont(font);
    scoreHistoryButton.setFont(font);
    quitButton.setFont(font);
    resumeButton.setFont(font);
    saveQuitButton.setFont(font);
    pauseMainMenuButton.setFont(font);
    retryButton.setFont(font);
    gameOverMainMenuButton.setFont(font);
    gameWonMainMenuButton.setFont(font);
    scoreHistoryBackButton.setFont(font);

    // Set up title configuration
    titleText.setCharacterSize(65);
    titleText.setFillColor(sf::Color(0, 229, 255)); // Neon Cyan
    titleText.setStyle(sf::Text::Bold);

    // Instruction text setup
    instructionText.setCharacterSize(22);
    instructionText.setFillColor(sf::Color(200, 200, 200));

    // Score text setup
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color(255, 215, 0)); // Gold

    // Semi-transparent menu card background (for menu screen overlays)
    menuBackground.setSize(sf::Vector2f(500.f, 480.f));
    menuBackground.setFillColor(sf::Color(15, 15, 18, 230)); // Glassmorphism Dark
    menuBackground.setOutlineColor(sf::Color(0, 229, 255, 100)); // Faded Cyan Outline
    menuBackground.setOutlineThickness(2.f);
    
    // Center it on the 800x640 screen
    menuBackground.setOrigin(sf::Vector2f(250.f, 240.f));
    menuBackground.setPosition(sf::Vector2f(400.f, 320.f));

    // Initialize all button coordinates and labels
    configureButton(newGameButton, "[1] New Game", 280.f);
    configureButton(resumeGameButton, "[2] Resume Game", 350.f);
    configureButton(scoreHistoryButton, "[3] Score History", 420.f);
    configureButton(quitButton, "[4] Quit", 490.f);

    configureButton(resumeButton, "Resume Game", 280.f);
    configureButton(saveQuitButton, "Save & Quit", 350.f);
    configureButton(pauseMainMenuButton, "Main Menu", 420.f);

    configureButton(retryButton, "Retry Level", 480.f);
    configureButton(gameOverMainMenuButton, "Main Menu", 540.f);

    configureButton(gameWonMainMenuButton, "Main Menu", 440.f);

    configureButton(scoreHistoryBackButton, "Back to Main Menu", 560.f, 25);
}

void UIManager::configureButton(sf::Text& button, const std::string& textStr, float yPosition, unsigned int size) {
    button.setString(textStr);
    button.setCharacterSize(size);
    button.setFillColor(sf::Color::White);
    
    sf::FloatRect bounds = button.getLocalBounds();
    button.setOrigin(sf::Vector2f(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f));
    button.setPosition(sf::Vector2f(400.f, yPosition));
}

void UIManager::drawMainMenu(sf::RenderWindow& win, bool hasSaveFile) {
    win.clear(sf::Color(10, 10, 12)); // Very dark grey, almost black

    // Draw card background
    win.draw(menuBackground);

    // Set title and draw centered
    titleText.setString("ARKADROID");
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f));
    titleText.setPosition(sf::Vector2f(400.f, 150.f));
    win.draw(titleText);

    // Draw buttons
    win.draw(newGameButton);
    
    // Grey out resume button if no save exists
    if (hasSaveFile) {
        resumeGameButton.setFillColor(resumeGameButton.getFillColor()); // keep hovered/active color
    } else {
        resumeGameButton.setFillColor(sf::Color(80, 80, 80)); // Disabled grey
    }
    win.draw(resumeGameButton);
    win.draw(scoreHistoryButton);
    win.draw(quitButton);

    win.display();
}

void UIManager::drawNameEntry(sf::RenderWindow& win, const std::string& currentInput) {
    win.clear(sf::Color(10, 10, 12));

    win.draw(menuBackground);

    titleText.setString("PLAYER NAME");
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f));
    titleText.setPosition(sf::Vector2f(400.f, 150.f));
    win.draw(titleText);

    instructionText.setString("ENTER YOUR NAME:");
    sf::FloatRect insBounds = instructionText.getLocalBounds();
    instructionText.setOrigin(sf::Vector2f(insBounds.left + insBounds.width / 2.f, insBounds.top + insBounds.height / 2.f));
    instructionText.setPosition(sf::Vector2f(400.f, 260.f));
    win.draw(instructionText);

    // Name text display (neon yellow/gold)
    sf::Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(35);
    nameText.setFillColor(sf::Color(255, 215, 0));
    nameText.setString(currentInput + "_");
    nameText.setStyle(sf::Text::Bold);
    
    sf::FloatRect nameBounds = nameText.getLocalBounds();
    nameText.setOrigin(sf::Vector2f(nameBounds.left + nameBounds.width / 2.f, nameBounds.top + nameBounds.height / 2.f));
    nameText.setPosition(sf::Vector2f(400.f, 350.f));
    
    // Typable field box
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(360.f, 60.f));
    box.setFillColor(sf::Color(30, 30, 35));
    box.setOutlineColor(sf::Color(255, 215, 0, 100));
    box.setOutlineThickness(1.f);
    box.setOrigin(sf::Vector2f(180.f, 30.f));
    box.setPosition(sf::Vector2f(400.f, 350.f));

    win.draw(box);
    win.draw(nameText);

    instructionText.setString("Press ENTER to Start");
    instructionText.setFillColor(sf::Color(150, 150, 150));
    sf::FloatRect insBounds2 = instructionText.getLocalBounds();
    instructionText.setOrigin(sf::Vector2f(insBounds2.left + insBounds2.width / 2.f, insBounds2.top + insBounds2.height / 2.f));
    instructionText.setPosition(sf::Vector2f(400.f, 440.f));
    win.draw(instructionText);

    win.display();
}

void UIManager::drawPauseScreen(sf::RenderWindow& win, int score) {
    // Draws over the current active gameplay screen as an overlay, semi-transparent background
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y)));
    overlay.setFillColor(sf::Color(10, 10, 12, 180)); // Semi-transparent overlay
    win.draw(overlay);

    win.draw(menuBackground);

    titleText.setString("PAUSED");
    titleText.setFillColor(sf::Color(255, 215, 0)); // Gold
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f));
    titleText.setPosition(sf::Vector2f(400.f, 150.f));
    win.draw(titleText);

    // Draw buttons
    win.draw(resumeButton);
    win.draw(saveQuitButton);
    win.draw(pauseMainMenuButton);
}

void UIManager::drawGameOver(sf::RenderWindow& win, int finalScore,
                              const std::vector<std::pair<std::string, int>>& topScores) {
    win.clear(sf::Color(15, 5, 5)); // Dark Red Hue background

    // Center card
    sf::RectangleShape card(menuBackground);
    card.setSize(sf::Vector2f(550.f, 540.f));
    card.setOrigin(sf::Vector2f(275.f, 270.f));
    card.setOutlineColor(sf::Color(255, 87, 34, 150)); // Red-Orange border
    win.draw(card);

    titleText.setString("GAME OVER");
    titleText.setFillColor(sf::Color(255, 87, 34)); // Coral Red
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f));
    titleText.setPosition(sf::Vector2f(400.f, 120.f));
    win.draw(titleText);

    scoreText.setString("Final Score: " + std::to_string(finalScore));
    scoreText.setFillColor(sf::Color(255, 215, 0));
    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(sf::Vector2f(scoreBounds.left + scoreBounds.width / 2.f, scoreBounds.top + scoreBounds.height / 2.f));
    scoreText.setPosition(sf::Vector2f(400.f, 190.f));
    win.draw(scoreText);

    // Render local top 5 scoreboard
    sf::Text tableHeader;
    tableHeader.setFont(font);
    tableHeader.setCharacterSize(20);
    tableHeader.setFillColor(sf::Color(200, 200, 200));
    tableHeader.setStyle(sf::Text::Underlined);
    tableHeader.setString("TOP 5 HIGH SCORES:");
    sf::FloatRect headBounds = tableHeader.getLocalBounds();
    tableHeader.setOrigin(sf::Vector2f(headBounds.left + headBounds.width / 2.f, headBounds.top + headBounds.height / 2.f));
    tableHeader.setPosition(sf::Vector2f(400.f, 240.f));
    win.draw(tableHeader);

    for (size_t i = 0; i < 5 && i < topScores.size(); ++i) {
        sf::Text rowText;
        rowText.setFont(font);
        rowText.setCharacterSize(18);
        rowText.setFillColor(sf::Color(220, 220, 220));
        
        std::string row = std::to_string(i + 1) + ". " + topScores[i].first;
        rowText.setString(row);
        rowText.setPosition(sf::Vector2f(250.f, 280.f + i * 30.f));
        win.draw(rowText);

        sf::Text rowScore;
        rowScore.setFont(font);
        rowScore.setCharacterSize(18);
        rowScore.setFillColor(sf::Color(255, 215, 0));
        rowScore.setString(std::to_string(topScores[i].second));
        // Align right
        sf::FloatRect rowScoreBounds = rowScore.getLocalBounds();
        rowScore.setOrigin(sf::Vector2f(rowScoreBounds.width, 0.f));
        rowScore.setPosition(sf::Vector2f(550.f, 280.f + i * 30.f));
        win.draw(rowScore);
    }

    win.draw(retryButton);
    win.draw(gameOverMainMenuButton);

    win.display();
}

void UIManager::drawGameWon(sf::RenderWindow& win, int finalScore) {
    win.clear(sf::Color(5, 15, 5)); // Dark Green Hue background

    win.draw(menuBackground);

    titleText.setString("VICTORY!");
    titleText.setFillColor(sf::Color(0, 230, 118)); // Bright Green
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f));
    titleText.setPosition(sf::Vector2f(400.f, 150.f));
    win.draw(titleText);

    scoreText.setString("Final Score: " + std::to_string(finalScore));
    scoreText.setFillColor(sf::Color(255, 215, 0));
    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(sf::Vector2f(scoreBounds.left + scoreBounds.width / 2.f, scoreBounds.top + scoreBounds.height / 2.f));
    scoreText.setPosition(sf::Vector2f(400.f, 260.f));
    win.draw(scoreText);

    // Winner text
    instructionText.setString("CONGRATULATIONS!");
    instructionText.setFillColor(sf::Color(255, 215, 0));
    sf::FloatRect insBounds = instructionText.getLocalBounds();
    instructionText.setOrigin(sf::Vector2f(insBounds.left + insBounds.width / 2.f, insBounds.top + insBounds.height / 2.f));
    instructionText.setPosition(sf::Vector2f(400.f, 330.f));
    win.draw(instructionText);

    win.draw(gameWonMainMenuButton);

    win.display();
}

void UIManager::drawScoreHistory(sf::RenderWindow& win,
                                  const std::vector<std::pair<std::string, int>>& scores) {
    win.clear(sf::Color(10, 10, 12));

    // Draw wide card for history
    sf::RectangleShape wideCard(menuBackground);
    wideCard.setSize(sf::Vector2f(720.f, 540.f));
    wideCard.setOrigin(sf::Vector2f(360.f, 270.f));
    wideCard.setPosition(sf::Vector2f(400.f, 300.f));
    win.draw(wideCard);

    titleText.setString("SCORE HISTORY");
    titleText.setFillColor(sf::Color(0, 229, 255));
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f));
    titleText.setPosition(sf::Vector2f(400.f, 80.f));
    win.draw(titleText);

    // List headers
    sf::Text header;
    header.setFont(font);
    header.setCharacterSize(18);
    header.setFillColor(sf::Color(200, 200, 200));
    header.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    header.setString("Rank");
    header.setPosition(sf::Vector2f(80.f, 150.f));
    win.draw(header);

    header.setString("Name");
    header.setPosition(sf::Vector2f(200.f, 150.f));
    win.draw(header);

    header.setString("Score");
    header.setPosition(sf::Vector2f(420.f, 150.f));
    win.draw(header);

    // Display scrollable list (first 10 records)
    for (size_t i = 0; i < 10 && i < scores.size(); ++i) {
        float y = 190.f + i * 32.f;

        sf::Text rowText;
        rowText.setFont(font);
        rowText.setCharacterSize(16);
        rowText.setFillColor(sf::Color(220, 220, 220));

        // Rank
        rowText.setString(std::to_string(i + 1));
        rowText.setPosition(sf::Vector2f(80.f, y));
        win.draw(rowText);

        // Name
        rowText.setString(scores[i].first);
        rowText.setPosition(sf::Vector2f(200.f, y));
        win.draw(rowText);

        // Score
        rowText.setString(std::to_string(scores[i].second));
        rowText.setFillColor(sf::Color(255, 215, 0));
        rowText.setPosition(sf::Vector2f(420.f, y));
        win.draw(rowText);
    }

    win.draw(scoreHistoryBackButton);

    win.display();
}

void UIManager::handleTextInput(const sf::Event& e) {
    if (currentState != GameState::NAME_ENTRY) return;

    // [SFML 2.x Compatible event type checking]
    if (e.type == sf::Event::TextEntered) {
        uint32_t unicode = e.text.unicode;
        // Backspace
        if (unicode == 8) {
            if (!playerName.empty()) {
                playerName.pop_back();
            }
        }
        // Readable printable characters (max 20)
        else if (unicode >= 32 && unicode <= 126 && playerName.length() < 20) {
            playerName += static_cast<char>(unicode);
        }
    }
}

std::string UIManager::getPlayerName() const {
    return playerName;
}

void UIManager::setPlayerName(const std::string& name) {
    playerName = name;
}

GameState UIManager::getState() const {
    return currentState;
}

void UIManager::setState(GameState s) {
    currentState = s;
}

void UIManager::handleMainMenuHover(sf::RenderWindow& win, sf::Vector2i mousePos, bool hasSaveFile) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    
    auto updateHover = [&worldMouse](sf::Text& btn, bool enabled) {
        if (!enabled) {
            btn.setFillColor(sf::Color(60, 60, 60));
            btn.setScale(sf::Vector2f(1.0f, 1.0f));
            return;
        }
        if (btn.getGlobalBounds().contains(worldMouse)) {
            btn.setFillColor(sf::Color(0, 229, 255)); // Faded Cyan
            btn.setScale(sf::Vector2f(1.1f, 1.1f));
        } else {
            btn.setFillColor(sf::Color::White);
            btn.setScale(sf::Vector2f(1.0f, 1.0f));
        }
    };

    updateHover(newGameButton, true);
    updateHover(resumeGameButton, hasSaveFile);
    updateHover(scoreHistoryButton, true);
    updateHover(quitButton, true);
}

void UIManager::handlePauseScreenHover(sf::RenderWindow& win, sf::Vector2i mousePos) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    
    auto updateHover = [&worldMouse](sf::Text& btn) {
        if (btn.getGlobalBounds().contains(worldMouse)) {
            btn.setFillColor(sf::Color(255, 215, 0)); // Faded Gold
            btn.setScale(sf::Vector2f(1.1f, 1.1f));
        } else {
            btn.setFillColor(sf::Color::White);
            btn.setScale(sf::Vector2f(1.0f, 1.0f));
        }
    };

    updateHover(resumeButton);
    updateHover(saveQuitButton);
    updateHover(pauseMainMenuButton);
}

void UIManager::handleGameOverHover(sf::RenderWindow& win, sf::Vector2i mousePos) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    
    auto updateHover = [&worldMouse](sf::Text& btn) {
        if (btn.getGlobalBounds().contains(worldMouse)) {
            btn.setFillColor(sf::Color(255, 87, 34)); // Coral
            btn.setScale(sf::Vector2f(1.1f, 1.1f));
        } else {
            btn.setFillColor(sf::Color::White);
            btn.setScale(sf::Vector2f(1.0f, 1.0f));
        }
    };

    updateHover(retryButton);
    updateHover(gameOverMainMenuButton);
}

void UIManager::handleGameWonHover(sf::RenderWindow& win, sf::Vector2i mousePos) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    
    auto updateHover = [&worldMouse](sf::Text& btn) {
        if (btn.getGlobalBounds().contains(worldMouse)) {
            btn.setFillColor(sf::Color(0, 230, 118)); // Green
            btn.setScale(sf::Vector2f(1.1f, 1.1f));
        } else {
            btn.setFillColor(sf::Color::White);
            btn.setScale(sf::Vector2f(1.0f, 1.0f));
        }
    };

    updateHover(gameWonMainMenuButton);
}

void UIManager::handleScoreHistoryHover(sf::RenderWindow& win, sf::Vector2i mousePos) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    
    if (scoreHistoryBackButton.getGlobalBounds().contains(worldMouse)) {
        scoreHistoryBackButton.setFillColor(sf::Color(0, 229, 255));
        scoreHistoryBackButton.setScale(sf::Vector2f(1.05f, 1.05f));
    } else {
        scoreHistoryBackButton.setFillColor(sf::Color::White);
        scoreHistoryBackButton.setScale(sf::Vector2f(1.0f, 1.0f));
    }
}

int UIManager::handleMainMenuClick(sf::RenderWindow& win, sf::Vector2i mousePos, bool hasSaveFile) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    if (newGameButton.getGlobalBounds().contains(worldMouse)) return 1;
    if (resumeGameButton.getGlobalBounds().contains(worldMouse) && hasSaveFile) return 2;
    if (scoreHistoryButton.getGlobalBounds().contains(worldMouse)) return 3;
    if (quitButton.getGlobalBounds().contains(worldMouse)) return 4;
    return 0;
}

int UIManager::handlePauseScreenClick(sf::RenderWindow& win, sf::Vector2i mousePos) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    if (resumeButton.getGlobalBounds().contains(worldMouse)) return 1;
    if (saveQuitButton.getGlobalBounds().contains(worldMouse)) return 2;
    if (pauseMainMenuButton.getGlobalBounds().contains(worldMouse)) return 3;
    return 0;
}

int UIManager::handleGameOverClick(sf::RenderWindow& win, sf::Vector2i mousePos) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    if (retryButton.getGlobalBounds().contains(worldMouse)) return 1;
    if (gameOverMainMenuButton.getGlobalBounds().contains(worldMouse)) return 2;
    return 0;
}

int UIManager::handleGameWonClick(sf::RenderWindow& win, sf::Vector2i mousePos) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    if (gameWonMainMenuButton.getGlobalBounds().contains(worldMouse)) return 1;
    return 0;
}

int UIManager::handleScoreHistoryClick(sf::RenderWindow& win, sf::Vector2i mousePos) {
    sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
    if (scoreHistoryBackButton.getGlobalBounds().contains(worldMouse)) return 1;
    return 0;
}



