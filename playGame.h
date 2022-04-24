#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <sstream>
#include <algorithm>

class playGame {
    std::vector<std::string> keyList;
    std::vector<char> color;
    std::string key;
    std::string guess;
    int newLetter;
    int turn;

    public:
        explicit playGame(const std::string& inputFile);
        void updateTurn();
        void updateColor();
        void updateGuess();
        void playTurn();
        int getTurn() const;
        bool hasWon() const;
        void displayBlanks() const;
        void displayColors() const;
        void displayWords() const;
};

#endif // PLAYGAME_H