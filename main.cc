#include "board.h"
#include "player.h"
const int NUM_PLAYERS = 4;

int main(int argc, char* argv[]) {
    //Stage 1: Load States
    Board game;
    Player students[NUM_PLAYERS];
    string turnOrder[] = {"Blue", "Red", "Orange", "Yellow"};
    int currentTurn = 0;
    for(int i = 0; i < argc/2; i++) {
        if(argv[i*2] == "-load") {
            //load state from file
        }
        if(argv[i*2] == "-seed") {
            //set rng seed (idk what this is tbh, it might affect dice too)
        }
        if(argv[i*2] == "-board") {
            //load board from file (sets players to default)
        }
    }
    //Stage 2: Setup
    for(int i = 0; i < NUM_PLAYERS; i++) {
        cout << "Student " << turnOrder[i] << ", where do you want to complete an Assignment?" << endl;
        int index;
        cin >> index;
        students[i].completeCriterion(index);
    }
    for(int i = NUM_PLAYERS - 1; i >= 0; i--) {
        cout << "Student " << turnOrder[i] << ", where do you want to complete an Assignment?" << endl;
        int index;
        cin >> index;
        students[i].completeCriterion(index);
    }
    
    //Stage 3: The Game
    bool gameLoop = true;
    while(gameLoop) {

    }
}