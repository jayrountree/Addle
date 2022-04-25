#include <string>
#include "playGame.h"

using namespace std;

int main () {
    int gameMode;
    cout << "Welcome to Addle. Please enter what difficulty you would like to play.\n";
    cout << "Hard: 1\nMedium: 2\nEasy: 3\n";
    cin >> gameMode;
    if (gameMode == 1)
        cout << "Each turn, a new letter will be inserted to create a new guessable word\n";
    else
        cout << "Every " << gameMode << " turns, a new letter will be inserted to create a new guessable word\n";
    cout << "This new letter will be denoted by a \"^\", and new letters will continue to be inserted until seven letters are reached.\n";
    cout << "Try and guess the word as quick as you can. Good luck!\n";
    playGame game = playGame("wordsList.txt", gameMode);
    string guess;
    while(!game.hasWon()) {
        game.playTurn();
    }
    cout << "Congrats! You have beaten Addle in " << game.getTurn() << " tr";
    if (game.getTurn() == 1)
        cout << "y";
    else
        cout << "ies";
    cout << ".\n";
    cout << "Here is every word in this Addle:\n";
    game.displayWords();
}