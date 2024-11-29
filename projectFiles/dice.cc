#include "dice.h"
using namespace std;

std::unique_ptr<Dice> Dice::createLoadedDice(int fixedValue) {
    return std::unique_ptr<LoadedDice>(new LoadedDice(fixedValue));
}

std::unique_ptr<Dice> Dice::createFairDice() {
    return std::unique_ptr<FairDice>(new FairDice());
}

int LoadedDice::rollDice() {
    return fixedVal;
}

int FairDice::rollDice() {
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
};