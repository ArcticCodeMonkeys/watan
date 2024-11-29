#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>
class Observer;
using namespace std;

class Subject {
  std::vector<Observer*> observers;
  string resource;
 public:
  void attach( Observer* o );
  void detach( Observer* o );
  void notifyObservers();
  std::vector<Observer*> getObservers();
  virtual ~Subject();
};

#endif
