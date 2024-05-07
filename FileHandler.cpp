#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cstdio>

// Define static constants
const std::string FileHandler::SCORES_FILE = "scores.txt";
const std::string FileHandler::SAVE_FILE = "savegame.dat";

void FileHandler::saveScore(const std::string& playerName, int score, int level) {
    // Open in append mode
    std::ofstream out(SCORES_FILE, std::ios::app);
    if (!out.is_open()) {
        return;
    }

    // Get current date in YYYY-MM-DD format
    std::time_t t = std::time(nullptr);
    std::tm now;
#ifdef _MSC_VER
    localtime_s(&now, &t);
#else
    now = *std::localtime(&t);
#endif
    char dateBuffer[128];
    std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &now);

    // Append to file: PlayerName,Score,Level,YYYY-MM-DD
    out << playerName << "," << score << "," << level << "," << dateBuffer << "\n";
    out.close();
}

std::vector<std::pair<std::string, int>> FileHandler::loadScores() {
    std::vector<std::pair<std::string, int>> scoreEntries;
    std::ifstream in(SCORES_FILE);
    if (!in.is_open()) {
        return scoreEntries;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string nameToken, scoreToken, levelToken, dateToken;

        if (std::getline(ss, nameToken, ',') &&
            std::getline(ss, scoreToken, ',') &&
            std::getline(ss, levelToken, ',') &&
            std::getline(ss, dateToken, ',')) {
            try {
                int score = std::stoi(scoreToken);
                scoreEntries.push_back({nameToken, score});
            } catch (...) {
                // Ignore parsing errors on individual corrupted entries
            }
        }
    }
    in.close();

    // Sort by score descending (highest first)
    std::sort(scoreEntries.begin(), scoreEntries.end(), 
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    return scoreEntries;
}

void FileHandler::saveGameState(const std::string& playerName,
                                int level, int score, int lives,
                                float ballX, float ballY,
                                float ballVelX, float ballVelY,
                                float paddleX, float paddleWidth) {
    std::ofstream out(SAVE_FILE, std::ios::trunc);
    if (!out.is_open()) {
        return;
    }

    // Line 1: playerName
    out << playerName << "\n";
    // Line 2: level,score,lives
    out << level << "," << score << "," << lives << "\n";
    // Line 3: ballX,ballY,ballVelX,ballVelY
    out << ballX << "," << ballY << "," << ballVelX << "," << ballVelY << "\n";
    // Line 4: paddleX,paddleWidth
    out << paddleX << "," << paddleWidth << "\n";

    out.close();
}

bool FileHandler::loadGameState(std::string& playerName,
                                int& level, int& score, int& lives,
                                float& ballX, float& ballY,
                                float& ballVelX, float& ballVelY,
                                float& paddleX, float& paddleWidth) {
    std::ifstream in(SAVE_FILE);
    if (!in.is_open()) {
        return false;
    }

    std::string line;
    
    // Line 1: playerName
    if (!std::getline(in, playerName)) {
        return false;
    }

    // Line 2: level,score,lives
    if (!std::getline(in, line)) {
        return false;
    }
    std::stringstream ss2(line);
    std::string t1, t2, t3;
    if (std::getline(ss2, t1, ',') && std::getline(ss2, t2, ',') && std::getline(ss2, t3, ',')) {
        try {
            level = std::stoi(t1);
            score = std::stoi(t2);
            lives = std::stoi(t3);
        } catch (...) { return false; }
    } else { return false; }

    // Line 3: ballX,ballY,ballVelX,ballVelY
    if (!std::getline(in, line)) {
        return false;
    }
    std::stringstream ss3(line);
    std::string b1, b2, b3, b4;
    if (std::getline(ss3, b1, ',') && std::getline(ss3, b2, ',') && 
        std::getline(ss3, b3, ',') && std::getline(ss3, b4, ',')) {
        try {
            ballX = std::stof(b1);
            ballY = std::stof(b2);
            ballVelX = std::stof(b3);
            ballVelY = std::stof(b4);
        } catch (...) { return false; }
    } else { return false; }

    // Line 4: paddleX,paddleWidth
    if (!std::getline(in, line)) {
        return false;
    }
    std::stringstream ss4(line);
    std::string p1, p2;
    if (std::getline(ss4, p1, ',') && std::getline(ss4, p2, ',')) {
        try {
            paddleX = std::stof(p1);
            paddleWidth = std::stof(p2);
        } catch (...) { return false; }
    } else { return false; }

    in.close();
    return true;
}

void FileHandler::deleteSaveState() {
    std::remove(SAVE_FILE.c_str());
}
