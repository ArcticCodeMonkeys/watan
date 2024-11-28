#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "player.h"
#include "board.h"
#include "tile.h"
#include "criterion.h"
const int NUM_PLAYERS = 4;
const int GOAL_COUNT = 72;
const int CRITERIA_COUNT = 54;
using namespace std;

int main(int argc, char* argv[]) {
    
    Board game;
    cout << "Welcome to the Game of Goose!" << endl;
    Player students[NUM_PLAYERS];
    char turnOrder[NUM_PLAYERS] = {'B', 'R', 'O', 'Y'};
    string resourcesArr[6] = {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL" ,"NETFLIX"};
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
        if(!fileStream) {
            cout << "Could not locate file" << endl;
            return 0;
        }
        string line;
        getline(fileStream, line);
        currentTurn = stoi(line);
        // load players
        Player *goalOwners[GOAL_COUNT] = {nullptr}; 
        Player *criterionOwners [CRITERIA_COUNT] = {nullptr};
        int typeArray [CRITERIA_COUNT];
        // loop through players, storing data
        for (int i = 0; i < NUM_PLAYERS; i++) {
            string l;
            if(!getline(fileStream, l))  {
                cout << "Could not read file" << endl;
                return 0;
            }
            istringstream iss{l};
            string readValue;
            int count = 0;
            // read resources
            while (count < 5 && iss >> readValue) {
                students[i].addResources(resourcesArr[count], stoi(readValue));
                count++;
            }
            
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
                count++;
            }
        }

        // load board
        getline(fileStream, line);
        istringstream iss{line};
        string readValue;
        string readResource;
        int tile [19][2];
        int count_resource = 0;
        int count_roll = 0;
        while (iss >> readValue) {
            if (count_resource == count_roll) {
                int resourceType = stoi(readValue);
                tile[count_resource][0] = resourceType;
                count_resource++;
            }
            else {
                int rollingValue = stoi(readValue);
                tile[count_roll][1] = rollingValue;
                count_roll++;
            }
            
        }
        // geese tile number
        getline(fileStream, line);
        int geeseTile = stoi(line);
        game = Board(goalOwners, criterionOwners, typeArray, tile, geeseTile);
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
    } else {
        // otherwise random board is loaded

        //Stage 2: Initial Assignment purchasing
        for(int i = 0; i < NUM_PLAYERS; i++) {
            cout << "Student " << turnOrder[i] << ", where do you want to complete an Assignment?" << endl;
            int index;
            cout << "> ";
            cin >> index;
            if(!students[i].completeCriterion(game.getCriteria()[index], true)) {
                i--;
                continue;
            }
            bool adj = false;
            while(!adj) {
                cout << "Student " << turnOrder[i] << ", achieve an adjacent Goal on either ";
                for(int i = 0; i < game.getCriteria()[index]->getAdjacents().size(); i++) {
                    cout << game.getCriteria()[index]->getAdjacents()[i]->getIndex();
                    if(i < game.getCriteria()[index]->getAdjacents().size() - 1) {
                        cout << " or ";
                    }
                }
                int goalIndex;
                cout << endl;
                cout << "> ";
                cin >> goalIndex;
                for(int i = 0; i < game.getCriteria()[index]->getAdjacents().size(); i++) {
                    if(game.getCriteria()[index]->getAdjacents()[i]->getIndex() == goalIndex) {
                        adj = true;
                        break;
                    }
                }
                if(adj && students[currentTurn].achieveGoal(game.getGoals()[goalIndex], true)) {
                } else {
                    cout << "That is not a valid placement, try again" << endl;
                }
            }
        }
        for(int i = NUM_PLAYERS - 1; i >= 0; i--) {
            cout << "Student " << turnOrder[i] << ", where do you want to complete an Assignment?" << endl;
            int index;
            cout << "> ";
            cin >> index;
            if(!students[i].completeCriterion(game.getCriteria()[index], true)) {
                i++;
                continue;
            }
            bool adj = false;
            while(!adj) {
                cout << "Student " << turnOrder[i] << ", achieve an adjacent Goal on either ";
                for(int i = 0; i < game.getCriteria()[index]->getAdjacents().size(); i++) {
                    cout << game.getCriteria()[index]->getAdjacents()[i]->getIndex();
                    if(i < game.getCriteria()[index]->getAdjacents().size() - 1) {
                        cout << " or ";
                    }
                }
                int goalIndex;
                cout << endl;
                cout << "> ";
                cin >> goalIndex;
                for(int i = 0; i < game.getCriteria()[index]->getAdjacents().size(); i++) {
                    if(game.getCriteria()[index]->getAdjacents()[i]->getIndex() == goalIndex) {
                        adj = true;
                        break;
                    }
                }
                if(adj && students[currentTurn].achieveGoal(game.getGoals()[goalIndex], true)) {
                } else {
                    cout << "That is not a valid placement, try again" << endl;
                }
            }
        }
    }
    


    //Stage 3: The Game
    bool gameLoop = true;
    while(gameLoop) {
        //Step 1: Set the Dice
        cout << "Student " << students[currentTurn].getName() << "'s Turn" << endl;
        cout << students[currentTurn];
        string rollCommand;
        
        while(true) {
            cout << "> ";
            cin >> rollCommand;
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
            /* for(int i = 0; i < NUM_PLAYERS; i++) {
            for(int i = 0; i < NUM_PLAYERS; i++) {
                for (int j = 0; j < 6; j++) {
                    cout << resourcesArr[j] << ": " << students[i].getResources()[resourcesArr[j]] << endl;
                }
                int cardCount = 0;
                int cardCountArr []= {0, 0, 0, 0, 0, 0};
                for (const auto& it : students[i].getResources()) {
                    cardCount += it.second;
                    for (int j = 0; j < 6; j++) {
                        if (it.first == resourcesArr[j]) {
                            cardCountArr[j] = it.second;
                        }
                    }
                }
                if (cardCount >= 10) {
                    int discardCount = cardCount / 2;
                    int stolen = 0;
                    while (stolen < discardCount) {
                        int randomCard = rand() % cardCount;
                        for (int j = 0; j < 6; j++) {
                            if (randomCard < cardCountArr[j]) {
                                cardCountArr[j]--;
                                stolen++;
                                break;
                            }
                            randomCard -= cardCountArr[j];
                        }
                    }
                    map<string, int> lostResources;
                    for (int j = 0; j < 6; j++) {
                        lostResources[resourcesArr[j]] = students[i].getResources()[resourcesArr[j]] - cardCountArr[j];
                        students[i].takeResources(resourcesArr[j], lostResources[resourcesArr[j]]);
                    }
                    
                }
                
                cout << "Student " << students[i].getName() << " has lost resources." << endl;
                for (int j = 0; j < 6; j++) {
                    cout << resourcesArr[j] << ": " << students[i].getResources()[resourcesArr[j]] << endl;
                }
            }
            
            cout << "Choose where to place the GEESE." << endl;
            int index;
            cout << "> ";
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
            cout << "> ";
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
        while(true) {
            cout << "> ";
            cin >> command;
            if (command == "next") {
                currentTurn = (currentTurn + 1) % 4;
                break;
            }
            else if (command == "board") {
                cout << game;
            }
            else if (command == "status") {
                for(int i = 0; i < NUM_PLAYERS; i++) {
                    cout << students[i];
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