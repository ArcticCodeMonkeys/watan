#include "goal.h"
#include "player.h"

Goal::Goal(): player{nullptr}, index{-1}, adjacents{nullptr} {
    for (int i = 0; i < 3; i++) {
        adjacents[i] = nullptr;
    }
}
