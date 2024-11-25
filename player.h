#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "goal.h"
#include "criterion.h"
#include "dice.h"
#include "observer.h"
using namespace std;

class Player : public Observer {
    vector<Criterion*> criteria;
    vector<Goal*> goals;
    map<string, int> resources;
    char name;
    LoadedDice LDice;
    UnloadedDice Dice; //these should be able to be combined into one i just dont know how.
    public:
        bool completeCriterion(int index);
        bool improveCriterion(int index);
        bool achieveGoal(int index);
        void trade();
        void moveGoose(int index);
        void addResources(string resource, int count);
        std::ostream &operator<<(std::ostream &out);
        void printCriteria();
        void notify();
        
};