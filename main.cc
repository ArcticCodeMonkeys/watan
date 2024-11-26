#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "player.h"
#include "board.h"
const int NUM_PLAYERS = 4;
using namespace std;

int main(int argc, char* argv[]) {
    //Stage 1: Load States
    Player students[NUM_PLAYERS];
    char turnOrder[NUM_PLAYERS] = {'B', 'R', 'O', 'Y'};
    for (int i = 0; i < NUM_PLAYERS; i++) {
        students[i] = new Player();
        students[i].name = turnOrder[i];
    }
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
        map<string, int> total_resources [NUM_PLAYERS];
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
        Board game = new Board(total_resources, goalOwners, criterionOwners, typeArray, tile, geeseTile);
    }
    else if (boardFile != "") {
        // load board
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
        Board game = new Board (tile);
    }
    else {
        // load random board
        Board game = new Board();
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
        //Step 1: Set the Dice
        Player current = students[currentTurn];
        cout << "Student " << current.name << "'s Turn" << endl;
        current.printStatus();
        string rollCommand;
        while(getline(cin, rollCommand)) {
            if(rollCommand == "roll") {
                break;
            } else if (rollCommand == "load") {
                current.useLoadedDice = true;
                current.lDice.fixedVal << cin;
            } else if (rollCommand == "fair") {
                current.useLoadedDice = false;
            } else {
                cout << "Invalid Command; try either roll, load x, or fair." << endl;
            }
        }
        //Step 2: Roll the Dice
        int diceRoll = current.rollDice();
        if(diceRoll == 7) {
            //GOOSE!
            for(int i = 0; i < NUM_PLAYERS; i++) {
                int cardCount = 0;
                for(auto it = students[i].resources.begin(); it != students[i].resources.end(); ++it) {
                    cardCount += it->second;
                }
                if(cardCount >= 10) {
                    int disappeared = cardCount / 2;
                    map<string, int> lostResources;
                    while (disappeared > 0) {
                        int disappearType = rand() % 5;
                        string disappearString;
                        if (disappearType == 0) {
                            disappearString = "CAFFEINE";
                        } else if (disappearType == 1) {
                            disappearString = "LAB";
                        } else if (disappearType == 2) {
                            disappearString = "LECTURE";
                        } else if (disappearType == 3) {
                            disappearString = "STUDY";
                        } else if (disappearType == 4) {
                            disappearString = "TUTORIAL";
                        }
                        if (students[i].resources[disappearString] > 0) {
                            students[i].resources[disappearString] -= 1;
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

            if(!(board->tile[index].goosed)) {
                for(int i = 0; i < 19; i++) {
                    if(board->tile[i].goosed) {
                        board->tile[i].goosed = false;
                    }
                }
                board->tile[index].goosed = true;
            }
            string stealFrom [6];
            for (int i = 0; i < 6 ; i++) {
                string name = board->tile[index]->criteria[i]->player.name;
                if (name != current.name) {
                    stealFrom[i] = name;
                }
            }
            if (stealFrom[0] == "") {
                cout << "Student " << current.name << " has no students to steal from." << endl;
            }
            else {
                cout << "Student " << current.name << "can choose to steal from ";
                for (int j = 0; j < NUM_PLAYERS; j++) {
                    if (students[j].name != current.name) {
                        for (int i = 0; i < 6; i++) {
                            if (students[j].name == stealFrom[i]) {
                                cout << students[j].name << ", ";
                                break;
                            }
                        }
                    }
                }
            }
            cin >> command;
            for (int i = 0; i < NUM_PLAYERS; i++) {
                if (turnOrder[i] == command) {
                    int cardCount = 0;
                    for(auto it = students[i].resources.begin(); it != students[i].resources.end(); ++it) {
                        cardCount += it->second;
                    }
                    int randomCard = rand() % cardCount;
                    int cardType = 0;
                    for (auto it = students[i].resources.begin(); it != students[i].resources.end(); ++it) {
                        int val = it->second;
                        if (cardType + val > randomCard) {
                            students[i].resources[it->first] -= 1;
                            current.resources[it->first] += 1;
                            cout << "Student " << current.name << " steals " << it->first << " from " << turnOrder[i] << endl;
                            break;
                        }
                        cardType += val;
                    }
                    break;
                }
            }
        }
        else {
            //Step 3: Else, enerate resources for the tile
            for(int i = 0; i < 19; i++) {
                if(board->tile[i].value == diceRoll) {
                    board->tile[i].notifyObservers();
                }
            }
        }
        //Step 4: Action Time
        string command;
        while(cin >> command) {
            if (command == "next") {
                currentTurn = (currentTurn + 1) % 4;
                break;
            }
            else if (command == "board") {
                cout << board;
            }
            else if (command == "status") {
                for(int i = 0; i < NUM_PLAYERS; i++) {
                    cout << students[i];
                }
            }
            else if (command == "criteria") {
                for(auto it = students[currentTurn]->criteria.begin(); it != students[currentTurn]->criteria.end(); ++it) {
                    cout << it;
                }
            }
            else if (command == "achieve") {
                int index;
                cin >> index;
                current.achieveGoal(index);
            }
            else if (command == "complete") {
                int index;
                cin >> index;
                current.completeCriterion(index);
            }
            else if (command == "improve") {
                int index;
                cin >> index;
                current.improveCriterion(index);
            }
            else if (command == "trade") {
                string target;
                string give;
                string take;
                cin >> target;
                cin >> give;
                cin >> take;
                for (int i = 0; i < NUM_PLAYERS; i++) {
                    if (turnOrder[i] == target) {
                        current.trade(give, take, turn);
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
                    for (auto it = students[i].resources.begin(); it != students[i].resources.end(); ++it) {
                        saveStream << it->second << " ";
                    }
                    saveStream << "g ";
                    for (int j = 0; j < 71; j++) {
                        if (students[i].goals[j] != nullptr) {
                            saveStream << j << " ";
                        }
                    }
                    saveStream << "c ";
                    for (int j = 0; j < 53; j++) {
                        if (students[i].criteria[j] != nullptr) {
                            saveStream << j << " " << students[i].criteria[j]->type << " ";
                        }
                    }
                    saveStream << endl;
                }
                int resourceType = 0;
                int gooseTile = 0;
                for (int i = 0; i < 19; i++) {
                    string resourceType = board->tile[i].resourceType;
                    if (board->tile[i].goosed) {
                        gooseTile = i;
                    }
                    if (resourceType == "CAFFEINE") {
                        resourceType = 0;
                    } else if (resourceType == "LAB") {
                        resourceType = 1;
                    } else if (resourceType == "LECTURE") {
                        resourceType = 2;
                    } else if (resourceType == "STUDY") {
                        resourceType = 3;
                    } else if (resourceType == "TUTORIAL") {
                        resourceType = 4;
                    }
                    saveStream << resourceType << " " << board->tile[i].value << " ";
                }
                saveStream << endl;
                saveStream << gooseTile << endl;
            }
            else if (command == "help") {
                cout << "Valid commands: " << endl
                << "board " << endl
                << "status " << endl
                << "criteria " << endl
                << "achieve " << endl
                << "<goal> " << endl
                << "complete <criterion> " << endl
                << "improve <criterion> " << endl
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