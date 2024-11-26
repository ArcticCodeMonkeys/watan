#ifndef DICE_H
#define DICE_H
#include <memory>

using namespace std;
class Dice {
    public:
        virtual ~Dice() = default;
        virtual int rollDice() = 0;
        static std::unique_ptr<Dice> createLoadedDice(int fixedValue);
        static std::unique_ptr<Dice> createFairDice();
};

class LoadedDice : public Dice {
    int fixedVal;
    public:
    explicit LoadedDice(int value) : fixedVal(value) {}
       int rollDice() override;
};

class FairDice : public Dice {
    public:
        int rollDice() override;
};
#endif
