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
    if (turn < 5)
        key = keyList.at(turn);
}

// compares key and guess, sets color vector
void playGame::updateColor() {
    color.clear();
    char colorArray[key.length()];
    bool flag;
    vector<int> removed;
    for (int i = 0; i < guess.length(); i++) {
        if (key[i] == guess[i]) { // checks correct guess same spot
            colorArray[i] = 'g';
            removed.push_back(i);
        }
    }
    for (int i = 0; i < guess.length(); i++) {
        flag = false;
        for (int x = 0; x < key.length(); x++) {
            if (guess[i] == key[x] && find(removed.begin(), removed.end(), x) == removed.end()) { // checks correct guess incorrect spot
                colorArray[i] = 'y';
                removed.push_back(x);
                flag = true;
                break;
            }
        }
        if (!flag) {
            colorArray[i] == 'x';
        }
    }
    for (int i = 0; i < guess.length(); i++) {
        if (key[i] == guess[i]) { // checks correct guess same spot again
            colorArray[i] = 'g';
        }
    }
    for (char c: colorArray) {} // for some reason this is required to place x
    for (int i = 0; i < guess.length(); i++) {
        if (colorArray[i] == 0) { // checks incorrect guess
            colorArray[i] = 'x';
        }
    }
    for (char c: colorArray) {
        cout << c;
        color.push_back(c);
    }
    cout << '\n';
}

// takes in a new guess
void playGame::updateGuess() {
    cin >> guess;
}

// executes a turn of Addle, updates guess
void playGame::playTurn() {
    displayBlanks();
    cout << key << '\n';
    updateGuess();
    updateColor();
    displayColors();
    updateTurn();
}

// checks for a win
bool playGame::hasWon() const {
    return all_of(color.begin(), color.end(), [](char letter){ return letter == 'g'; }); // checks if all characters in color are 'g'
}

// display number of characters to guess
void playGame::displayBlanks() const{
    cout << "_ _ _";
    for(int i = 0; i < turn; i++){
        if (i < 4)
            cout << " _";
    }
    cout << '\n';
}

void playGame::displayColors() const{
    for(char x : color) {
        cout << x << " ";
    }
    cout << '\n';
}
