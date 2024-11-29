#include <vector>
#include <string>
#include <map>
#include <iostream>
using namespace std;
int main() {
    string resourcesArr[6] = {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL" ,"NETFLIX"};
    map<std::string, int> resources = {
        {"CAFFEINE", 98},
        {"LAB", 2},
        {"LECTURE", 83},
        {"STUDY", 1289381},
        {"TUTORIAL", 0},
        {"NETFLIX", 0}
    };
    int total = 0;
    int indexes[6];
    int count = 0;
    for(auto it : resources) {
        total += it.second;
        indexes[count] = total;
        count++;
    }
    
    if(total >= 10) {
        int stealCount = total/2;
        std::vector<int> randomNumbers;
        for (int i = 0; i < stealCount; ++i) {
            int randomNum = std::rand() % (total + 1); // Generates a number between 0 and j
            randomNumbers.push_back(randomNum);
        }
    for(int i = 0; i < 6; i++) {
        cout << resourcesArr[i] << " " << resources[resourcesArr[i]] << endl;
    }
}
}