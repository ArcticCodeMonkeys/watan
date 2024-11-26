#include "goal.h"
#include "player.h"


Player* Goal::getPlayer() {
    return player;
}
        
void Goal::setPlayer(Player* p) {
    player = p;
}
    
Goal* Goal::getAdjacent(int index) {
    return adjacents[index];
}


Goal::Goal(): player{nullptr}, index{-1}, adjacents{nullptr} {
    for (int i = 0; i < 3; i++) {
        adjacents[i] = nullptr;
    }
}
