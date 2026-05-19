#include "Index.h"
#include "Document.h"
#include <filesystem>
#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

void Index::indexeazaDirector(const std::string& caleDir) {
    try {
        for (const auto& entry : fs::recursive_directory_iterator(caleDir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                Document doc;
                std::string caleCurenta = entry.path().string();
                
                if (doc.citesteFisier(caleCurenta)) {
                    std::vector<std::string> cuvinte = doc.getNumeCuvinte();
                    
                    for (const std::string& cuvant : cuvinte) {
                        auto& listaFisiere = indexInversat[cuvant];
                        
                        if (std::find(listaFisiere.begin(), listaFisiere.end(), caleCurenta) == listaFisiere.end()) {
                            listaFisiere.push_back(caleCurenta);
                        }
                    }
                } else {
                    std::cerr << "Eroare la citirea fisierului: " << caleCurenta << std::endl;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Eroare de sistem de fisiere: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Eroare generala: " << e.what() << std::endl;
    }
}

std::vector<std::string> Index::cauta(const std::string& cuvant) const {
    auto it = indexInversat.find(cuvant);
    if (it != indexInversat.end()) {
        return it->second;
    }
    return std::vector<std::string>(); 
}
