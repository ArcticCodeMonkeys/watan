#include "board.h"

class Board {
    Tile *tiles[19];
    Goal *goals[71];
    Criterion *criteria[53];
    public:
    Board() {
        int edgeCount = 0;
        int cornerCount = 0;
        for(int i = 0; i < 6; i++) {
            //we iterate through tile positions to connect tiles to their criteria
            for(int k = 0; k < 19; k++) {
                if(i == 1) {
                    tiles[k]->criteria[i] = i * 2;
                    if(k > 5) {
                        tiles[k]->criteria[i] += 1;
                    }
                    if(k > 7) {
                        tiles[k]->criteria[i] += 1;
                    }
                    if(k > 10) {
                        tiles[k]->criteria[i] += 1;
                    }
                    if(k > 12) {
                        tiles[k]->criteria[i] += 1;
                    }
                    if(k > 15) {
                        tiles[k]->criteria[i] += 1;
                    }
                    if(k > 17) {
                        tiles[k]->criteria[i] += 1;
                    }
                }
            }
        }
    }
    std::ostream &operator<<(std::ostream &out) {
        
    }
};