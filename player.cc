#include "player.h"
#include "goal.h"
#include "criterion.h"
#include "tile.h"
#include "dice.h"

map<char, string> nameArr = {{'B', "Blue"}, {'R', "Red"}, {'O', "Orange"}, {'Y', "Yellow"}};

Player::Player(vector<Criterion*> criteria, vector<Goal*> goals, map<string, int> resources, char name): criteria{criteria}, goals{goals}, resources{resources}, name{name}, victoryPoints{0}, dice{Dice::createFairDice()} {
    for(auto it = criteria.begin(); it != criteria.end(); ++it) {
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
bool Player::completeCriterion(Criterion *purchase, bool free) {
    
    //check there is no criterion here already
    if(purchase->getPlayer() != nullptr) {
        cout << "Invalid Placement, already purchased" << endl;
        return false;
    }
    //check for any adjacent houses (therefore invalid placement)
    for(size_t i = 0; i < purchase->getNeighbors().size(); i++) {
        if(purchase->getNeighbors()[i]->getPlayer() != nullptr) {
            cout << "Invalid Placement, " << nameArr[purchase->getNeighbors()[i]->getPlayer()->getName()] << " has already purchased the Criterion at " << purchase->getNeighbors()[i]->getIndex() << endl;
            return false;
        }
    }
    //check for at least one adjacent goal.

    bool adjGoal = false;
    for(size_t i = 0; i < purchase->getAdjacents().size(); i++) {
        if(purchase->getAdjacents()[i]->getPlayer() == this) {
            adjGoal = true;
            break;
        }
    }
    if(!adjGoal && !free) {
        cout << "Invalid Placement, No Adjacent Goal" << endl;
        return false;
    }
    if((resources["LAB"] > 0 && resources["LECTURE"] > 0 && resources["CAFFEINE"] > 0 && resources["TUTORIAL"] > 0) || free) {
        if(!free) {
            resources["LAB"] -= 1;
            resources["LECTURE"] -= 1;
            resources["CAFFEINE"] -=1;
            resources["TUTORIAL"] -= 1;
        }
        purchase->setType('A');
        purchase->setPlayer(this);
        criteria.emplace_back((purchase));
        victoryPoints++;
        return true;
    }
    //not enough resources
    cout << "Invalid Placement, not enough resources" << endl;
    return false;
}
bool Player::improveCriterion(Criterion *upgrade, bool free) {
    if(upgrade->getPlayer() != this) {
        return false;
    }
    if(upgrade->getType() == 'A') {
        if(free || (resources["LECTURE"] > 1 && resources["STUDY"] > 2)) {
            resources["LECTURE"] -= 2;
            resources["STUDY"] -= 3;
            upgrade->setType('M');
            victoryPoints++;
            return true;
        }
        return false;
    } else if(upgrade->getType() == 'M') {
        if(free || (resources["LAB"] > 1 && resources["LECTURE"] > 1 && resources["CAFFEINE"] > 2 && resources["TUTORIAL"] > 0 && resources["STUDY"] > 1)) {
            resources["LAB"] -= 2;
            resources["LECTURE"] -= 2;
            resources["CAFFEINE"] -= 3;
            resources["TUTORIAL"] -= 1;
            resources["STUDY"] -= 2;
            upgrade->setType('E');
            victoryPoints++;
            return true;
        }
        return false;
    }
    return false;
}
bool Player::achieveGoal(Goal* purchase, bool free) {

    if(purchase->getPlayer() != nullptr) {
        cout << "Invalid Placement, already purchased";
        return false;
    }
    //check for at least one adjacent road.
    if(free) {
        purchase->setPlayer(this);
        goals.emplace_back(purchase);
        return true;
    }
    bool adjGoal = false;
    for(size_t i = 0; i < purchase->getAdjacents().size(); i++) {
        if(purchase->getAdjacents()[i]->getPlayer() == this) {
            adjGoal = true;
            break;
        }
    }
    if(!adjGoal) {
        cout << "Invalid Placement, you have no adjacent roads here" << endl;
        return false;
    }
    //confirm enough resources and not occupied
    if(purchase->getPlayer() == nullptr && resources["STUDY"] > 0 && resources["TUTORIAL"] > 0) {
        resources["STUDY"] -= 1;
        resources["TUTORIAL"] -= 1;
        purchase->setPlayer(this);
        goals.emplace_back(purchase);
        return true;
    }
    cout << "Not enough resources" << endl;
    return false;
}
void Player::trade(Player *p, string ask, string give) {
    if(resources[give] == 0)  {
        cout << nameArr[name] << ", you do not have any " << give << "." << endl;
        return;
    }
    if(p->getResources()[ask] == 0) {
        cout << nameArr[p->getName()] << " does not have any " << ask << " to give." << endl;
        return;
    }
    cout << nameArr[name] << " offers " << nameArr[p->getName()] << " one " << give << " for one " << ask << ". Does " << nameArr[p->getName()] << " accept this offer? (y/n)" << endl;
    char confirmation;
    cout << "> ";
    cin >> confirmation;
    if(confirmation == 'y' || confirmation == 'Y') {
        takeResources(give, 1);
        p->addResources(give, 1);
        addResources(ask, 1);
        p->takeResources(ask, 1);
        return;
    }
    cout << nameArr[p->getName()] << " declined the offer." << endl;
}

void Player::tradeBank(string give, string take) {
    if(resources[give] < 4) {
        cout << nameArr[name] << ", you do not have enough " << give << " to trade." << endl;
        return;
    }
    takeResources(give, 4);
    addResources(take, 1);
}


void Player::addResources(string resource, int count) {
    resources[resource] += count;
}

void Player::takeResources(string resource, int count) {
    resources[resource] -= count;
}

std::ostream &operator<<(std::ostream &out, Player &player) {
    out << nameArr[player.getName()] << " has " << player.getvictoryPoints() << " victory points, "
        << player.getResources().at("CAFFEINE") << " caffeines, "
        << player.getResources().at("LAB") << " labs, "
        << player.getResources().at("LECTURE") << " lectures, "
        << player.getResources().at("STUDY") << " studies, and "
        << player.getResources().at("TUTORIAL") << " tutorials.\n";
    return out;
}

void Player::printCriteria() {
    cout << nameArr[getName()]<< " has completed: " << endl;
    for(size_t i = 0; i < getCriteria().size(); i++) {
        cout << getCriteria()[i]->getIndex() << " " << getCriteria()[i]->getType() << endl;
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

void Player::setDice(int value) {
    if(value == -1) {
        dice = Dice::createFairDice();
    } else {
        dice = Dice::createLoadedDice(value);
    }
}
int Player::rollDice() {
    return dice->rollDice();
}

int Player::getvictoryPoints() {
    return victoryPoints;
}

void Player::addVictoryPoints(int amt) {
    victoryPoints += amt;
}
void Player::setvictoryPoints(int points) {
    victoryPoints = points;
}

Player::~Player() {
    for(size_t i = 0; i < criteria.size(); i++) {
        criteria[i] = nullptr;
    }
    for(size_t i = 0; i < goals.size(); i++) {
        goals[i] = nullptr;
    }
    dice.reset();
}
