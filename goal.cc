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


Goal::Goal(): player{nullptr}, index{-1}, adjacents{nullptr} {
    for (int i = 0; i < 3; i++) {
        adjacents[i] = nullptr;
    }
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