#include "goal.h"
#include "tile.h"
class Criterion {
    //need to add an index parameter which begins at -1
    enum class Type {ASSIGNMENT, MIDTERM, EXAM};
    int index;
    
    Goal *adjacents[3];
    Tile *tile [3];
    public:
        Type type;
        Player *player;
        Criterion(int index);
        void printType();
        char getType();
};