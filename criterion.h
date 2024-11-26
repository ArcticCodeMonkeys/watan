#include "goal.h"
class Criterion {
    //need to add an index parameter which begins at -1
    enum class Type {ASSIGNMENT, MIDTERM, EXAM};
    Type type;
    int index;
    Goal *adjacents[3];
    Tile *tile [3];
    public:
        Criterion(int index);
        void printType();
        char getType();
};