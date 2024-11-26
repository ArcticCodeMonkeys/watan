#include "board.h"
#include "tile.h"
#include "goal.h"
#include "criterion.h"

const int TILE_COUNT = 19;
const int GOAL_COUNT = 71;
const int CRITERIA_COUNT = 53;
Board::Board() {
    for (int i = 0; i < TILE_COUNT; ++i) {
        tiles[i] = new Tile();
    }
    for (int i = 0; i < GOAL_COUNT; ++i) {
        goals[i] = new Goal();
    }
    for (int i = 0; i < CRITERIA_COUNT; ++i) {
        criteria[i] = new Criterion();
    }
    int criteriaMap[TILE_COUNT][6] = {
        {0, 1, 4, 9, 8, 3},
        {2, 3, 8, 14, 13, 7},
        {4, 5, 10, 16, 15, 9},
        {6, 7, 13, 19, 18, 12},
        {8, 9, 14, 21, 20, 14},
        {10, 11, 16, 23, 22, 16},
        {13, 14, 20, 26, 25, 19},
        {15, 16, 22, 28, 27, 21},
        {18, 19, 25, 31, 30, 24},
        {20, 21, 27, 33, 32, 26},
        {22, 23, 29, 25, 24, 28},
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
        {9, 13, 21, 0, 20, 12},
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
        }
    }
    for (int i = 0; i < TILE_COUNT; ++i) {
        for (int k = 0; k < 6; ++k) {
            tiles[i]->setCriteria(k, goals[goalMap[i][k]]);
        }
    }
}

Board::Board(map<string, int> hands, Player *goalOwners[], Player *criteriaOwners[], int typeArray[], int *tile[], int geeseTile) {

}

Tile ** Board::getTiles() {
    return tiles;
}