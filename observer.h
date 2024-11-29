#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
using namespace std;

class Observer {
  string resource;
 public:
  virtual void notify(string notify) = 0;
  virtual ~Observer() = default;
};

#endif
