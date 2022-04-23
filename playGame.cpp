#include "playGame.h"

using namespace std;

// constructor for playGame class, sets keyList and color vectors
playGame::playGame(const string& inputFile) {
    // initialize turn
    turn = 0;
    // randomly select line from file
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0, 2859);
    int listLoc = dist(mt);
    string line, word;
    ifstream wordsList;
    wordsList.open("wordsList.txt");
    if (wordsList.is_open()) {
        for(int i = 0; i < listLoc; i++) {
            getline(wordsList,line);
        }
    }
    // parse line into keyList
    std::stringstream ss(line);
    while (getline(ss, word, ' ')){
        keyList.push_back(word);
    }
    color.push_back('g');
    color.push_back('g');
    color.push_back('g');
}

// updates key by indexing keyList by turn
void playGame::updateKey() {
    
}

// updates turn
void playGame::updateTurn() {
    turn++;
}

// compares key and guess, sets color vector
void playGame::checkColor() {

}


// executes a turn of Addle, sets guess/updates turn and key
void playGame::playTurn(const string& g) {
    
}

// display number of characters and color
void playGame::display() const {
    cout << "_ _ _";
    for(int i = 0; i < turn; i++){
        if(i<4){
            cout << " _";
        }
    }
    cout << '\n';
    for(char x : color) {
        cout << x << " ";
    }
    cout << '\n';
}

