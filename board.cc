#include "board.h"
#include "tile.h"
#include "goal.h"
#include "criterion.h"
#include "player.h"
const int TILE_COUNT = 19;
const int GOAL_COUNT = 72;
const int CRITERIA_COUNT = 54;


void Board::tileLinking() {
    int criteriaMap[TILE_COUNT][6] = {
        {0, 1, 4, 9, 8, 3},
        {2, 3, 8, 14, 13, 7},
        {4, 5, 10, 16, 15, 9},
        {6, 7, 13, 19, 18, 12},
        {8, 9, 15, 21, 20, 14},
        {10, 11, 17, 23, 22, 16},
        {13, 14, 20, 26, 25, 19},
        {15, 16, 22, 28, 27, 21},
        {18, 19, 25, 31, 30, 24},
        {20, 21, 27, 33, 32, 26},
        {22, 23, 29, 35, 24, 28},
        {25, 26, 32, 38, 37, 31},
        {27, 28, 34, 40, 39, 33},
        {30, 31, 37, 43, 42, 36},
        {32, 33, 39, 45, 44, 38},
        {34, 35, 41, 47, 46, 40},
        {37, 38, 44, 49, 48, 43},
        {39, 40, 46, 51, 50, 45},
        {44, 45, 50, 53, 52, 49}
    };
    int goalMap[TILE_COUNT][6] = {
        {0, 2, 7, 10, 6, 1},
        {3, 6, 14, 18, 13, 5},
        {4, 8, 16, 19, 15, 7},
        {9, 13, 21, 26, 20, 12},
        {10, 15, 23, 27, 22, 14},
        {11, 17, 25, 28, 24, 16},
        {18, 22, 31, 35, 30, 21},
        {19, 24, 33, 36, 32, 23},
        {26, 30, 38, 43, 37, 29},
        {27, 32, 40, 44, 39, 31},
        {28, 34, 42, 45, 41, 33},
        {35, 39, 48, 52, 47, 38},
        {36, 41, 50, 53, 49, 40},
        {43, 47, 55, 60, 54, 46},
        {44, 49, 57, 61, 56, 48},
        {45, 51, 59, 62, 58, 50},
        {52, 56, 64, 67, 63, 55},
        {53, 58, 66, 68, 65, 57},
        {61, 65, 70, 71, 69, 64}
    };
    for (int i = 0; i < TILE_COUNT; ++i) {
        for (int k = 0; k < 6; ++k) {
            tiles[i]->setCriteria(k, criteria[criteriaMap[i][k]]);
            criteria[criteriaMap[i][k]]->addTile(tiles[i]);
        }
    }
    
    for (int i = 0; i < TILE_COUNT; ++i) {
        for (int k = 0; k < 6; ++k) {
            tiles[i]->setGoals(k, goals[goalMap[i][k]]);
        }
    }
    
    for (int j = 0; j < TILE_COUNT; ++j) {
        for (int k = 0; k < 6; ++k) {
            int val = goalMap[j][k];
            goals[val]->addAdjacent(goals[goalMap[j][(k - 1 + 6)%6]]);
            goals[val]->addAdjacent(goals[goalMap[j][(k + 1)%6]]);
        }
    }
    
    for (int j = 0; j < TILE_COUNT; ++j) {
        for (int k = 0; k < 6; ++k) {
            int val = criteriaMap[j][k];
            criteria[val]->addNeighbor(criteria[criteriaMap[j][(k + 1) % 6]]);
            criteria[val]->addNeighbor(criteria[criteriaMap[j][(k - 1 + 6) % 6]]);
        }
    }
    for (int i = 0; i < CRITERIA_COUNT; i++) {
        for (size_t j = 0; j < criteria[i]->getTiles().size(); j++) {
            for (int k = 0; k < 6; k++) {
                if (criteria[i]->getTiles()[j]->getCriteria(k) == criteria[i]) {
                    criteria[i]->addAdjacent(criteria[i]->getTiles()[j]->getGoal(k % 6));
                    criteria[i]->addAdjacent(criteria[i]->getTiles()[j]->getGoal((k - 1 + 6) % 6));
                }
            }
        }
    }
    for (int i = 0; i < CRITERIA_COUNT; i++) {
        vector <Goal *> adj{};
        for (size_t j = 0; j < criteria[i]->getAdjacents().size(); j++) {
            bool seen = false;
            for(size_t k = 0; k < adj.size(); k++) {
                if(adj[k] == criteria[i]->getAdjacents()[j]) {
                    seen = true;
                }
            }
            if(!seen) {
                adj.emplace_back(criteria[i]->getAdjacents()[j]);
            }
        }
        criteria[i]->setAdjacents(adj);

    }
    

}

Board::Board() {
    
    vector<string> tileBag = {"TUTORIAL", "TUTORIAL", "TUTORIAL", "STUDY", "STUDY", "STUDY", "CAFFEINE", "CAFFEINE", "CAFFEINE", "CAFFEINE", "LAB", "LAB", "LAB", "LAB", "LECTURE", "LECTURE", "LECTURE", "LECTURE", "NETFLIX" };
    vector<int> valBag = {2, 12, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 7};
    int leftInBag = 19;
    
    for(int i = 0; i < 19; i++) {
        int index = rand() % leftInBag;
        int rollVal = valBag[index];
        string resource = tileBag[index];
        if(rollVal == 7) {
            tiles[i] = new Tile(7, "NETFLIX", true);
            valBag.erase(std::remove(valBag.begin(), valBag.end(), 7), valBag.end());
            tileBag.erase(std::remove(tileBag.begin(), tileBag.end(), "NETFLIX"), tileBag.end());
        } else {
            tiles[i] = new Tile(rollVal, resource, false);
            valBag.erase(valBag.begin() + index);
            tileBag.erase(tileBag.begin() + index);
        }
        leftInBag--;
    }
    
    for (int i = 0; i < GOAL_COUNT; ++i) {
        goals[i] = new Goal(i, nullptr);
    }
    
    for (int i = 0; i < CRITERIA_COUNT; ++i) {
        criteria[i] = new Criterion(i, nullptr, 0);
    }
    
    tileLinking();
}

Board::Board(Player *goalOwners[], Player *criteriaOwners[], int typeArray[], int tile[19][2], int geeseTile) {
    string resources[] = {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL", "NETFLIX"};
    for (int i = 0; i < TILE_COUNT; i++) {
        tiles[i] = new Tile(tile[i][1], resources[tile[i][0]], (i == geeseTile));
    }
    for (int i = 0; i < GOAL_COUNT; i++ ) {
        goals[i] = new Goal(i, nullptr); //update
        if(goalOwners[i]) {
            goalOwners[i]->achieveGoal(goals[i], true);
            goals[i]->setPlayer(goalOwners[i]);
        }
        
    }

    for (int i = 0; i < CRITERIA_COUNT; i++ ) {
        criteria[i] = new Criterion(i, nullptr, typeArray[i]); //update
        if(criteriaOwners[i]) {
            criteriaOwners[i]->completeCriterion(criteria[i], true);
            criteria[i]->setType(typeArray[i] == 0 ? '\0' : typeArray[i] == 1 ? 'A' : typeArray[i] == 2 ? 'M': 'E');
            criteriaOwners[i]->addVictoryPoints(typeArray[i]-1);
            criteria[i]->setPlayer(criteriaOwners[i]);
        }
    }
    tileLinking();

}

Board::Board(int tile[19][2]) {
    string resources[] = {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL", "NETFLIX"}; 
    for (int i = 0; i < TILE_COUNT; i++) {
        tiles[i] = new Tile(tile[i][1], resources[tile[i][0]], (resources[tile[i][0]] == "NETFLIX"));
    }
    for (int i = 0; i < GOAL_COUNT; i++ ) {
        goals[i] = new Goal(i, nullptr); //update
    }

    for (int i = 0; i < CRITERIA_COUNT; i++ ) {
        criteria[i] = new Criterion(i, nullptr, 0); //update
    }
    tileLinking();

}


string insertSpaces(int n) {
    string spaces = "";
    for (int i = 0; i < n; i++) {
        spaces += " ";
    }
    return spaces;
}

string printSide(Criterion * corner1, Goal * edge, Criterion *corner2) {
    string side = "|" + corner1->printOwner() + "|--" + edge->printOwner() + "--|" + corner2->printOwner() + "|";
    return side;
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
    for (int i = 0; i < 41; i++) {
        switch (i) {
            case 0:
                out << insertSpaces(39);
                out << printSide(board.criteria[0], board.goals[0], board.criteria[1]);
                out << insertSpaces(37);
                out << '\n';
                break;
            
            case 1:
                out << insertSpaces(39);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(33);
                out << '\n';
                break;
            case 2:
                out << insertSpaces(37);
                out << board.goals[1]->printOwner();
                out << insertSpaces(6);
                out << " 0";
                out << insertSpaces(5);
                out << board.goals[2]->printOwner();
                out << insertSpaces(36);
                out << '\n';
                break;
            case 3:
                out << insertSpaces(37);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[0]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << '\n';
                break;
            
            case 4:
                out << insertSpaces(24);
                out << printSide(board.criteria[2], board.goals[3], board.criteria[3]);
                out << insertSpaces(7);
                out << board.tiles[0]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[4], board.goals[4], board.criteria[5]);
                out << '\n';
                break;
            
            case 5:
                out << insertSpaces(24);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[0]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << '\n';
                break;
            
            case 6:
                out << insertSpaces(22);
                out << board.goals[5]->printOwner();
                out << insertSpaces(6);
                out << " 1";
                out << insertSpaces(5);
                out << board.goals[6]->printOwner();
                out << insertSpaces(13);
                out << board.goals[7]->printOwner();
                out << insertSpaces(6);
                out << " 2";
                out << insertSpaces(5);
                out << board.goals[8]->printOwner();
                out << '\n';
                break;
            
            case 7:
                out << insertSpaces(22);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[1]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[2]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << '\n';
                break;
            
            case 8:
                out << insertSpaces(9);
                out << printSide(board.criteria[6], board.goals[9], board.criteria[7]);
                out << insertSpaces(7);
                out << board.tiles[1]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[8], board.goals[10], board.criteria[9]);
                out << insertSpaces(7);
                out << board.tiles[2]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[10], board.goals[11], board.criteria[11]);
                out << '\n';
                break;
            
            case 9:
                out << insertSpaces(9);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[1]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[2]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << '\n';
                break;
            
            case 10:
                out << insertSpaces(7);
                out << board.goals[12]->printOwner();
                out << insertSpaces(6);
                out << " 3";
                out << insertSpaces(5);
                out << board.goals[13]->printOwner();
                out << insertSpaces(13);
                out << board.goals[14]->printOwner();
                out << insertSpaces(6);
                out << " 4";
                out << insertSpaces(5);
                out << board.goals[15]->printOwner();
                out << insertSpaces(13);
                out << board.goals[16]->printOwner();
                out << insertSpaces(6);
                out << " 5";
                out << insertSpaces(5);
                out << board.goals[17]->printOwner();
                out << '\n';
                break;
            
            case 11:
                out << insertSpaces(7);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[3]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[4]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[5]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << '\n';
                break;
            
            case 12:
                out << insertSpaces(4);
                out << '|';
                out << board.criteria[12]->printOwner();
                out << '|';
                out << insertSpaces(7);
                out << board.tiles[3]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[13], board.goals[18], board.criteria[14]);
                out << insertSpaces(7);
                out << board.tiles[4]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[15], board.goals[19], board.criteria[16]);
                out << insertSpaces(7);
                out << board.tiles[5]->printRollingValue();
                out << insertSpaces(7);
                out << '|';
                out << board.criteria[17]->printOwner();
                out << '|';
                out << '\n';
                break;

            case 13:
                out << insertSpaces(7);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[3]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[4]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[5]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << '\n';
                break;
            
            case 14:
                out << insertSpaces(7);
                out << board.goals[20]->printOwner();
                out << insertSpaces(13);
                out << board.goals[21]->printOwner();
                out << insertSpaces(6);
                out << " 6";
                out << insertSpaces(5);
                out << board.goals[22]->printOwner();
                out << insertSpaces(13);
                out << board.goals[23]->printOwner();
                out << insertSpaces(6);
                out << " 7";
                out << insertSpaces(5);
                out << board.goals[24]->printOwner();
                out << insertSpaces(13);
                out << board.goals[25]->printOwner();
                out << '\n';
                break;
            
            case 15:
                out << insertSpaces(9);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[6]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[7]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << '\n';
                break;
            
            case 16:
                out << insertSpaces(9);
                out << printSide(board.criteria[18], board.goals[26], board.criteria[19]);
                out << insertSpaces(7);
                out << board.tiles[6]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[20], board.goals[27], board.criteria[21]);
                out << insertSpaces(7);
                out << board.tiles[7]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[22], board.goals[28], board.criteria[23]);
                out << '\n';
                break;
            
            case 17:
                out << insertSpaces(9);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[6]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[7]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << '\n';
                break;

            case 18:
                out << insertSpaces(7);
                out << board.goals[29]->printOwner();
                out << insertSpaces(6);
                out << " 8";
                out << insertSpaces(5);
                out << board.goals[30]->printOwner();
                out << insertSpaces(13);
                out << board.goals[31]->printOwner();
                out << insertSpaces(6);
                out << " 9";
                out << insertSpaces(5);
                out << board.goals[32]->printOwner();
                out << insertSpaces(13);
                out << board.goals[33]->printOwner();
                out << insertSpaces(6);
                out << "10";
                out << insertSpaces(5);
                out << board.goals[34]->printOwner();
                out << '\n';
                break;

            case 19:
                out << insertSpaces(7);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[8]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[9]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[10]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << '\n';
                break;

            case 20:
                out << insertSpaces(4);
                out << '|';
                out << board.criteria[24]->printOwner();
                out << '|';
                out << insertSpaces(7);
                out << board.tiles[8]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[25], board.goals[35], board.criteria[26]);
                out << insertSpaces(7);
                out << board.tiles[9]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[27], board.goals[36], board.criteria[28]);
                out << insertSpaces(7);
                out << board.tiles[10]->printRollingValue();
                out << insertSpaces(7);
                out << '|';
                out << board.criteria[29]->printOwner();
                out << '|';
                out << '\n';
                break;
            
            case 21:
                out << insertSpaces(7);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[8]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[9]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[10]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << '\n';
                break;
            
            case 22:
                out << insertSpaces(7);
                out << board.goals[37]->printOwner();
                out << insertSpaces(13);
                out << board.goals[38]->printOwner();
                out << insertSpaces(6);
                out << "11";
                out << insertSpaces(5);
                out << board.goals[39]->printOwner();
                out << insertSpaces(13);
                out << board.goals[40]->printOwner();
                out << insertSpaces(6);
                out << "12";
                out << insertSpaces(5);
                out << board.goals[41]->printOwner();
                out << insertSpaces(13);
                out << board.goals[42]->printOwner();
                out << '\n';
                break;
            
            case 23:
                out << insertSpaces(9);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[11]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[12]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << '\n';
                break;
            
            case 24:
                out << insertSpaces(9);
                out << printSide(board.criteria[30], board.goals[43], board.criteria[31]);
                out << insertSpaces(7);
                out << board.tiles[11]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[32], board.goals[44], board.criteria[33]);
                out << insertSpaces(7);
                out << board.tiles[12]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[34], board.goals[45], board.criteria[35]);
                out << '\n';
                break;
            
            case 25:
                out << insertSpaces(9);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[11]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[12]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << '\n';
            
                break;
            case 26:
                out << insertSpaces(7);
                out << board.goals[46]->printOwner();
                out << insertSpaces(6);
                out << "13";
                out << insertSpaces(5);
                out << board.goals[47]->printOwner();
                out << insertSpaces(13);
                out << board.goals[48]->printOwner();
                out << insertSpaces(6);
                out << "14";
                out << insertSpaces(5);
                out << board.goals[49]->printOwner();
                out << insertSpaces(13);
                out << board.goals[50]->printOwner();
                out << insertSpaces(6);
                out << "15";
                out << insertSpaces(5);
                out << board.goals[51]->printOwner();
                out << '\n';
                break;
            
            case 27:
                out << insertSpaces(7);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[13]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[14]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[15]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << '\n';
                break;
            
            case 28:
                out << insertSpaces(4);
                out << '|';
                out << board.criteria[36]->printOwner();
                out << '|';
                out << insertSpaces(7);
                out << board.tiles[13]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[37], board.goals[52], board.criteria[38]);
                out << insertSpaces(7);
                out << board.tiles[14]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[39], board.goals[53], board.criteria[40]);
                out << insertSpaces(7);
                out << board.tiles[15]->printRollingValue();
                out << insertSpaces(7);
                out << '|';
                out << board.criteria[41]->printOwner();
                out << '|';
                out << '\n';
                break;
            
            case 29:
                out << insertSpaces(7);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[13]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[14]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[15]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << '\n';
                break;
            
            case 30:
                out << insertSpaces(7);
                out << board.goals[54]->printOwner();
                out << insertSpaces(13);
                out << board.goals[55]->printOwner();
                out << insertSpaces(6);
                out << "16";
                out << insertSpaces(5);
                out << board.goals[56]->printOwner();
                out << insertSpaces(13);
                out << board.goals[57]->printOwner();
                out << insertSpaces(6);
                out << "17";
                out << insertSpaces(5);
                out << board.goals[58]->printOwner();
                out << insertSpaces(13);
                out << board.goals[59]->printOwner();
                out << '\n';
                break;
            
            case 31:
                out << insertSpaces(9);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[16]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[17]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << '\n';
                break;
            
            case 32:
                out << insertSpaces(9);
                out << printSide(board.criteria[42], board.goals[60], board.criteria[43]);
                out << insertSpaces(7);
                out << board.tiles[16]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[44], board.goals[61], board.criteria[45]);
                out << insertSpaces(7);
                out << board.tiles[17]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[46], board.goals[62], board.criteria[47]);
                out << '\n';
                break;
            
            case 33:
                out << insertSpaces(22);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[16]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << insertSpaces(12);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[17]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << '\n';
                break;
            
            case 34:
                out << insertSpaces(22);
                out << board.goals[63]->printOwner();
                out << insertSpaces(13);;
                out << board.goals[64]->printOwner();
                out << insertSpaces(6);
                out << "18";
                out << insertSpaces(5);
                out << board.goals[65]->printOwner();
                out << insertSpaces(13);
                out << board.goals[66]->printOwner();
                out << '\n';
                break;
            
            case 35:
                out << insertSpaces(24);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(5);
                out << board.tiles[18]->printResource();
                out << insertSpaces(3);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << '\n';
                break;
            
            case 36:
                out << insertSpaces(24);
                out << printSide(board.criteria[48], board.goals[67], board.criteria[49]);
                out << insertSpaces(7);
                out << board.tiles[18]->printRollingValue();
                out << insertSpaces(7);
                out << printSide(board.criteria[50], board.goals[68], board.criteria[51]);
                out << '\n';
                break;
            
            case 37:
                out << insertSpaces(37);
                out << '\\';
                out << insertSpaces(5);
                out << board.tiles[18]->printGeese();
                out << insertSpaces(6);
                out << '/';
                out << '\n';
                break;
            case 38:
                out << insertSpaces(37);
                out << board.goals[69]->printOwner();
                out << insertSpaces(14);
                out << board.goals[70]->printOwner();
                out << insertSpaces(35);
                out << '\n';
                break;
            case 39:
                out << insertSpaces(39);
                out << '\\';
                out << insertSpaces(12);
                out << '/';
                out << insertSpaces(33);
                out << '\n';
                break;
            case 40:
                out << insertSpaces(39);
                out << printSide(board.criteria[52], board.goals[71], board.criteria[53]);
                out << insertSpaces(37);
                out << '\n';
                break;
        }
    }
    return out;
}

Tile ** Board::getTiles() {
    return tiles;
}

Criterion ** Board::getCriteria() {
    return criteria;
}

Goal ** Board::getGoals() {
    return goals;
}