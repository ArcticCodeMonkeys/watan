#include "subject.h"
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
