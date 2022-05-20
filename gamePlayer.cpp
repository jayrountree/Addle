#include "gamePlayer.h"

using namespace std;

// constructor for gamePlayer: sets frequency, turn, guessLength, and gameMode
gamePlayer::gamePlayer(const int& gm) {
    frequency = {
            {'a', 0.0756316}, {'b', 0.0186695}, {'c', 0.0410866}, {'d', 0.0399661},
            {'e', 0.115569}, {'f', 0.0141894}, {'g', 0.0295077}, {'h', 0.0214657},
            {'i', 0.0879741}, {'j', 0.0016653}, {'k', 0.0081368}, {'l', 0.0544774},
            {'m', 0.0267115}, {'n', 0.0711494}, {'o', 0.0599563}, {'p', 0.0291362},
            {'q', 0.0017953}, {'r', 0.0726579}, {'s', 0.0854977}, {'t', 0.0700247},
            {'u', 0.0340517}, {'v', 0.0105864}, {'w', 0.0085165}, {'x', 0.0028705},
            {'y', 0.0172291}, {'z', 0.0014755}
    };
    turn = 0;
    guessLength = 3;
    gameMode = gm;
}

void gamePlayer::calculateFrequency(){
    map<char, double> freq = {
            {'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0},
            {'g', 0}, {'h', 0}, {'i', 0}, {'j', 0}, {'k', 0}, {'l', 0},
            {'m', 0}, {'n', 0}, {'o', 0}, {'p', 0}, {'q', 0}, {'r', 0},
            {'s', 0}, {'t', 0}, {'u', 0}, {'v', 0}, {'w', 0}, {'x', 0},
            {'y', 0}, {'z', 0}
    };
    int totalLetters = 0;
    ifstream words;
    string line;
    words.open("words.txt");
    if (words.is_open()) {
        while(getline(words,line)){
            for (char letter: line) {
                freq[letter]++;
                totalLetters++;
            }
        }
    }
    words.close();
    map<char,double>::iterator it;
    for (it=freq.begin(); it != freq.end(); it++) {
        it->second /= totalLetters;
        //cout << it->first << " " << it-> second << '\n';
    }
}

void gamePlayer::updateGuessLength(const int& addSpot) {
    bool adding = false;
    if (gameMode == 1) {
        if (turn < 5) {
            guessLength++;
            adding = true;
        }
    }
    if (gameMode == 2) {
        if (turn < 10 && turn % 2 == 0) {
            guessLength++;
            adding = true;
        }
    }
    if (gameMode == 3) {
        if (turn < 15 && turn % 3 == 0) {
            guessLength++;
            adding = true;
        }
    }
    /*
    if (adding) {
        if (addSpot == 0)
            guess = " " + guess;
        else if (addSpot == guess.size())
            guess = guess + " ";
        else {
            guess = guess.substr(0,addSpot) + " " + guess.substr(addSpot, string::npos);
        }
    }
     */
};

string gamePlayer::makeGuess(const vector<char>& color, const int& addSpot) {
    std::vector<std::string> possibleGuesses;
    string word;
    bool toAdd;
    bool toGuess;
    ifstream words;
    double guessRating;
    guessed.clear();
    words.open("words.txt");
    if (words.is_open()) {
        while (getline(words,word)) {
            toAdd = true;
            if (word.length() == guessLength) {
                /*
                for (int i = 0; i < word.length(); i++) {
                    if (color.at(i) == 'g' && word[i] != guess[i])
                       toAdd = false;
                    if (color.at(i) == 'x' && word[i] == guess[i])
                        toAdd = false;
                }
                if (toAdd)
                    possibleGuesses.push_back(word);
                    */
                possibleGuesses.push_back(word);
            }
        }
    }
    words.close();
    turn++;
    updateGuessLength(addSpot);
    for (auto & newGuess : possibleGuesses) {
        toGuess = true;
        for (auto & alreadyGuessed : guessed) {
            cout << "test " << newGuess << " " << alreadyGuessed << '\n';
            if (newGuess == alreadyGuessed) {

                toGuess = false;
            }
        }
        if (toGuess) {
            guess = newGuess;
            guessed.push_back(guess);
            return guess;
        }
    }
}


