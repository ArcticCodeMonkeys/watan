#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "observer.h"


class Goal;
class Criterion;
class Tile;
class Dice;

class Player : public Observer {
    vector<Criterion*> criteria;
    vector<Goal*> goals;
    map<string, int> resources;
    char name;
    bool useLoadedDice = false;
    LoadedDice LDice;
    UnloadedDice Dice; //these should be able to be combined into one i just dont know how.
    public:
        Player(vector<Criterion*> criteria, vector<Goal*> goals, map<string, int> resources, char name);
        Player();
        ~Player();
        bool completeCriterion(int index);
        bool improveCriterion(int index);
        bool achieveGoal(int index);
        void trade(Player p, string ask, string give);
        int moveGoose(int index);
        void addResources(string resource, int count);
        std::ostream &operator<<(std::ostream &out);
        void printCriteria();
        void notify();
        
};