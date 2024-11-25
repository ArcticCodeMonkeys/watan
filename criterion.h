#include "goal.h"
class Criterion {
    //need to add an index parameter which begins at -1
    enum class Type {Assignment, Midterm, Exam};
    Type type;
    int index;
    Goal *adjacents[3];
    Tile *tile [3];
    public:
        Criterion (index);
        void printType();
};