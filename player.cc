#include "player.h"
#include "goal.h"
using namespace std;
Player::Player(vector<Criterion*> criteria, vector<Goal*> goals, map<string, int> resources, char name): criteria{criteria}, goals{goals}, resources{resources}, name{name}  {}
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
    
}
Player::~Player() {}
bool Player::completeCriterion(int index) {
    if(criteria[index]->type == Criterion::Type::EMPTY && criteria[index]->player == nullptr && criteria[index]->adjCriteria[0]->player == nullptr && criteria[index]->adjCriteria[1]->player == nullptr && criteria[index]->adjCriteria[2]->player == nullptr) {
        if(resources["LAB"] > 0 && resources["LECTURE"] > 0 && resources["CAFFEINE"] > 0 && resources["TUTORIAL"] > 0) {
            resources["LAB"] -= 1;
            resources["LECTURE"] -= 1;
            resources["CAFFEINE"] -=1;
            resources["TUTORIAL"] -= 1;
            criteria[index]->type = Criterion::Type::ASSIGNMENT;
            return true;
        }
        return false;
    }
}
bool Player::improveCriterion(int index) {
    if(criteria[index]->player != this) {
        return false;
    }
    if(criteria[index]->type == Criterion::Type::ASSIGNMENT) {
        if(resources["LECTURE"] > 1 && resources["STUDY"] > 2) {
            resources["LECTURE"] -= 2;
            resources["STUDY"] -= 3;
            criteria[index]->type = Criterion::Type::MIDTERM;
            return true;
        }
        return false;
    } else if(criteria[index]->type == Criterion::Type::MIDTERM) {
        if(resources["LAB"] > 1 && resources["LECTURE"] > 1 && resources["CAFFEINE"] > 2 && resources["TUTORIAL"] > 0 && resources["STUDY"] > 1) {
            resources["LAB"] -= 2;
            resources["LECTURE"] -= 2;
            resources["CAFFEINE"] -= 3;
            resources["TUTORIAL"] -= 1;
            resources["STUDY"] -= 2;
            criteria[index]->type = Criterion::Type::EXAM;
            return true;
        }
        return false;
    }
    return false;
}
bool Player::achieveGoal(int index) {
    if(goals[index]->player == nullptr && (criteria[index]->adjGoals[0]->player == this || criteria[index]->adjGoals[1]->player == this || criteria[index]->adjCriteria[2]->player == this) && resources["STUDY"] > 0 && resources["TUTORIAL"] > 0) {
        resources["STUDY"] -= 1;
        resources["TUTORIAL"] -= 1;
        goals[index]->player = this;
        return true;
    }
}
void Player::trade(Player p, string ask, string give) {
    if(this.resources[give] == 0)  {
        cout << this.name << ", you do not have any " << give << "." endl;
        return;
    }
    if(p.resources[ask] == 0) {
        cout << p.name << " does not have any " << ask << " to give." << endl;
        return;
    }
    cout << this.name << " offers " << p.name << " one " << give << " for one " << ask << ". Does " << p.name << " accept this offer?" << endl;
    char confirmation;
    confirmation << cin;
    if(confirmation == "Y") {
        this.resources[give] -= 1;
        p.resources[give] += 1;
        this.resources[ask] += 1;
        p.resources[ask] -= 1;
        return;
    }
    cout << p.name << " declined the offer." << endl;
}