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
    Goal *goals[72];
    Criterion *criteria[54];
    public:
        Board();
        Board(Player *goalOwners[], Player *criteriaOwners[], int typeArray[], int tile[19][2], int geeseTile);
        Board(int tile[19][2]);
        ~Board();
        void tileLinking();
        friend std::ostream &operator<<(std::ostream &out, const Board &board);
        Tile** getTiles();
        Criterion** getCriteria();
        Goal** getGoals();
};
#endif
