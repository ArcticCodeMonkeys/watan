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
    enum class Type {EMPTY, ASSIGNMENT, MIDTERM, EXAM};
    Type type;
    int index;
    Player *player;
    vector<Goal*> adjacents;
    vector<Criterion*> neighbors;
    vector<Tile*> tiles;
    public:
        Criterion(int index, Player *p, int type);
        ~Criterion();
        vector<Criterion*> getNeighbors();
        void addNeighbor(Criterion *c);
        vector<Goal*> getAdjacents();
        void addAdjacent(Goal *goal);
        void setAdjacents(vector<Goal*> goals);
        Player* getPlayer();
        void setPlayer(Player *p);
        string printOwner();
        void printType();
        char getType();
        void setType(char t);
        int getIndex();
        void notify(string resource) override;
        vector<Tile*> getTiles();
        void setTile(int index, Tile *t);
        void addTile(Tile *t);
};
#endif
