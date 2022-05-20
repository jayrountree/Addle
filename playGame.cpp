#include "playGame.h"

using namespace std;

// constructor for playGame class: sets keyList, letters, color, turn, newLetter, key, and gameMode
playGame::playGame(const string& inputFile, const int& gm, const int& bm) {
    // randomly select line from file
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0, 2859);
    int listLoc = dist(mt);
    string line, word;
    ifstream keys;
    keys.open("keys.txt");
    if (keys.is_open()) {
        for (int i = 0; i < listLoc; i++) {
            getline(keys,line);
        }
    }
    keys.close();
    // parse line into keyList
    std::stringstream ss(line);
    while (getline(ss, word, ' ')){
        keyList.push_back(word);
    }
    // initialize map of all letters
    letters = {
            {'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0},
            {'g', 0}, {'h', 0}, {'i', 0}, {'j', 0}, {'k', 0}, {'l', 0},
            {'m', 0}, {'n', 0}, {'o', 0}, {'p', 0}, {'q', 0}, {'r', 0},
            {'s', 0}, {'t', 0}, {'u', 0}, {'v', 0}, {'w', 0}, {'x', 0},
            {'y', 0}, {'z', 0}
    };

    // initialize color, turn, newLetter, key, and gameMode
    color.push_back('x');
    color.push_back('x');
    color.push_back('x');
    turn = 0;
    newLetter = -1;
    key = keyList.at(0);
    gameMode = gm;
}

// checks for guess validity
bool playGame::isValid() const{
    ifstream validWords;
    string word;
    if (guess.length() != key.length()) // checks if valid length
        return false;
    validWords.open("words.txt");
    if (validWords.is_open()) {
        while (getline(validWords,word)) {
            if (guess == word) { // checks if valid english word
                validWords.close();
                return true;
            }
        }
    }
    validWords.close();
    return false;
}

// checks if on an add turn dependent on game mode
bool playGame::addTurn() const {
    if (turn > 0) {
        if (gameMode == 1) {
            if (turn < 5)
                return true;
        }
        if (gameMode == 2) {
            if (turn < 10 && turn % 2 == 0)
                return true;
        }
        if (gameMode == 3) {
            if (turn < 15 && turn % 3 == 0)
                return true;
        }
    }
    return false;
}

// checks for a win
bool playGame::hasWon() const {
    return all_of(color.begin(), color.end(), [](char letter){ return letter == 'g'; }); // checks if all characters in color are 'g'
}

// finds the index of a new letter

int playGame::findNewLetter() {
    string oldKey = key;
    bool flag = true;
    for (int i = 0; i < oldKey.length(); i++) { // finds the index of the new letter
        if (oldKey[i] != key[i]) {
            flag = false;
            newLetter = i;
            break;
        }
    }
    if (flag) { // sets newLetter to the last letter
        newLetter = -1;
    }
    return newLetter;
}

// updates turn, newLetter, and key by indexing keyList by turn
void playGame::updateTurn() {
    turn++;
    if (addTurn()) {
        if (gameMode == 1)
            key = keyList.at(turn);
        else if (gameMode == 2)
            key = keyList.at(turn/2);
        else
            key = keyList.at(turn/3);
        findNewLetter();
    }
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
        if (!flag) { // checks incorrect guess
            colorArray[i] = 'x';
        }
    }
    for (int i = 0; i < guess.length(); i++) {
        if (key[i] == guess[i]) { // checks correct guess same spot again
            colorArray[i] = 'g';
        }
    }
    for (int i = 0; i < guess.length(); i++) {
        if (colorArray[i] == 0) { // catches missed incorrect guesses
            colorArray[i] = 'x';
        }
    }
    //for (char c: colorArray) {} // indexes each color to avoid weird ascii outputs
    for (char c: colorArray) { // fills color vector
        color.push_back(c);
    }
}

// takes in a new guess
void playGame::updateGuess() {
    cin >> guess;
    while(!isValid()) {
        if (guess == "igiveup")
            cout << "The correct word is: " << key << '\n';
        cout << "Please enter a valid word\n";
        cin >> guess;
    }
}

// updates for each correctly guessed letter
void playGame::updateLetters() {
    map<char,int>::iterator it;
    for (int i = 0; i < color.size(); i++) {
        if (color.at(i) == 'g' || color.at(i) == 'y') {
            it = letters.find(guess[i]);
            if (it != letters.end()) {
                it->second++;
            }
        }
    }
}

// gets turn number
int playGame::getTurn() const {
    return turn;
}

vector<char> playGame::getColor() const {
    return color;
}

// displays the number of characters to guess and where new letter was inserted
void playGame::displayBlanks() const {
    bool flag = false;
    for (auto const& x : letters) {
        if (x.second > 0) {
            cout << x.first;
            flag = true;
        }
    }
    if (flag)
        cout << '\n';
    for (int i = 0; i < key.length(); i++){ // displays blanks
        cout << "_ ";
    }
    cout << '\n';
    if (addTurn()) { // displays new letter insertion
        for (int i = 0; i < key.length()-1; i++) {
            if (i == newLetter)
                cout << "^ ";
            else
                cout << "  ";
        }
        if (newLetter == -1)
            cout << "^";
        else
            cout << " ";
        cout << '\n';
    }
}

// displays the colors of the guess
void playGame::displayColors() const {
    if(!hasWon()) { // displays the colors if still playing
        for (char x: color) {
            cout << x << " ";
        }
        cout << '\n';
    }
}

// displays every key
void playGame::displayWords() const {
    for (const string& word: keyList) {
        cout << word << '\n';
    }
}

// executes a turn of Addle
void playGame::playTurn() {
    displayBlanks();
    updateGuess();
    updateColor();
    updateLetters();
    displayColors();
    updateTurn();
}

// executes a turn of Addle with a bot
void playGame::playBotTurn(const string& g) {
    displayBlanks();
    guess = g;
    cout << guess << '\n';
    updateColor();
    updateLetters();
    displayColors();
    updateTurn();
}
