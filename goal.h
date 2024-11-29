#ifndef GOAL_H
#define GOAL_H
using namespace std;
#include <vector>
#include <string>

class Player;

class Goal {
    Player *player;
    int index;
    vector<Goal*> adjacents;
    vector<Criterion *> neighbors;
    public:
        Goal(int idx);
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
