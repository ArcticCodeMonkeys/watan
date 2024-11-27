#ifndef TILE_H
#define TILE_H
#include "subject.h"
class Criterion;

class Tile: public Subject {
    //need to add an index parameter which begins at -1
    int rollingValue;
    string resource;
    Criterion * criteria[6];
    Goal * goals[6];
    bool geese;

    public:
        Tile(int rollingValue, string resource, bool geese);
        Tile();
        void notifyObservers();
        void setCriteria(int index, Criterion *c);
        void setGeese(bool geese);
        Criterion* getCriteria(int index);
        bool getGeese();
        int getRollingValue();
        string getResource();
        Goal * getGoal(int index);
        void setGoals(int index, Goal *g);
        string printResource();
};
#endif
