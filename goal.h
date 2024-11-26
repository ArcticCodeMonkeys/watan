using namespace std;

class Player; //forward declaration of player
class Goal {
    //need to add an index parameter which begins at -1
    Player *player;
    int index;
    Goal *adjacents[3];
    public:
        Goal();
};
