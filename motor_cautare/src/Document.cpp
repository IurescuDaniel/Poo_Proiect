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

// Funcții ajutătoare inline extrem de rapide pentru lucrul cu setul ASCII (evită localizarea standard)
inline bool is_alnum_ascii(unsigned char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           (c >= '0' && c <= '9');
}

inline char to_lower_ascii(unsigned char c) {
    if (c >= 'A' && c <= 'Z') {
        return static_cast<char>(c + 32);
    }
    return static_cast<char>(c);
}

std::vector<std::string> Document::getNumeCuvinte() const {
    std::vector<std::string> cuvinte;
    cuvinte.reserve(continut.size() / 7);
    
    std::string cuvantCurent = "";
    cuvantCurent.reserve(32);
    
    for (char c : continut) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (is_alnum_ascii(uc)) {
            cuvantCurent += to_lower_ascii(uc);
        } else {
            if (!cuvantCurent.empty()) {
                if (cuvantCurent.length() >= 2) {
                    // Optimizare: dacă lungimea cuvântului este > 7, el nu poate fi în setul STOP_WORDS
                    if (cuvantCurent.length() > 7 || STOP_WORDS.find(cuvantCurent) == STOP_WORDS.end()) {
                        cuvinte.push_back(cuvantCurent);
                    }
                }
                cuvantCurent.clear(); // clear() păstrează capacitatea alocată a string-ului, evitând realocări
            }
        }
    }
    
    if (!cuvantCurent.empty()) {
        if (cuvantCurent.length() >= 2) {
            if (cuvantCurent.length() > 7 || STOP_WORDS.find(cuvantCurent) == STOP_WORDS.end()) {
                cuvinte.push_back(cuvantCurent);
            }
        }
    }
    
    return cuvinte;
}
