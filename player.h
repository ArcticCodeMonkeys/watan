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
        bool completeCriterion(Criterion* purchase, bool free);
        bool improveCriterion(Criterion* upgrade, bool free);
        bool achieveGoal(Goal* purchase, bool free);
        void trade(Player *p, string ask, string give);
        void tradeBank(string give, string take);
        void addResources(string resource, int count);
        void takeResources(string resource, int count);
        void printCriteria();
        void setName(char c);
        char getName();
        map<string, int> getResources();
        void setResources(map<string, int> resources);
        vector<Criterion*> getCriteria();
        void setCriteria(vector<Criterion*> criteria);
        vector<Goal*> getGoals();
        void setGoals(vector<Goal*> goals);
        void setDice(int value);
        int rollDice();
        int getvictoryPoints();
        void addVictoryPoints(int amt);
        void setvictoryPoints(int points);
};

std::ostream &operator<<(std::ostream &out, Player &player);


#endif
