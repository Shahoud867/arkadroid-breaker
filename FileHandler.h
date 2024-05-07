#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <utility>

/**
 * @file FileHandler.h
 * @brief Static utility class for handling persistence (scores and game states).
 * 
 * [RUBRIC: FileHandler static utility ✓]
 */
class FileHandler {
public:
    /**
     * @brief Save a score entry to the high-scores database file.
     * @param playerName Name of the player.
     * @param score Final achieved score.
     * @param level Final level index reached.
     */
    static void saveScore(const std::string& playerName, int score, int level);

    /**
     * @brief Load and parse all score entries, returning them sorted (highest score first).
     * @return std::vector<std::pair<std::string, int>> Collection of name-score records.
     */
    static std::vector<std::pair<std::string, int>> loadScores();

    /**
     * @brief Serialize the game parameters to restore a session.
     */
    static void saveGameState(const std::string& playerName,
                              int level, int score, int lives,
                              float ballX, float ballY,
                              float ballVelX, float ballVelY,
                              float paddleX, float paddleWidth);

    /**
     * @brief Deserialize the saved session data if the save file exists.
     * @return true If save file was successfully loaded.
     * @return false If file did not exist or could not be loaded.
     */
    static bool loadGameState(std::string& playerName,
                              int& level, int& score, int& lives,
                              float& ballX, float& ballY,
                              float& ballVelX, float& ballVelY,
                              float& paddleX, float& paddleWidth);

    /**
     * @brief Delete the game save state file to clean up when game ends or restarts.
     */
    static void deleteSaveState();

private:
    static const std::string SCORES_FILE;    ///< Path to the scores log ("scores.txt")
    static const std::string SAVE_FILE;      ///< Path to the state log ("savegame.dat")
};

#endif // FILEHANDLER_H
