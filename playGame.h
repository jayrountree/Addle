#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

class game {
    std::vector<std::string> keyList;
    std::vector<char> color;
    std::string key;
    std::string guess;
    int turn;

    public:
        void playGame(std::string wordList);
        void updateKey();
        void updateTurn();
        void turn(std::string guess);
        void display();

};



#endif // GAME_H