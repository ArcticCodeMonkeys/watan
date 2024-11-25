#ifndef BOARD_H
#define BOARD_H
#include <iostream>


class Tile;
class Goal;
class Criterion;

class Board {
    Tile *tiles[19];
    Goal *goals[71];
    Criterion *criteria[53];
    public:
        Board();
        Board(int tile[19][2]);
        std::ostream &operator<<(std::ostream &out);
        void saveBoard();
        Tile** getTiles();
        //void loadBoard(bool random, int seed = 0, std::string boardFile = "");
        //void loadGame(bool random, int seed = 0, std::string gameFile = "");
};
#endif
