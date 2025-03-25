#ifndef GOAL_H
#define GOAL_H
#include <vector>
#include <string>
using namespace std;

class Player;
class Criterion;

class Goal {
    Player *player;
    int index;
    vector<Goal*> adjacents;
    vector<Criterion *> neighbors;
    public:
        Goal(int idx, Player* p);
        ~Goal();
        Player* getPlayer();
        void setPlayer(Player* p);
        vector<Goal*> getAdjacents();
        void addAdjacent(Goal* g);
        vector<Criterion *> getNeighbors();
        void addNeighbor(Criterion *c);
        int getIndex();
        string printOwner();
        void setAdjacents(vector<Goal*> adj);
};
#endif
