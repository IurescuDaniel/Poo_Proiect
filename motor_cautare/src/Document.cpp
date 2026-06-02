#include "Document.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <unordered_set>

static const std::unordered_set<std::string> STOP_WORDS = {
    "si", "in", "la", "pe", "cu", "de", "un", "o", "sa", "ca", "nu", "se", "ce", 
    "are", "ale", "din", "sau", "dar", "mai", "fost", "fi", "va", "ai", "al", 
    "ei", "el", "ea", "eu", "tu", "ii", "le", "ne", "tot", "foarte", "este", 
    "erau", "prin", "care", "acest", "aceasta", "pentru", "unei", "unui"
};

bool Document::citesteFisier(const std::string& cale) {
    caleFisier = cale;
    std::ifstream fisier(cale);
    
    if (!fisier.is_open()) {
        return false;
    }
    
    // Citirea eficientă a întregului fișier într-un string
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
        // Păstrăm doar caracterele alfanumerice pentru a forma cuvinte
        if (std::isalnum(static_cast<unsigned char>(c))) {
            cuvantCurent += c;
        } else {
            if (!cuvantCurent.empty()) {
                // MODIFICAT: Normalizare lowercase folosind std::transform
                std::transform(cuvantCurent.begin(), cuvantCurent.end(), cuvantCurent.begin(),
                    [](unsigned char ch){ return std::tolower(ch); });
                // NOU: Filtrare stop-words
                if (STOP_WORDS.find(cuvantCurent) == STOP_WORDS.end()) {
                    cuvinte.push_back(cuvantCurent);
                }
                cuvantCurent = "";
            }
        }
    }
    
    // Adăugăm ultimul cuvânt dacă există
    if (!cuvantCurent.empty()) {
        std::transform(cuvantCurent.begin(), cuvantCurent.end(), cuvantCurent.begin(),
            [](unsigned char ch){ return std::tolower(ch); });
        // NOU: Filtrare stop-words
        if (STOP_WORDS.find(cuvantCurent) == STOP_WORDS.end()) {
            cuvinte.push_back(cuvantCurent);
        }
    }
    
    return cuvinte;
}
