#include "Logger.h"
#include <fstream>

void Logger::update(const std::string& cuvant, int nrRezultate) {
    std::ofstream file("log.txt", std::ios::app);
    if (file.is_open()) {
        file << "Cuvant cautat: " << cuvant << " | Rezultate: " << nrRezultate << "\n";
        file.close();
    }
}
