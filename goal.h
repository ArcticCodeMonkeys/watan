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
        Goal(int idx);
        Goal(int idx, Player* p);
        Player* getPlayer();
        void setPlayer(Player* p);
        vector<Goal*> getAdjacents();
        void addAdjacent(Goal* g);
        int getIndex();
        string printOwner();
};
#endif
