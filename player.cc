#include "player.h"
#include "goal.h"
#include "criterion.h"
#include "tile.h"
#include "dice.h"


Player::Player(vector<Criterion*> criteria, vector<Goal*> goals, map<string, int> resources, char name): criteria{criteria}, goals{goals}, resources{resources}, name{name}, victoryPoints{0}, dice{Dice::createFairDice()} {
    for(auto it = getCriteria().begin(); it != getCriteria().end(); ++it) {
        char type = (*it)->getType();
        victoryPoints += (type == 'E' ? 3 : (type == 'M' ? 2 : (type == 'A' ? 1 : 0)));
    }
}
Player::Player() {
    criteria = vector<Criterion*>();
    goals = vector<Goal*>();
    resources = {
        {"CAFFEINE", 0},
        {"LAB", 0},
        {"LECTURE", 0},
        {"STUDY", 0},
        {"TUTORIAL", 0},
        {"NETFLIX", 0}
    };
    name = '\0';
    victoryPoints = 0;
    dice = Dice::createFairDice();
}
Player::~Player() {}
bool Player::completeCriterion(int index) {
    if(criteria[index]->getType() == '\0' && criteria[index]->getPlayer() == nullptr && criteria[index]->getNeighbors(0)->getPlayer() == nullptr && criteria[index]->getNeighbors(1)->getPlayer() == nullptr && criteria[index]->getNeighbors(2)->getPlayer() == nullptr) {
        if(resources["LAB"] > 0 && resources["LECTURE"] > 0 && resources["CAFFEINE"] > 0 && resources["TUTORIAL"] > 0) {
            resources["LAB"] -= 1;
            resources["LECTURE"] -= 1;
            resources["CAFFEINE"] -=1;
            resources["TUTORIAL"] -= 1;
            criteria[index]->setType('A');
            return true;
        }
        return false;
    }
}
bool Player::improveCriterion(int index) {
    if(criteria[index]->getPlayer() != this) {
        return false;
    }
    if(criteria[index]->getType() == 'A') {
        if(resources["LECTURE"] > 1 && resources["STUDY"] > 2) {
            resources["LECTURE"] -= 2;
            resources["STUDY"] -= 3;
            criteria[index]->setType('M');
            return true;
        }
        return false;
    } else if(criteria[index]->getType() == 'M') {
        if(resources["LAB"] > 1 && resources["LECTURE"] > 1 && resources["CAFFEINE"] > 2 && resources["TUTORIAL"] > 0 && resources["STUDY"] > 1) {
            resources["LAB"] -= 2;
            resources["LECTURE"] -= 2;
            resources["CAFFEINE"] -= 3;
            resources["TUTORIAL"] -= 1;
            resources["STUDY"] -= 2;
            criteria[index]->setType('E');
            return true;
        }
        return false;
    }
    return false;
}
bool Player::achieveGoal(int index) {
    if(goals[index]->getPlayer() == nullptr && (criteria[index]->getAdjacents(0)->getPlayer() == this || criteria[index]->getAdjacents(1)->getPlayer() == this || criteria[index]->getAdjacents(2)->getPlayer() == this) && resources["STUDY"] > 0 && resources["TUTORIAL"] > 0) {
        resources["STUDY"] -= 1;
        resources["TUTORIAL"] -= 1;
        goals[index]->setPlayer(this);
        return true;
    }
}
void Player::trade(Player p, string ask, string give) {
    if(resources[give] == 0)  {
        cout << name << ", you do not have any " << give << "." << endl;
        return;
    }
    if(p.resources[ask] == 0) {
        cout << p.name << " does not have any " << ask << " to give." << endl;
        return;
    }
    cout << name << " offers " << p.name << " one " << give << " for one " << ask << ". Does " << p.name << " accept this offer?" << endl;
    char confirmation;
    cin >> confirmation;
    if(confirmation == 'Y') {
        resources[give] -= 1;
        p.resources[give] += 1;
        resources[ask] += 1;
        p.resources[ask] -= 1;
        return;
    }
    cout << p.name << " declined the offer." << endl;
}

void Player::addResources(string resource, int count) {
    resources[resource] += count;
}

std::ostream &Player::operator<<(std::ostream &out) {
    out << name << " has " << victoryPoints <<  " victory points, " << resources["CAFFEINE"] << " caffeines, " << resources["LABS"] << " labs, " << resources["LECTURES"] << " lectures, " << resources["TUTORIALS"] << " tutorials, and " << resources["STUDIES"] << " studies." << endl;
}

void Player::printCriteria() {
    cout << getName() << " has completed: " << endl;
    for(auto it = getCriteria().begin(); it != getCriteria().end(); ++it) {
        Criterion* criterion = *it;
        cout << criterion->getIndex() << " " << criterion->getType() << endl;
    }
}

void Player::setName(char name) {
    this->name = name;
}


char Player::getName() {
    return name;
}
map<string, int> Player::getResources() {
    return resources;
}

void Player::setResources(map<string, int> resources) {
    this->resources = resources;
}

vector<Criterion*> Player::getCriteria() {
    return criteria;
}

void Player::setCriteria(vector<Criterion*> criteria) {
    this->criteria = criteria;
}

vector<Goal*> Player::getGoals() {
    return goals;
}

void Player::setGoals(vector<Goal*> goals) {
    this->goals = goals;
}