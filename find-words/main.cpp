#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
void print(map<string,vector<string>>& myMap) {
    for (auto& itr : myMap) {
        cout << itr.first << '\n';
        for(string &word : itr.second) {
            cout << "\t" << word << '\n';
        }
    }
}

void print(vector<string> &wordVec) {
    for (string &word : wordVec) {
        cout << word << '\n';
    }
}

void addWord(map<string,vector<string>> &wordMap, string &addWord, string &keyWord) {
    if(wordMap.find(keyWord) != wordMap.end()){
        wordMap[keyWord].push_back(addWord);
    }
    else {
        wordMap.insert({keyWord,vector<string>()});
        wordMap[keyWord].push_back(addWord);
    }
}

void addUnique(vector<string> &wordVec, string &word) {
    if(std::find(wordVec.begin(),wordVec.end(),word) == wordVec.end()){
        wordVec.push_back(word);
    }
}

bool checkPattern(string str, string pattern) {
    int ind1;
    int ind2 = -1;
    bool contains;
    if (str.length() < pattern.length())
        return false;
    for (int i = 0; i != pattern.length(); i++) {
        contains = false;
        for(int x = ind2+1; x != str.length(); x++) {
            if(str[x] == pattern[i]) {
                ind1 = x;
                if (ind2 > ind1) {
                    return false;
                }
                ind2 = x;
                if(i == pattern.length()-1) {
                    return true;
                }
                contains = true;
                break;
            }
        }
        if(!contains) {
            return false;
        }
    }
    return false;
}

void inOrder(string input, string output) { // NOLINT(performance-unnecessary-value-param)
    ifstream words;
    words.open(input);
    ofstream wordsOut;
    wordsOut.open(output);
    vector<string> three;
    vector<string> four;
    vector<string> five;
    vector<string> six;
    vector<string> seven;
    string currentWord;
    if (words.is_open()) {
        while(getline(words,currentWord)) {
            if(currentWord.length() == 3) {
                three.push_back(currentWord);
            }
            else if(currentWord.length() == 4 && std::find(three.begin(),three.end(),currentWord.substr(0,3)) != three.end()) {
                four.push_back(currentWord);
            }
            else if(currentWord.length() == 5 && std::find(four.begin(),four.end(),currentWord.substr(0,4)) != four.end()) {
                five.push_back(currentWord);
            }
            else if(currentWord.length() == 6 && std::find(five.begin(),five.end(),currentWord.substr(0,5)) != five.end()) {
                six.push_back(currentWord);
            }
        }
        words.close();
    }
    if(wordsOut.is_open()) {
        for (string &word: six) {
            wordsOut << word << '\n';
        }
    }
    wordsOut.close();
}

void outOfOrder(string input, string output) { // NOLINT(performance-unnecessary-value-param)
    ifstream words;
    words.open(input);
    ofstream wordsOut;
    wordsOut.open(output);
    vector<string> seven;
    vector<string> six;
    vector<string> five;
    vector<string> four;
    vector<string> three;
    map<string,vector<string>> sixToSeven;
    map<string,vector<string>> fiveToSix;
    map<string,vector<string>> fourToFive;
    map<string,vector<string>> threeToFour;
    string currentWord;
    if (words.is_open()) {
        while(getline(words,currentWord)) {
            if(currentWord.length() == 7) {
                addUnique(seven,currentWord);
            }
        }
        words.clear();
        words.seekg(0, ios::beg);
        while(getline(words,currentWord)) {
            if(currentWord.length() == 6) {
                for(string vecWord : seven) {
                    if(checkPattern(vecWord,currentWord)) {
                        addWord(sixToSeven,vecWord,currentWord);
                        addUnique(six,currentWord);
                    }
                }
            }
        }
        words.clear();
        words.seekg(0, ios::beg);
        while(getline(words,currentWord)) {
            if(currentWord.length() == 5) {
                for(string vecWord : six) {
                    if(checkPattern(vecWord,currentWord)) {
                        addWord(fiveToSix,vecWord,currentWord);
                        addUnique(five,currentWord);
                    }
                }
            }
        }
        words.clear();
        words.seekg(0, ios::beg);
        while(getline(words,currentWord)) {
            if(currentWord.length() == 4) {
                for(string vecWord : five) {
                    if(checkPattern(vecWord,currentWord)) {
                        addWord(fourToFive,vecWord,currentWord);
                        addUnique(four,currentWord);
                    }
                }
            }
        }
        words.clear();
        words.seekg(0, ios::beg);
        while(getline(words,currentWord)) {
            if(currentWord.length() == 3) {
                for(string vecWord : four) {
                    if(checkPattern(vecWord,currentWord)) {
                        addWord(threeToFour,vecWord,currentWord);
                        addUnique(three,currentWord);
                    }
                }
            }
        }
        words.close();
    }
    for (auto& itr3 : threeToFour) {
        for(string word : itr3.second) {
            auto itr4 = fourToFive.find(word);
            for(string word : itr4->second) {
                auto itr5 = fiveToSix.find(word);
                for(string word : itr5->second) {
                    auto itr6 = sixToSeven.find(word);
                    for(string word : itr6->second) {
                        wordsOut << itr3.first << " " << itr4->first << " " << itr5->first << " " << itr6->first << " " << word << '\n';
                    }
                }
            }
        }
    }
    wordsOut.close();
}

int main() {
    inOrder("words.txt","appendedLetterWords.txt");
    outOfOrder("words.txt", "insertedLetterWords.txt");
}

