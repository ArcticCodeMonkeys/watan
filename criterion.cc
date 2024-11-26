#include "criterion.h"
#include "goal.h"
#include "tile.h"
#include "player.h"

Criterion::Criterion(int index): index(index), type(Type::ASSIGNMENT) {
    for (int i = 0; i < 3; i++) {
        adjacents[i] = nullptr;
        tile[i] = nullptr;
    }
}

Criterion::Criterion(): index(-1), type(Type::EMPTY) {
    for (int i = 0; i < 3; i++) {
        adjacents[i] = nullptr;
        tile[i] = nullptr;
    }
}

Criterion* Criterion::getNeighbors(int index) {
    return neighbors[index];
}

Goal* Criterion::getAdjacents(int index) {
    return adjacents[index];
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

void Criterion::notify(string resource) {
    if (player != nullptr) {
        if (type == Criterion::Type::ASSIGNMENT) {
            player->addResources(resource, 1);
        } else if (type == Criterion::Type::MIDTERM) {
            player->addResources(resource, 2);
        } else if (type == Criterion::Type::EXAM) {
            player->addResources(resource, 3);
        }
    }
}
int Criterion::getIndex() {
    return index;
}
