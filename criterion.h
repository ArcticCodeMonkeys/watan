#include <iostream>

class Player;
class Goal;
class Tile;

class Criterion {
    //need to add an index parameter which begins at -1
    
    int index;
    
    Tile *tile [3];
    public:
        enum class Type {EMPTY, ASSIGNMENT, MIDTERM, EXAM};
        Type type;
        Criterion *neighbors[3];
        Goal *adjacents[3];
        Player *player;
        Criterion(int index);
        void printType();
        char getType();
};