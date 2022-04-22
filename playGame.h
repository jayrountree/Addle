#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <vector>
#include <string>

class playGame {
    std::vector<std::string> keyList;
    std::vector<char> color;
    std::string key;
    std::string guess;
    int turn;

    public:
        playGame(std::string wordList);
        void updateKey();
        void updateTurn();
        void checkColor();
        void playTurn(std::string g);
        void display();

};



#endif // PLAYGAME_H