#include <iostream>
#include "tile.h"
#include "goal.h"
#include "criterion.h"

class Board {
    Tile *tiles[19];
    Goal *goals[71];
    Criterion *criteria[53];
    public:
        std::ostream &operator<<(std::ostream &out);
        void saveBoard();
        void loadBoard(bool random, int seed = 0);
};
