#include "goal.h"
#include "player.h"

Goal::Goal(int idx, Player* p = nullptr): player{p}, index{idx}{}

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
