#ifndef CRITERION_H
#define CRITERION_H
#include <iostream>
#include "observer.h"
class Player;
class Goal;
class Tile;

class Criterion: public Observer {
    //need to add an index parameter which begins at -1
    enum class Type {EMPTY, ASSIGNMENT, MIDTERM, EXAM};
    Type type;
    int index;
    Player *player;
    vector<Goal*> adjacents;
    vector<Criterion*> neighbors;
    Tile *tile [3];
    public:
        Criterion(int index);
        vector<Criterion*> getNeighbors();
        vector<Goal*> getAdjacents();
        Player* getPlayer();
        string printOwner();
        void printType();
        char getType();
        void setType(char t);
        int getIndex();
        Criterion();
        void notify(string resource);
        friend std::ostream &operator<<(std::ostream &out, const Criterion &criterion);
        Tile ** getTiles();
};
#endif
