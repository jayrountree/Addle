#include <string>
#include "playGame.h"

using namespace std;

int main () {
    playGame game = playGame("wordsList.txt");
    string guess;
    while(!game.hasWon()) {
        game.playTurn();
    }
    cout << "Congrats! You have beaten Addle.";
}