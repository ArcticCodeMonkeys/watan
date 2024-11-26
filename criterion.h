#ifndef CRITERION_H
#define CRITERION_H
#include <iostream>

class Player;
class Goal;
class Tile;

class Criterion {
    //need to add an index parameter which begins at -1
    enum class Type {EMPTY, ASSIGNMENT, MIDTERM, EXAM};
    Type type;
    int index;
    Player *player;
    Goal *adjacents[3];
    Criterion *neighbors[3];
    Tile *tile [3];
    public:
        Criterion(int index);
        Criterion* getNeighbors(int index);
        Goal* getAdjacents(int index);
        Player* getPlayer();
        void printType();
        char getType();
        void setType(char t);
};
#endif
