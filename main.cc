#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "player.h"
#include "board.h"
#include "tile.h"
#include "criterion.h"
const int NUM_PLAYERS = 4;
const int GOAL_COUNT = 54;
const int CRITERIA_COUNT = 72;
using namespace std;

int main(int argc, char* argv[]) {
    
    Board game;
    cout << "Welcome to the Game of Goose!" << endl;
    Player students[NUM_PLAYERS];
    char turnOrder[NUM_PLAYERS] = {'B', 'R', 'O', 'Y'};
    string resourcesArr[6] = {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL", "NETFLIX"};
    for (int i = 0; i < NUM_PLAYERS; i++) {
        students[i].setName(turnOrder[i]);
    }
    int currentTurn = 0;

    // command line arguments handling
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
    
    {givenSeed? srand(seed) : srand(time(NULL));}

    // loading game from file
    if (gameFile != "") {
        ifstream fileStream{gameFile};
        string line;
        getline(fileStream, line);
        currentTurn = stoi(line);

        // load players
        map<string, int> total_resources [NUM_PLAYERS];
        Player *goalOwners [GOAL_COUNT]; 
        Player *criterionOwners [CRITERIA_COUNT];
        int typeArray [CRITERIA_COUNT];
        // loop through players, storing data
        for (int i = 0; i < NUM_PLAYERS; i++) {
            getline(fileStream, line);
            istringstream iss{line};
            string readValue;
            int count = 0;
            // read resources
            map<string, int> resources;
            while (count < 5 && iss >> readValue) {
                
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
                    goalOwners[goalIndex] = &students[i];
                }
            }
            // read criteria
            count = 0;
            int prevRead = 0;
            while (iss >> readValue) {
                if (count % 2 == 0) {
                    int criterionIndex = stoi(readValue);
                    criterionOwners[criterionIndex] = &students[i];
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
        game = Board(total_resources, goalOwners, criterionOwners, typeArray, tile, geeseTile);
    }
    // load board
    else if (boardFile != "") {
        ifstream fileStream{gameFile};
        string line;
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
        game = Board(tile);
    }
    // otherwise random board is loaded

    //Stage 2: Initial Assignment purchasing
    for(int i = 0; i < NUM_PLAYERS; i++) {
        cout << "Student " << turnOrder[i] << ", where do you want to complete an Assignment?" << endl;
        int index;
        cin >> index;
        if(!students[i].completeCriterion(game.getCriteria()[index], true)) {
            i--;
        }
    }
    for(int i = NUM_PLAYERS - 1; i >= 0; i--) {
        cout << "Student " << turnOrder[i] << ", where do you want to complete an Assignment?" << endl;
        int index;
        cin >> index;
        if(!students[i].completeCriterion(game.getCriteria()[index], true)) {
            i++;
        }
    }
    


    //Stage 3: The Game
    bool gameLoop = true;
    while(gameLoop) {
        //Step 1: Set the Dice
        cout << "Student " << students[currentTurn].getName() << "'s Turn" << endl;
        //cout << students[currentTurn]; SOMETHING THAT SHOULD BE DONE
        string rollCommand;
        while(cin >> rollCommand) {
            if(rollCommand == "roll") {
                break;
            } else if (rollCommand == "load") {
                int fixedVal;
                cin >> fixedVal;
                students[currentTurn].setDice(fixedVal);
            } else if (rollCommand == "fair") {
                students[currentTurn].setDice(-1);
            } else {
                cout << "Invalid Command; try either roll, load x, or fair." << endl;
            }
        }
        
        //Step 2: Roll the Dice
        cout << "bouta roll some dice" << endl;
        Tile ** tiles = game.getTiles();
        int diceRoll = students[currentTurn].rollDice();
        if(diceRoll == 7) {
            //GOOSE!
            for(int i = 0; i < NUM_PLAYERS; i++) {
                int cardCount = 0;
                cout << i << NUM_PLAYERS << endl;
                for(auto it = students[i].getResources().begin(); it != students[i].getResources().end(); ++it) {
                    cardCount += it->second;
                }
                cout << "Reached here" << endl;
                if(cardCount >= 10) {
                    int disappeared = cardCount / 2;
                    map<string, int> lostResources;
                    while (disappeared > 0) {
                        int disappearType = rand() % 5;
                        string disappearString = resourcesArr[disappearType];
                        if (students[i].getResources()[disappearString] > 0) {
                            students[i].getResources()[disappearString] -= 1;
                            disappeared--;
                            if (lostResources.find(disappearString) == lostResources.end()) {
                                lostResources[disappearString] = 1;
                            } else {
                                lostResources[disappearString] += 1;
                            }
                        }
                    }
                    cout << "Student " << turnOrder[i] << "loses " << disappeared << " resources to the geese. They lose:" << endl;
                    for(auto it = lostResources.begin(); it != lostResources.end(); ++it) {
                        cout << it->second << " " << it->first << endl;
                    }
                }
            }
            cout << "Choose where to place the GEESE." << endl;
            int index;
            cin >> index;
            
            if(!(tiles[index]->getGeese())) {
                for(int i = 0; i < 19; i++) {
                    if(tiles[i]->getGeese()) {
                       tiles[i]->setGeese(false);
                    }
                }
                tiles[index]->setGeese(true);
            }
            char stealFrom [6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
            for (int i = 0; i < 6 ; i++) {
                char name = tiles[index]->getCriteria(i)->getPlayer()->getName();
                if (name != students[currentTurn].getName()) {
                    stealFrom[i] = name;
                }
            }
            if (stealFrom[0] == '\0') {
                cout << "Student " << students[currentTurn].getName() << " has no students to steal from." << endl;
            }
            else {
                cout << "Student " << students[currentTurn].getName() << "can choose to steal from ";
                for (int j = 0; j < NUM_PLAYERS; j++) {
                    if (students[j].getName() != students[currentTurn].getName()) {
                        for (int i = 0; i < 6; i++) {
                            if (students[j].getName() == stealFrom[i]) {
                                cout << students[j].getName() << ", ";
                                break;
                            }
                        }
                    }
                }
            }
            char charCommand;
            cin >> charCommand;
            for (int i = 0; i < NUM_PLAYERS; i++) {
                if (turnOrder[i] == charCommand) {
                    int cardCount = 0;
                    for(auto it = students[i].getResources().begin(); it != students[i].getResources().end(); ++it) {
                        cardCount += it->second;
                    }
                    int randomCard = rand() % cardCount;
                    int cardType = 0;
                    for (auto it = students[i].getResources().begin(); it != students[i].getResources().end(); ++it) {
                        int val = it->second;
                        if (cardType + val > randomCard) {
                            students[i].getResources()[it->first] -= 1;
                            students[currentTurn].getResources()[it->first] += 1;
                            cout << "Student " << students[currentTurn].getName() << " steals " << it->first << " from " << turnOrder[i] << endl;
                            break;
                        }
                        cardType += val;
                    }
                    break;
                }
            }
        }
        else {
            cout << "didnt goose" << endl;
            for(int i = 0; i < 19; i++) {
                if(tiles[i]->getRollingValue() == diceRoll) {
                    tiles[i]->notifyObservers();
                }
            }
        }
        cout << "Rolled a " << diceRoll << endl;
        //Step 3: Action Time
        string command;
        while(cin >> command) {
            if (command == "next") {
                currentTurn = (currentTurn + 1) % 4;
                break;
            }
            else if (command == "board") {
                cout << game;
            }
            else if (command == "status") {
                for(int i = 0; i < NUM_PLAYERS; i++) {
                    //cout << students[i]; SOMETHING THAT SHOULD BE DONE
                }
            }
            else if (command == "criteria") {
                for(int i = 0; i < students[currentTurn].getCriteria().size(); i++) {   
                    cout << students[currentTurn].getCriteria()[i]->getIndex() << " " << students[currentTurn].getCriteria()[i]->getType() << endl;
                }
            }
            else if (command == "achieve") {
                int index;
                cin >> index;
                students[currentTurn].achieveGoal(game.getGoals()[index], false);
            }
            else if (command == "complete") {
                int index;
                cin >> index;
                students[currentTurn].completeCriterion(game.getCriteria()[index], false);
            }
            else if (command == "improve") {
                int index;
                cin >> index;
                students[currentTurn].improveCriterion(index);
            }
            else if (command == "trade") {
                char target;
                string give;
                string take;
                cin >> target;
                cin >> give;
                cin >> take;
                for (int i = 0; i < NUM_PLAYERS; i++) {
                    if (turnOrder[i] == target) {
                        students[currentTurn].trade(&students[i], give, take);
                       break;
                    }
                }
            }
            else if (command == "save") {
                string saveFile;
                cin >> saveFile;
                ofstream saveStream{saveFile};
                saveStream << currentTurn << endl;
                for(int i = 0; i < NUM_PLAYERS; i++) {
                    for (auto it = students[i].getResources().begin(); it != students[i].getResources().end(); ++it) {
                        saveStream << it->second << " ";
                    }
                    saveStream << "g ";
                    for (int j = 0; j < GOAL_COUNT; j++) {
                        if (students[i].getGoals()[j] != nullptr) {
                            saveStream << j << " ";
                        }
                    }
                    saveStream << "c ";
                    for (int j = 0; j < CRITERIA_COUNT; j++) {
                        if (students[i].getCriteria()[j] != nullptr) {
                            saveStream << j << " " << students[i].getCriteria()[j]->getType() << " ";
                        }
                    }
                    saveStream << endl;
                }
                int gooseTile = 0;
                for (int i = 0; i < 19; i++) {
                    string resourceType = tiles[i]->getResource();
                    if (tiles[i]->getGeese()) {
                        gooseTile = i;
                    }
                    int resourceInt = 0;
                    for (int i = 0; i < 6; i++) {
                        if (resourceType == resourcesArr[i]) {
                            resourceInt = i;
                        }
                    }
                    saveStream << resourceInt << " " << tiles[i]->getRollingValue() << " ";
                }
                saveStream << endl;
                saveStream << gooseTile << endl;
            }
            else if (command == "help") {
                cout << "Valid commands: " << endl
                << "board " << endl
                << "status " << endl
                << "criteria " << endl
                << "achieve <goal#>" << endl
                << "complete <criterion#> " << endl
                << "improve <criterion#> " << endl
                << "trade <colour> <give> <take> " << endl
                << "next " << endl 
                << "save <file> " << endl
                << "help" << endl;
            }
            else {
                cout << "Invalid Command; type help for a list of commands." << endl;
            }
        }
    }
}