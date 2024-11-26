#include <iostream>
#include <vector>
#include <map>

#ifndef PLAYER_H
#define PLAYER_H
#include "observer.h"
using namespace std;

class Criterion;
class Goal;
class LoadedDice;
class UnloadedDice;

class Player : public Observer {
    vector<Criterion*> criteria;
    vector<Goal*> goals;
    map<string, int> resources;
    char name;
    int victoryPoints;
    bool useLoadedDice = false;
    LoadedDice LDice;
    UnloadedDice Dice; //these should be able to be combined into one i just dont know how.
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
        void printCriteria();
        void notify();
        void setName(char name);
        char getName();
        map<string, int> getResources();
        void setResources(map<string, int> resources);
        vector<Criterion*> getCriteria();
        void setCriteria(vector<Criterion*> criteria);
        void setGoals(vector<Goal*> goals);
        vector<Goal*> getGoals();
        bool getUseLoadedDice();
        void setUseLoadedDice(bool useLoadedDice);
        LoadedDice getLDice();   
        friend std::ostream& operator<<(std::ostream &out, const Player &player);
};


#endif