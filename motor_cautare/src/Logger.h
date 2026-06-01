#ifndef LOGGER_H
#define LOGGER_H

#include "Observer.h"
#include <string>

class Logger : public Observer {
public:
    Logger() = default;
    void update(const std::string& cuvant, int nrRezultate) override;
};

#endif // LOGGER_H
