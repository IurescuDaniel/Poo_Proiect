#include "Document.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

bool Document::citesteFisier(const std::string& cale) {
    caleFisier = cale;
    std::ifstream fisier(cale);
    
    if (!fisier.is_open()) {
        return false;
    }
    
    std::stringstream buffer;
    buffer << fisier.rdbuf();
    continut = buffer.str();
    
    fisier.close();
    return true;
}

std::vector<std::string> Document::getNumeCuvinte() const {
    std::vector<std::string> cuvinte;
    std::string cuvantCurent = "";
    
    for (char c : continut) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            // Transformăm în litere mici pentru o indexare case-insensitive (opțional, dar util)
            cuvantCurent += std::tolower(static_cast<unsigned char>(c));
        } else {
            if (!cuvantCurent.empty()) {
                cuvinte.push_back(cuvantCurent);
                cuvantCurent = "";
            }
        }
    }
    
    if (!cuvantCurent.empty()) {
        cuvinte.push_back(cuvantCurent);
    }
    
    return cuvinte;
}
