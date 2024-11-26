#include "dice.h"
using namespace std;

std::unique_ptr<Dice> Dice::createLoadedDice(int fixedValue) {
    return std::make_unique<LoadedDice>(fixedValue);
}

std::unique_ptr<Dice> Dice::createFairDice() {
    return std::make_unique<FairDice>();
}

int LoadedDice::rollDice() {
    return fixedVal;
}

int FairDice::rollDice() {
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
};