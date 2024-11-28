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
bool Player::completeCriterion(Criterion *purchase, bool free) {
    
    //check there is no criterion here already
    if(purchase->getType() != '\0') {
        cout << "Invalid Placement, already purchased" << endl;
        return false;
    }
    //check for any adjacent houses (therefore invalid placement)
    for(int i = 0; i < purchase->getNeighbors().size(); i++) {
        if(purchase->getNeighbors()[i]->getPlayer() != nullptr) {
            cout << "Invalid Placement, " << purchase->getNeighbors()[i]->getPlayer()->getName() << " has already purchased the Criterion at " << purchase->getNeighbors()[i]->getIndex() << endl;
            return false;
        }
    }
    //check for at least one adjacent goal.

    bool adjGoal = false;
    for(int i = 0; i < purchase->getAdjacents().size(); i++) {
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
bool Player::improveCriterion(int index) {
    if(criteria[index]->getPlayer() != this) {
        return false;
    }
    if(criteria[index]->getType() == 'A') {
        if(resources["LECTURE"] > 1 && resources["STUDY"] > 2) {
            resources["LECTURE"] -= 2;
            resources["STUDY"] -= 3;
            criteria[index]->setType('M');
            victoryPoints++;
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
            victoryPoints++;
            return true;
        }
        return false;
    }
    return false;
}
bool Player::achieveGoal(Goal* purchase) {
    //check for at least one adjacent road.
    bool adjGoal = false;
    for(int i = 0; i < purchase->getAdjacents().size(); i++) {
        if(purchase->getAdjacents()[i]->getPlayer() == this) {
            adjGoal = true;
            break;
        }
    }
    if(!adjGoal) {
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
    return false;
}
void Player::trade(Player *p, string ask, string give) {
    if(resources[give] == 0)  {
        cout << name << ", you do not have any " << give << "." << endl;
        return;
    }
    if(p->getResources()[ask] == 0) {
        cout << p->getName() << " does not have any " << ask << " to give." << endl;
        return;
    }
    cout << name << " offers " << p->getName() << " one " << give << " for one " << ask << ". Does " << p->getName() << " accept this offer?" << endl;
    char confirmation;
    cin >> confirmation;
    if(confirmation == 'Y') {
        takeResources(give, 1);
        p->addResources(give, 1);
        addResources(ask, 1);
        p->takeResources(ask, 1);
        return;
    }
    cout << p->getName() << " declined the offer." << endl;
}

void Player::addResources(string resource, int count) {
    resources[resource] += count;
}

void Player::takeResources(string resource, int count) {
    resources[resource] -= count;
}

std::ostream &operator<<(std::ostream &out, Player &player) {
    out << player.getName() << " has " << player.getvictoryPoints() <<  " victory points, " << player.getResources()["CAFFEINE"] << " caffeines, " << player.getResources()["LABS"] << " labs, " << player.getResources()["LECTURES"] << " lectures, " << player.getResources()["TUTORIALS"] << " tutorials, and " << player.getResources()["STUDIES"] << " studies." << endl;
    return out;
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

void Player::setvictoryPoints(int points) {
    victoryPoints = points;
}
