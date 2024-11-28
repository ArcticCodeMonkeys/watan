#ifndef CRITERION_H
#define CRITERION_H
#include <iostream>
#include "observer.h"
#include <vector>
#include <string>
#include "goal.h"
#include "tile.h"
#include "player.h"
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
    vector<Tile*> tiles;
    public:
        Criterion(int index);
        vector<Criterion*> getNeighbors();
        vector<Goal*> getAdjacents();
        void addAdjacent(Goal *goal);
        Player* getPlayer();
        string printOwner();
        void printType();
        char getType();
        void setType(char t);
        int getIndex();
        Criterion();
        void notify(string resource);
        friend std::ostream &operator<<(std::ostream &out, const Criterion &criterion);
        vector<Tile*> getTiles();
        void setTile(int index, Tile *t);
        void addTile(Tile *t);
};
#endif
