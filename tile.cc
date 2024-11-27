#include "tile.h"
#include "criterion.h"
#include "goal.h"
using namespace std;

Tile::Tile(int rollingValue, string resource, bool geese): rollingValue{rollingValue}, resource{resource}, geese{geese} {}

Tile::Tile() {
    rollingValue = 0;
    resource = "";
    geese = false;
}

void Tile::notifyObservers() {
    for (auto &ob : criteria) {
        ob->notify(resource);
    }
}

void Tile::setCriteria(int index, Criterion *c) {
    attach(c);
    criteria[index] = c;
}

bool Tile::getGeese() {
    return geese;
}

void Tile::setGeese(bool geese) {
    this->geese = geese;
}

int Tile::getRollingValue() {
    return rollingValue;
}

string Tile::getResource() {
    return resource;
}

string Tile::printResource() {
    int remaining_spaces = 12 - resource.length();
    string output_string = "       " + resource;
    for (int i = 0; i < remaining_spaces; i++) {
        output_string += " ";
    }
    return output_string;
}

std::unique_ptr<Dice> Tile::getDice() {
    return std::move(dice);
}

Criterion *Tile::getCriteria(int index) {
    return criteria[index];
}

void Tile::setDice(std::unique_ptr<Dice> dice) {
    this->dice = std::move(dice);
}

Goal* Tile::getGoal(int index) {
    return goals[index];
}

void Tile::setGoals(int index, Goal *g) {
    goals[index] = g;
}