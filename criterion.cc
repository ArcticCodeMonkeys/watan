#include "criterion.h"
using namespace std;
Criterion::Criterion(int index): index(index), type(Type::ASSIGNMENT) {
    for (int i = 0; i < 3; i++) {
        adjacents[i] = nullptr;
        tile[i] = nullptr;
    }
}
Criterion::printType() {
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
    } else {
        return 'E';
    }
}
