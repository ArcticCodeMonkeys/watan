#include "board.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <sstream>
const int NUM_PLAYERS = 4;

int main(int argc, char* argv[]) {
    //Stage 1: Load States
    Player students[NUM_PLAYERS];
    string turnOrder[] = {"B", "R", "O", "Y"};

    int currentTurn = 0;
    string command = "";
    string boardFile = "";
    string gameFile = "";
    int seed = 0;
    bool givenSeed = false;
    for (int i = 1; i < argc; i += 2) {
        command = argv[i];
        if (command == "-load") {
            gameFile = argv[i + 1];
        }
        else if (command == "-seed") {
            seed = stoi(argv[i + 1]);
            givenSeed = true;
        }
        else if (command == "-board") {
            boardFile = argv[i + 1];
        }
    }
    if (givenSeed) {
        srand(seed);
    }
    else {
        srand(time(NULL));
    }
    if (gameFile != "") {
        ifstream fileStream{gameFile};
        string line;
        getline(fileStream, line);
        currentTurn = stoi(line);

        // load players
        map<string, int> [4] total_resources;
        Player *goalOwners [71]; 
        Player *criterionOwners [53];
        int typeArray [53];
        // loop through players, storing data
        for (int i = 0; i < NUM_PLAYERS; i++) {
            getline(fileStream, line);
            istringstream iss{line};
            string readValue;
            int count = 0;
            // read resources
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
            total_resources[i] = resources;

            // read goals
            iss >> readValue; // skip "g"
            while (iss >> readValue) {
                if (readValue == "c") {
                    break;
                }
                else {
                    int goalIndex = stoi(readValue);
                    owners[goalIndex] = students[i];
                }
            }
            // read criteria
            count = 0;
            int prevRead = 0;
            while (iss >> readValue) {
                if (count % 2 == 0) {
                    int criterionIndex = stoi(readValue);
                    criterionOwners[criterionIndex] = students[i];
                    prevRead = criterionIndex;
                }
                else {
                    int criterionType = stoi(readValue);
                    typeArray[prevRead] = criterionType;
                }
            }
        }

        // load board
        getline(fileStream, line);
        istringstream iss{line};
        string readValue;
        int tile [19][2];
        int count = 0;
        while (iss >> readValue) {
            if (count % 2 == 0) {
                int resourceType = stoi(readValue);
                tile[count][0] = resourceType;
            }
            else {
                int rollingValue = stoi(readValue);
                tile[count][1] = rollingValue;
            }
        }
        // geese tile number
        getline(fileStream, line);
        int geeseTile = stoi(line);
        Board game = new Board (total_resources, goalOwners, criterionOwners, typeArray, tile, geeseTile);
    }
    else if (boardFile != "") {
        // load board
         getline(fileStream, line);
        istringstream iss{line};
        string readValue;
        int tile [19][2];
        int count = 0;
        while (iss >> readValue) {
            if (count % 2 == 0) {
                int resourceType = stoi(readValue);
                tile[count][0] = resourceType;
            }
            else {
                int rollingValue = stoi(readValue);
                tile[count][1] = rollingValue;
            }
        }
        Board game = new Board (tile);
    }
    else {
        // load random board
        Board game = new Board()
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