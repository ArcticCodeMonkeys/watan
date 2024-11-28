#include "goal.h"
#include "player.h"

Player* Goal::getPlayer() {
    return player;
}
        
void Goal::setPlayer(Player* p) {
    player = p;
}
    
vector<Goal*> Goal::getAdjacents() {
    return adjacents;
}

void Goal::addAdjacent(Goal* g) {
    adjacents.emplace_back(g);
}

int Goal::getIndex() {
    return index;
}

Goal::Goal(int idx): index{idx} {
}

string Goal::printOwner() {
    if (player != nullptr) {
        char name = player->getName();
        return " " + string(1, name);
    } else {
        if (index < 10) {
            return " " + to_string(index);
        } else {
            return to_string(index);
        }
    }
}
