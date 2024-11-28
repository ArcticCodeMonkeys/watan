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
    public:
        Player* getPlayer();
        void setPlayer(Player* p);
        vector<Goal*> getAdjacents();
        void addAdjacent(Goal* g);
        int getIndex();
        Goal(int idx);
        string printOwner();
};
#endif
