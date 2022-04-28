#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>

class playGame {
    std::vector<std::string> keyList;
    std::vector<char> color;
    std::map<char, int> letters;
    std::string guess;
    std::string key;
    int newLetter;
    int gameMode;
    int turn;

    public:
        playGame(const std::string& inputFile, const int& gm);
        bool isValid() const;
        bool addTurn() const;
        bool hasWon() const;
        void updateTurn();
        void updateColor();
        void updateGuess();
        void updateLetters();
        int getTurn() const;
        void displayBlanks() const;
        void displayColors() const;
        void displayWords() const;
        void playTurn();
};

#endif // PLAYGAME_H