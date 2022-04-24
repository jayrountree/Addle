#include <string>
#include "playGame.h"

using namespace std;

int main () {
    cout << "Welcome to Addle. Each turn, a new letter will be added to create a new guessable word.\n";
    cout << "This new letter will be denoted by a \"^\", and letters will continue to be added until a seven letter word is reached.\n";
    cout << "Try and guess the word as quick as you can. Good luck!\n";
    playGame game = playGame("wordsList.txt");
    string guess;
    while(!game.hasWon()) {
        game.playTurn();
    }
    cout << "Congrats! You have beaten Addle.";
}