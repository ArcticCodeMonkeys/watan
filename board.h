#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Tile;
class Goal;
class Criterion;
class Player;

class Board {
    Tile *tiles[19];
    Goal *goals[71];
    Criterion *criteria[53];
    public:
        Board();
        Board(map<string, int> hands [], Player *goalOwners[], Player *criteriaOwners[], int typeArray[], int tile[19][2], int geeseTile);
        Board(int tile[19][2]);
        void tileLinking();
        friend std::ostream &operator<<(std::ostream &out, const Board &board);
        void saveBoard();
        Tile** getTiles();
        Criterion** getCriteria();
        Goal** getGoals();
        //void loadBoard(bool random, int seed = 0, std::string boardFile = "");
        //void loadGame(bool random, int seed = 0, std::string gameFile = "");
};
#endif
