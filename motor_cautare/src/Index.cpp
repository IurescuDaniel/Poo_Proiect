#include "Index.h"
#include "Document.h"
#include <filesystem>
#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

void Index::indexeazaDirector(const std::string& caleDir) {
    // NOU: Verifică dacă directorul există înainte de iterare
    if (!fs::exists(caleDir) || !fs::is_directory(caleDir)) {
        throw std::invalid_argument("Eroare: Directorul " + caleDir + " nu exista sau nu este valid!");
    }

    try {
        int indexateCurent = 0; // NOU: contor pentru afisare progres
        
        for (const auto& entry : fs::recursive_directory_iterator(caleDir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                Document doc;
                std::string caleCurenta = entry.path().string();
                
                if (doc.citesteFisier(caleCurenta)) {
                    std::vector<std::string> cuvinte = doc.getNumeCuvinte();
                    
                    // MODIFICAT: Adăugăm cuvintele în indexul inversat si numaram aparitiile
                    for (const std::string& cuvant : cuvinte) {
                        // NOU: Ignoră cuvintele sub 2 caractere pentru a optimiza memoria
                        if (cuvant.length() < 2) continue;
                        
                        indexInversat[cuvant][caleCurenta]++;
                    }
                    totalDocumenteIndexate++;
                    indexateCurent++;
                    
                    // NOU: Afișare progres indexare
                    if (indexateCurent % 100 == 0) {
                        std::cout << "Progres: " << indexateCurent << " fisiere indexate..." << std::endl;
                    }
                } else {
                    // NOU: gestiune eroare non-critica fara a iesi din aplicatie (log warn)
                    std::cerr << "Avertisment: Fisierul " << caleCurenta << " nu a putut fi deschis, sarim peste." << std::endl;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Eroare de sistem de fisiere la indexare: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Eroare generala la indexare: " << e.what() << std::endl;
    }
}

// MODIFICAT: Acum returneaza un map (cale fisier -> numar aparitii)
std::map<std::string, int> Index::cauta(const std::string& cuvant) const {
    // NOU: Gestioneaza exceptia cand indexul este complet gol
    if (indexInversat.empty()) {
        std::cerr << "Avertisment: Indexul este gol. Nu exista documente procesate." << std::endl;
        return {};
    }

    auto it = indexInversat.find(cuvant);
    if (it != indexInversat.end()) {
        return it->second;
    }
    return {}; 
}
