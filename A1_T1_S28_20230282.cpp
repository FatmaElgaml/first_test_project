// File: A1_T1_S28_20230282.cpp
// Purpose: I want to improve in coding in general.
// Author: Fatma Ali Abdel_Aty Ali Elgamal
// Section: S28
// ID: 20230282
// TA: ...................
// Date: 12 Oct 2024
// Problem 2: convert masculine pronoun for feminine and masculine pronoun.
// Problem 5: add a list of players, show top 10 players and their scores and get the highest score for a players.
// Problem 8: create a beautiful figure by stars '*'. 
// Problem 11: comparison between two files by two different methods (word by word && character by character ).


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

//  Problem 2: Pronoun Replacement
bool ismasculinePronoun(string& word) {
    return word == "he" || word == "He" || word == "his" || word == "His" || word == "him" || word == "Him";
}

void pronounReplacement() {
    string paragraph;
    cout << "Enter a paragraph: ";
    cin.ignore(); 
    getline(cin, paragraph);

    string word, finalSentence;
    stringstream ss(paragraph);
    char punctuation;

    while (ss >> word) {
        char lastletter = word[word.size() - 1];
        bool punc = ispunct(lastletter);
        string new_word = punc ? word.substr(0, word.size() - 1) : word;

        if (ismasculinePronoun(new_word)) {
            if (new_word == "he" || new_word == "He")
                new_word = (new_word == "he") ? "he or she" : "He or She";
            if (new_word == "his" || new_word == "His")
                new_word = (new_word == "his") ? "his or her" : "His or Her";
            if (new_word == "him" || new_word == "Him")
                new_word = (new_word == "him") ? "him or hers" : "Him or Hers";
        }

        if (punc)
            new_word += lastletter;

        finalSentence += new_word + " ";
    }

    cout << "The final result of the sentence is: " << finalSentence << endl;
}

//  Problem 5: High Score Management
struct Player {
    string name;
    int score;
};

bool comparePlayers(const Player& a, const Player& b) {
    return a.score > b.score;
}

void highScoreManagement() {
    int numberOfPlayers;
    cout << "Enter the number of players: ";
    cin >> numberOfPlayers;

    vector<Player> players;
    string name;
    int score;

    cin.ignore();
    for (int i = 0; i < numberOfPlayers; i++) {
        cout << "Please enter the name of the player: ";
        getline(cin, name);
        cout << "Please enter the score of the player: ";
        cin >> score;
        players.push_back({ name, score });
        sort(players.begin(), players.end(), comparePlayers);
        cin.ignore();
    }

    if (players.size() > 10) {
        players.pop_back(); 
    }

    int choice;
    while (true) {
        cout << "\nMenu Options:\n";
        cout << "1. Add a new player and score\n";
        cout << "2. Show top 10 players and scores\n";
        cout << "3. Find the highest score for a player.\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cin.ignore();
            cout << "Please enter the name of the player: ";
            getline(cin, name);
            cout << "Please enter the score of the player: ";
            cin >> score;
            players.push_back({ name, score });
            sort(players.begin(), players.end(), comparePlayers);
            if (players.size() > 10) {
                players.pop_back();
            }
        }
        else if (choice == 2) {
            for (const auto& player : players) {
                cout << player.name << " - " << player.score << endl;
            }
        }
        else if (choice == 3) {
            string searchName;
            cout << "Enter the name of the player: ";
            cin.ignore();
            getline(cin, searchName);

            int highestScore = -1;
            bool found = false;
            for (const auto& player : players) {
                if (player.name == searchName) {
                    found = true;
                    highestScore = max(highestScore, player.score);
                }
            }

            if (found) {
                cout << searchName << "'s highest score is: " << highestScore << endl;
            }
            else {
                cout << searchName << " not found or not in the top 10." << endl;
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice, please try again." << endl;
        }
    }
}

//  Problem 11: File Comparison
bool comparisonByCharacter(const string& file1, const string& file2) {
    ifstream F1(file1), F2(file2);
    if (!F1.is_open() || !F2.is_open()) {
        cout << "The files aren't opened ." << endl;
        return false;
    }

    char character1, character2;
    int countCharacter = 0;

    while (F1.get(character1) && F2.get(character2)) {
        countCharacter++;
        if (character1 != character2) {
            cout << "There is a difference in character: " << countCharacter
                << ": " << file1 << " = '" << character1 << "', "
                << file2 << " = '" << character2 << "'" << endl;
            return false;
        }
    }

 

    return true;
}

bool comparisonByWord(const string& file1, const string& file2) {
    ifstream F1(file1), F2(file2);
    if (!F1.is_open() || !F2.is_open()) {
        cout << "The files aren't opened ." << endl;
        return false;
    }

    string word1, word2;
    int countWord = 0;


    while (F1 >> word1 && F2 >> word2) {
        countWord++;
        if (word1 != word2) {
            cout << "There is a difference in word: " << countWord
                << ": " << file1 << " = '" << word1 << "', "
                << file2 << " = '" << word2 << "'" << endl;
            return false;
        }
    }

    return true;
}

void fileComparison() {
    string file1, file2;
    cout << "Enter the name of the first file: ";
    cin.ignore();
    getline(cin,file1);
    cout << "Enter the name of the second file: ";
    cin.ignore();
    getline(cin ,file2);

    cout << "Choose the way you want to compare with.\n";
    cout << "1: Character by character\n";
    cout << "2: Word by word\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        if (comparisonByCharacter(file1, file2))
            cout << file1 << " and " << file2 << " are identical." << endl;
    }
    else if (choice == 2) {
        if (comparisonByWord(file1, file2))
            cout << file1 << " and " << file2 << " are identical." << endl;
    }
    else {
        cout << "Invalid choice" << endl;
    }
}

// Problem 8: Fractal Star Pattern
void printLineOfStars(int numStars, int indent) {
    for (int i = 0; i < indent; i++) cout << " ";
    for (int i = 0; i < numStars; i++) cout << "*";
    cout << endl;
}

void pattern(int n, int i) {
    if (n == 1) {
        printLineOfStars(1, i);
        return;
    }

    pattern(n / 2, i);
    printLineOfStars(n, i);
    pattern(n / 2, i + n / 2);
}

bool isPowerOfTwo(int num) {
    return num > 0 && (num & (num - 1)) == 0;
}

void fractalPattern() {
    int n, i;
    cout << "Enter the number of stars (must be a power of two) and indent: ";
    cin >> n >> i;

    if (!isPowerOfTwo(n)) {
        cout << "INVALID INPUT" << endl;
    }
    else {
        pattern(n, i);
    }
}

// Main Menu
int main() {
    while (true) {
        int choice;
        cout << "\nChoose a problem to solve:\n";
        cout << "1. Pronoun Replacement\n";
        cout << "2. High Score Management\n";
        cout << "3. File Comparison\n";
        cout << "4. Fractal Star Pattern\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            pronounReplacement();
            break;
        case 2:
            highScoreManagement();
            break;
        case 3:
            fileComparison();
            break;
        case 4:
            fractalPattern();
            break;
        case 5:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}
