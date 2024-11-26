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
