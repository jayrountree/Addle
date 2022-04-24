#include <string>
#include "playGame.h"

using namespace std;

int main () {
    cout << "Welcome to Addle. Each turn, a new letter will be inserted to create a new guessable word.\n";
    cout << "This new letter will be denoted by a \"^\", and new letters will continue to be inserted until seven letters are reached.\n";
    cout << "Try and guess the word as quick as you can. Good luck!\n";
    playGame game = playGame("wordsList.txt");
    string guess;
    while(!game.hasWon()) {
        game.playTurn();
    }
    cout << "Congrats! You have beaten Addle in " << game.getTurn() << " tries.\n";
    cout << "Here is every word in this Addle:\n";
    game.displayWords();
}