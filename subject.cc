#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach( Observer* o ) {
    observers.emplace_back(o);
}

void Subject::detach( Observer* o ) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if(*it == o) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyObservers() {
    for(auto &o: observers) {
        o->notify(resource);
    }
}
std::vector<Observer*> Subject::getObservers() {
    return observers;
}

Subject::~Subject() {
    for(auto &o: observers) {
        delete o;
    }
}
