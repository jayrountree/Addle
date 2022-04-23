#include "playGame.h"

using namespace std;

// constructor for playGame class: sets keyList, color, turn, and key
playGame::playGame(const string& inputFile) {
    // randomly select line from file
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0, 2859);
    int listLoc = dist(mt);
    string line, word;
    ifstream wordsList;
    wordsList.open("wordsList.txt");
    if (wordsList.is_open()) {
        for (int i = 0; i < listLoc; i++) {
            getline(wordsList,line);
        }
    }
    // parse line into keyList
    std::stringstream ss(line);
    while (getline(ss, word, ' ')){
        keyList.push_back(word);
    }
    // initialize color, turn, and key
    color.push_back('x');
    color.push_back('x');
    color.push_back('x');
    turn = 0;
    key = keyList.at(0);
}

// updates turn and key by indexing keyList by turn
void playGame::updateTurn() {
    turn++;
    if (turn < 4)
        key = keyList.at(turn);
}

// compares key and guess, sets color vector
void playGame::updateColor() {
    color.clear();
    string lettersLeft = guess;
    char currentLetter;
    int keyInd = 0;
    bool flag;
    vector<int> removed;
    while (lettersLeft.length() > 0) {
        flag = false;
        currentLetter = lettersLeft[0];
        if (currentLetter == key[keyInd]) { // checks same place same spot
            color.push_back('g');
        }
        else {
            for(int i = keyInd; i < key.length(); i++) {
                if (currentLetter == key[i] && find(removed.begin(), removed.end(), i) != removed.end()) {
                    color.push_back('y');
                    removed.push_back(i);
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                color.push_back('x');
            }
        }
        keyInd++;
        lettersLeft = lettersLeft.substr(1,lettersLeft.length()-1);
    }
}

// takes in a new guess
void playGame::updateGuess() {
    cin >> guess;
}

// executes a turn of Addle, updates guess
void playGame::playTurn() {
    display();
    updateGuess();
    cout << key << '\n';
    updateColor();
    updateTurn();
}

// checks for a win
bool playGame::hasWon() const {
    return all_of(color.begin(), color.end(), [](char letter){ return letter == 'g'; }); // checks if all characters in color are 'g'
}

// display number of characters and color
void playGame::display() {
    cout << "_ _ _";
    for(int i = 0; i < turn; i++){
        if (i < 4)
            cout << " _";
    }
    cout << '\n';
    for(char x : color) {
        cout << x << " ";
    }
    cout << '\n';
}

