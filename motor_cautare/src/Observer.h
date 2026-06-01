#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& cuvant, int nrRezultate) = 0;
};

#endif // OBSERVER_H
