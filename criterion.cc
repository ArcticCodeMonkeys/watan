#include "criterion.h"

Criterion::Criterion(int index) index(index) type(Type::Assignment) {
    for (int i = 0; i < 3; i++) {
        adjacents[i] = nullptr;
        tile[i] = nullptr;
    }
    
}
Criterion::printType() {
    if (type == Type::Assignment) {
        cout << "Assignment";
    } else if (type == Type::Midterm) {
        cout << "Midterm";
    } else {
        cout << "Exam";
    }
}
