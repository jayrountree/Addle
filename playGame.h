#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <algorithm>

class playGame {
    std::vector<std::string> keyList;
    std::vector<char> color;
    std::string key;
    std::string guess;
    int turn;

    public:
        playGame(const std::string& inputFile);
        void updateKey();
        void updateTurn();
        void checkColor();
        void playTurn(const std::string& g);
        void display() const;

};



#endif // PLAYGAME_H