#ifndef GOAL_H
#define GOAL_H
using namespace std;

class Player;

class Goal {
    //need to add an index parameter which begins at -1
    Player *player;
    int index;
    Goal *adjacents[3];
    public:
        Player* getPlayer();
        void setPlayer(Player* p);
        Goal* getAdjacent(int index);
        Goal();
};
#endif
