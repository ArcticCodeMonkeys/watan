#ifndef GOAL_H
#define GOAL_H
using namespace std;
#include <vector>
#include <string>

class Player;

class Goal {
    //need to add an index parameter which begins at -1
    Player *player;
    int index;
    vector<Goal*> adjacents;
    public:
        Player* getPlayer();
        void setPlayer(Player* p);
        vector<Goal*> getAdjacents();
        Goal();
        string printOwner();
};
#endif
