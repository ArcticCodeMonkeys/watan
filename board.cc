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
        for (int j = 0; j < criteria[i]->getTiles().size(); j++) {
            for (int k = 0; k < 6; k++) {
                if (criteria[i]->getTiles()[j]->getCriteria(k) == criteria[i]) {
                    criteria[i]->addAdjacent(criteria[i]->getTiles()[j]->getGoal(k % 6));
                    criteria[i]->addAdjacent(criteria[i]->getTiles()[j]->getGoal((k - 1 + 6) % 6));
                }
            }
        }
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
    string resources[] = {"CAFFIENE", "LAB", "LECTURE", "STUDY", "TUTORIAL", "NETFLIX"};
    for (int i = 0; i < TILE_COUNT; i++) {
        tiles[i] = new Tile(tile[i][1], resources[tile[i][0]], (i == geeseTile));
    }
    for (int i = 0; i < GOAL_COUNT; i++ ) {
        goals[i] = new Goal(i, nullptr); //update
        if(goalOwners[i]) {
            goalOwners[i]->achieveGoal(goals[i], true);
        }
    }

    for (int i = 0; i < CRITERIA_COUNT; i++ ) {
        criteria[i] = new Criterion(i, nullptr, typeArray[i]); //update
        if(criteriaOwners[i]) {
            criteriaOwners[i]->completeCriterion(criteria[i], true);
        }
    }
    tileLinking();

}

Board::Board(int tile[19][2]) {
    string resources[] = {"CAFFIENE", "LAB", "LECTURE", "STUDY", "TUTORIAL", "NETFLIX"}; 
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

std::ostream& operator<<(std::ostream& out, const Board& board) {
    for(int i = 0; i < TILE_COUNT; i++) {
        out << "      |" << board.tiles[i]->getCriteria(0)->printOwner() << "|--" << board.tiles[i]->getGoal(0)->printOwner() << "--|" << board.tiles[i]->getCriteria(1)->printOwner() << "|      " << endl;
        out << "      /            \\     " << endl;
        out << "    " << board.tiles[i]->getGoal(5)->printOwner() << "      " << board.tiles[i]->printIndex(i) << "      " << board.tiles[i]->getGoal(1)->printOwner() << "    " << endl;
        out << "   /" << board.tiles[i]->printResource() << "\\  " << endl;
        out << "|" << board.tiles[i]->getCriteria(5)->printOwner() << "|        " << board.tiles[i]->printRollingValue() << "        |" << board.tiles[i]->getCriteria(2)->printOwner() << "|" << endl;
        out << "   \\      " << (board.tiles[i]->getGeese() ? "GEESE" : "     ") << "       /  " << endl;
        out << "    " << board.tiles[i]->getGoal(4)->printOwner() << "              " << board.tiles[i]->getGoal(2)->printOwner() << "    " << endl;
        out << "      \\            /      " << endl;
        out << "      |" << board.tiles[i]->getCriteria(4)->printOwner() << "|--" << board.tiles[i]->getGoal(3)->printOwner() << "--|" << board.tiles[i]->getCriteria(3)->printOwner() << "|      " << endl;
        out << endl;
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