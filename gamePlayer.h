#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>


class gamePlayer {
    std::vector<std::string> guessed;
    std::map<char, double> frequency;
    std::string guess;
    int turn;
    int guessLength;
    int gameMode;

    public:
        explicit gamePlayer(const int& gm);
        void calculateFrequency();
        void updateGuessLength(const int& addSpot);
        std::string makeGuess(const std::vector<char>& color, const int& addSpot);
};

#endif // GAMEPLAYER_H