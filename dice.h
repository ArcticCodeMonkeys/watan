#ifndef DICE_H
#define DICE_H
#include "subject.h"
using namespace std;
class Dice : public Subject {
    public:
        virtual int rollDice() = 0;
};

class LoadedDice : public Dice {
    int fixedVal;
    public:
       int rollDice() override;
};

class UnloadedDice : public Dice {
    public:
        int rollDice() override;
};
#endif
