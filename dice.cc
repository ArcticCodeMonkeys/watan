#include "dice.h"
int LoadedDice::rollDice() {
    return fixedVal;
}

int UnloadedDice::rollDice() {
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
};