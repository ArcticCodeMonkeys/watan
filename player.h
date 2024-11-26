#include <iostream>
#include <vector>
#include <map>
#include <memory>
#ifndef PLAYER_H
#define PLAYER_H
using namespace std;

class Criterion;
class Goal;
class Dice;

class Player {
    vector<Criterion*> criteria;
    vector<Goal*> goals;
    map<string, int> resources;
    char name;
    int victoryPoints;
    std::unique_ptr<Dice> dice;
    public:
        Player(std::vector<Criterion*> criteria, std::vector<Goal*> goals, map<string, int> resources, char name);
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
        void setName(char c);
        char getName();
        map<string, int> getResources();
        void setResources(map<string, int> resources);
        vector<Criterion*> getCriteria();
        void setCriteria(vector<Criterion*> criteria);
        vector<Goal*> getGoals();
        void setGoals(vector<Goal*> goals);
};
#endif