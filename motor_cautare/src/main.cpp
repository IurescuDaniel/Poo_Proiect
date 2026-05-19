#include <iostream>
#include <string>
#include "Index.h"

int main() {
    std::cout << "=== Motor de Cautare Full-Text ===\n";
    
    std::string caleDir;
    std::cout << "Introduceti calea directorului pentru indexare: ";
    std::getline(std::cin, caleDir);
    
    Index motorCautare;
    std::cout << "Se indexeaza fisierele din " << caleDir << "...\n";
    motorCautare.indexeazaDirector(caleDir);
    std::cout << "Indexare finalizata!\n\n";
    
    std::string cuvantCautat;
    while (true) {
        std::cout << "Introduceti un cuvant pentru cautare (sau 'exit' pentru a iesi): ";
        std::getline(std::cin, cuvantCautat);
        
        if (cuvantCautat == "exit") {
            break;
        }
        
        if (cuvantCautat.empty()) {
            continue;
        }
        
        std::string cuvantCautatMic = cuvantCautat;
        for (char& c : cuvantCautatMic) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        
        std::vector<std::string> rezultate = motorCautare.cauta(cuvantCautatMic);
        
        if (rezultate.empty()) {
            std::cout << "Cuvantul '" << cuvantCautat << "' nu a fost gasit in niciun fisier.\n\n";
        } else {
            std::cout << "Cuvantul '" << cuvantCautat << "' a fost gasit in " << rezultate.size() << " fisier(e):\n";
            for (const std::string& cale : rezultate) {
                std::cout << "  - " << cale << "\n";
            }
            std::cout << "\n";
        }
    }
    
    return 0;
}
