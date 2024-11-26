#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
  string resource;
 public:
  virtual void notify(string resource) = 0;
  virtual ~Observer() = default;
};

#endif
