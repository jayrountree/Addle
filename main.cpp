#include <string>
#include <iostream>
#include <iomanip>
#include "playGame.h"

using namespace std;

int main () {
    playGame game = playGame("wordsList.txt");
    string guess;
    cout << "Game start" << '\n';
    game.display();
    cout << "Enter first guess:";
    cin >> guess;
}