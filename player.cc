#include "player.h"

class Player {
    vector<Criterion*> criteria;
    vector<Goal*> goals;
    map<string, int> resources;
    LoadedDice LDice;
    UnloadedDice Dice; //these should be able to be combined into one i just dont know how.
    public:
    bool completeCriterion(int index) {
        if(criteria[index]->type == Criterion::TYPE::EMPTY && criteria[index]->player == nullptr && (criteria[index]->adjCriteria[0]->player == this || criteria[index]->adjCriteria[1]->player == this || criteria[index]->adjCriteria[2]->player == this)) {
            if(resources["LAB"] > 0 && resources["LECTURE"] > 0 && resources["CAFFEINE"] > 0 && resources["TUTORIAL"] > 0) {
                resources["LAB"] -= 1;
                resources["LECTURE"] -= 1;
                resources["CAFFEINE"] -=1;
                resources["TUTORIAL"] -= 1;
                criteria[index]->type = Criterion::TYPE::ASSIGNMENT;
                return true;
            }
            return false;
        }
    }
    bool improveCriterion(int index) {
        if(criteria[index]->type == Criterion::TYPE::ASSIGNMENT) {
            if(resources["LECTURE"] > 1 && resources["STUDY"] > 2) {
                resources["LECTURE"] -= 2;
                resources["STUDY"] -= 3;
                criteria[index]->type = Criterion::TYPE::MIDTERM;
                return true;
            }
            return false;
        } else if(criteria[index]->type == Criterion::TYPE::MIDTERM) {
            if(resources["LAB"] > 1 && resources["LECTURE"] > 1 && resources["CAFFEINE"] > 2 && resources["TUTORIAL"] > 0 && resources["STUDY"] > 1) {
                resources["LAB"] -= 2;
                resources["LECTURE"] -= 2;
                resources["CAFFEINE"] -= 3;
                resources["TUTORIAL"] -= 1;
                resources["STUDY"] -= 2;
                return true;
            }
            return false;
        }
        return false;
    }
    bool achieveGoal(int index) {
        if(goals[index]->player == nullptr && resources["STUDY"] > 0 && resources["TUTORIAL"] > 0) {
            resources["STUDY"] -= 1;
            resources["TUTORIAL"] -= 1;
            goals[index]->player = this;
            return true;
        }
    }
};