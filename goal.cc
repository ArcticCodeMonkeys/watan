#include "goal.h"
#include "player.h"
#include "criterion.h"

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

vector<Criterion *> Goal::getNeighbors() {
    return neighbors;
}

void Goal::addNeighbor(Criterion* c) {
    neighbors.emplace_back(c);
}

int Goal::getIndex() {
    return index;
}

Goal::~Goal() {
    player = nullptr;
    for (size_t i = 0; i < adjacents.size(); ++i) {
        adjacents[i] = nullptr;
    }
    for (size_t i = 0; i < neighbors.size(); ++i) {
        neighbors[i] = nullptr;
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

void Goal::setAdjacents(vector<Goal*> adj) {
    adjacents = adj;
}
