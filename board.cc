#include "board.h"
const int TILE_COUNT = 19;
const int GOAL_COUNT = 71;
const int CRITERIA_COUNT = 53;
class Board {
    Tile *tiles[TILE_COUNT];
    Goal *goals[GOAL_COUNT];
    Criterion *criteria[CRITERIA_COUNT];
    public:
    Board() {
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
            {0, 1, 3, 4, 8, 9},
            {2, 3, 7, 8, 13, 14},
            {4, 5, 9, 10, 15, 16},
            {6, 7, 12, 13, 18, 19},
            {8, 9, 14, 15, 20, 21},
            {10, 11, 16, 17, 22, 23},
            {13, 14, 19, 20, 25, 26},
            {15, 16, 21, 22, 27, 28},
            {18, 19, 24, 25, 30, 31},
            {20, 21, 26, 27, 32, 33},
            {22, 23, 28, 29, 24, 25},
            {25, 26, 31, 32, 37, 38},
            {27, 28, 33, 34, 39, 40},
            {30, 31, 36, 37, 42, 43},
            {32, 33, 38, 39, 44, 45},
            {34, 35, 40, 41, 46, 47},
            {37, 38, 43, 44, 48, 49},
            {39, 40, 45, 46, 50, 51},
            {44, 45, 49, 50, 52, 53}
        };
        int goalMap[TILE_COUNT][6] = {
            {0, 1, 2, 6, 7, 10},
            {3, 5, 6, 13, 14, 18},
            {4, 7, 8, 15, 16, 19},
            {9, 12, 13, 20, 21, 0},
            {10, 14, 15, 22, 23, 27},
            {11, 16, 17, 24, 25, 28},
            {18, 21, 22, 30, 31, 35},
            {19, 23, 24, 32, 33, 36},
            {26, 29, 30, 37, 38, 43},
            {27, 31, 32, 39, 40, 44},
            {28, 33, 34, 41, 42, 45},
            {35, 38, 39, 47, 48, 52},
            {36, 40, 41, 49, 50, 53},
            {43, 46, 47, 54, 55, 60},
            {44, 48, 49, 56, 57, 61},
            {45, 50, 51, 58, 59, 62},
            {52, 55, 56, 63, 64, 67},
            {53, 57, 58, 65, 66, 68},
            {61, 64, 65, 69, 70, 71}
        };
        for (int i = 0; i < TILE_COUNT; ++i) {
            for (int k = 0; k < 6; ++k) {
                tiles[i]->criteria[k] = criteria[criteriaMap[i][k]];
                criteriaMap
            }
        }
        for (int i = 0; i < TILE_COUNT; ++i) {
            for (int k = 0; k < 6; ++k) {
                tiles[i]->goals[k] = goals[goalMap[i][k]];
            }
        }
    }
    std::ostream &operator<<(std::ostream &out) {
        
    }
};