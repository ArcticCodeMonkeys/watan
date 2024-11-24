#include "dice.h"
class Dice : public Subject {
    public:
        virtual int rollDice() = 0;
};

class LoadedDice : public Dice {
    int fixedVal;
    public:
        
       int rollDice() override {
            return fixedVal;
        }
};

class UnloadedDice : public Dice {
    public:
        int rollDice() override {
            return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
        }
};