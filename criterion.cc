#include "criterion.h"

Criterion::Criterion(int index, Player *p = nullptr, int type = 0): index{index}, player{p}, type{(type == 0 ? Type::EMPTY : type == 1 ? Type::ASSIGNMENT : 
type == 2 ? Type::MIDTERM : Type::EXAM)} {}

vector<Criterion*> Criterion::getNeighbors() {
    return neighbors;
}

vector<Goal*> Criterion::getAdjacents() {
    return adjacents;
}

string Criterion::printOwner() {
    if (player != nullptr) {
        char name = player->getName();
        char getType = this->getType();
        return string(1, name) + getType;
    } else {
        if (index < 10) {
            return " " + to_string(index);
        } else {
            return to_string(index);
        }
    }
}


Player* Criterion::getPlayer() {
    return player;
}

void Criterion::printType() {
    if (type == Type::ASSIGNMENT) {
        cout << "Assignment";
    } else if (type == Type::MIDTERM) {
        cout << "Midterm";
    } else {
        cout << "Exam";
    }
}

char Criterion::getType() {
    if (type == Type::ASSIGNMENT) {
        return 'A';
    } else if (type == Type::MIDTERM) {
        return 'M';
    } else if (type == Type::EXAM) {
        return 'E';
    } else {
        return '\0';
    }
}

void Criterion::setType(char t) {
    if(t == '\0') {
        type = Criterion::Type::EMPTY;
    } else if (t == 'A')
    {
        type = Criterion::Type::ASSIGNMENT;
    } else if (t == 'M')
    {
        type = Criterion::Type::MIDTERM;
    } else if (t == 'E') {
        type = Criterion::Type::EXAM;
    }
    
}

void Criterion::notify(std::string resource) {
    if (player != nullptr) {
        int resourceAmount = 0;
        if (type == Type::ASSIGNMENT) {
            resourceAmount = 1;
        } else if (type == Type::MIDTERM) {
            resourceAmount = 2;
        } else if (type == Type::EXAM) {
            resourceAmount = 3;
        }
        player->addResources(resource, resourceAmount);
    }
}
int Criterion::getIndex() {
    return index;
}

vector<Tile*> Criterion::getTiles() {
    return tiles;
}

void Criterion::addAdjacent(Goal *goal) {
    adjacents.emplace_back(goal);
}

void Criterion::setTile(int index, Tile *t) {
    tiles[index] = t;
}

void Criterion::addTile(Tile *t) {
    tiles.emplace_back(t);
}

void Criterion::setPlayer(Player *p) {
    player = p;
}

void Criterion::addNeighbor(Criterion *c) {
    neighbors.emplace_back(c);
}

void Criterion::setAdjacents(vector<Goal*> goals) {
    adjacents = goals;
}