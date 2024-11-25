#include "board.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <sstream>
const int NUM_PLAYERS = 4;

int main(int argc, char* argv[]) {
    //Stage 1: Load States
    Board game;
    Player students[NUM_PLAYERS];
    string turnOrder[] = {"Blue", "Red", "Orange", "Yellow"};
    int currentTurn = 0;
    string command = "";
    string boardFile = "";
    string gameFile = "";
    int seed = 0;
    for (int i = 1; i < argc; i += 2) {
        command = argv[i];
        if (command == "-load") {
            gameFile = argv[i + 1];
        }
        else if (command == "-seed") {
            seed = stoi(argv[i + 1]);
        }
        else if (command == "-board") {
            boardFile = argv[i + 1];
        }
    }
    if (gameFile != "") {
        // load game with seed
        
        ifstream fileStream{gameFile};
        string line;
        getline(fileStream, line);
        currentTurn = stoi(line);
        for (int i = 0; i < NUM_PLAYERS; i++) {
            getline(fileStream, line);
            istringstream iss{line};
            string readValue;
            int count = 0;
            map<string, int> resources;
            while (count < 5 && iss >> readValue) {
                if (count == 0) {
                    resources["CAFFEINE"] = stoi(readValue);
                }
                else if (count == 1) {
                    resources["LAB"] = stoi(readValue);
                }
                else if (count == 2) {
                    resources["LECTURE"] = stoi(readValue);
                }
                else if (count == 3) {
                    resources["STUDY"] = stoi(readValue);
                }
                else if (count == 4) {
                    resources["TUTORIALS"] = stoi(readValue);
                }
                count++;
            }
            count = 0;
            iss >> readValue;
            Goal *goals = new Goal[71]; 
            if (readValue == "g") {
                while (readValue != "c") {
                    iss >> readValue;
                    if (readValue == "c") {
                        break;
                    }
                    else {
                        goals[readValue] 
                    }
                    
                }
            }
        }
        // curTurn

        // loop through players, storing data
        // load board
        // geese tile number
    }
    else if (boardFile != "") {
        // load board with seed
    }
    else {
        // load random board
    }

    //Stage 2: Setup
    for(int i = 0; i < NUM_PLAYERS; i++) {
        cout << "Student " << turnOrder[i] << ", where do you want to complete an Assignment?" << endl;
        int index;
        cin >> index;
        students[i].completeCriterion(index);
    }
    for(int i = NUM_PLAYERS - 1; i >= 0; i--) {
        cout << "Student " << turnOrder[i] << ", where do you want to complete an Assignment?" << endl;
        int index;
        cin >> index;
        students[i].completeCriterion(index);
    }
    
    //Stage 3: The Game
    bool gameLoop = true;
    while(gameLoop) {

    }
}