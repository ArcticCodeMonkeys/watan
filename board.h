#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <map>

class Tile;
class Goal;
class Criterion;

class Board {
    Tile *tiles[19];
    Goal *goals[71];
    Criterion *criteria[53];
    public:
        Board();
        Board(map<string, int> hands [], Player *goalOwners[], Player *criteriaOwners[], int typeArray[], int tile[19][2], int geeseTile);
        Board(int tile[19][2]);
        friend std::ostream& operator<<(std::ostream& out, const Board& board);
        void saveBoard();
        Tile** getTiles();
        //void loadBoard(bool random, int seed = 0, std::string boardFile = "");
        //void loadGame(bool random, int seed = 0, std::string gameFile = "");
};
#endif
