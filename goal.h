using namespace std;

class Player;

class Goal {
    //need to add an index parameter which begins at -1
    
    int index;
    Goal *adjacents[3];
    public:
        Player *player;
        Goal();
};
