#include <iostream>
#include <string>
#include "Index.h"
#include "Logger.h"

void afiseazaMeniu() {
    std::cout << "\n=== Motor de Cautare Full-Text ===\n";
    std::cout << "1. Seteaza calea directorului si indexeaza\n";
    std::cout << "2. Cauta un cuvant\n";
    std::cout << "3. Iesire\n";
    std::cout << "Alege o optiune (1-3): ";
}

int main() {
    Index motorCautare;
    Logger logger;
    motorCautare.attach(&logger);
    int optiune;
    
    // MODIFICAT: Adaugare loop de meniu interactiv (Optiunile 1-3)
    do {
        afiseazaMeniu();
        if (!(std::cin >> optiune)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(); // curata newline-ul lasat de cin
        
        switch (optiune) {
            case 1: {
                std::string caleDir;
                std::cout << "Introduceti calea directorului pentru indexare: ";
                std::getline(std::cin, caleDir);
                
                std::cout << "Se indexeaza fisierele din " << caleDir << "...\n";
                // NOU: Folosim try-catch pentru a gestiona input gresit fara a iesi din aplicatie
                try {
                    motorCautare.indexeazaDirector(caleDir);
                    std::cout << "Indexare finalizata cu succes!\n";
                    // NOU: Afisare numar total de documente si cuvinte (dimensiunea indexului)
                    std::cout << "Documente indexate in total: " << motorCautare.getTotalDocumente() << "\n";
                    std::cout << "Cuvinte unice in index: " << motorCautare.getDimensiuneIndex() << "\n";
                } catch (const std::exception& e) {
                    std::cerr << e.what() << "\n";
                }
                break;
            }
            case 2: {
                std::string cuvantCautat;
                std::cout << "Introduceti un cuvant pentru cautare: ";
                std::getline(std::cin, cuvantCautat);
                
                if (cuvantCautat.empty()) break;
                
                // Normalizare in lower-case pentru interogare
                std::string cuvantCautatMic = cuvantCautat;
                for (char& c : cuvantCautatMic) {
                    c = std::tolower(static_cast<unsigned char>(c));
                }
                
                // MODIFICAT: Afisare extinsa cu numarul de aparitii in fiecare fisier
                std::map<std::string, int> rezultate = motorCautare.cauta(cuvantCautatMic);
                
                if (rezultate.empty()) {
                    std::cout << "Cuvantul '" << cuvantCautat << "' nu a fost gasit in niciun fisier.\n";
                } else {
                    std::cout << "Cuvantul '" << cuvantCautat << "' a fost gasit in " << rezultate.size() << " fisier(e):\n";
                    for (const auto& [cale, nrAparitii] : rezultate) {
                        std::cout << "  - " << cale << " (Aparitii: " << nrAparitii << ")\n";
                    }
                }
                break;
            }
            case 3:
                std::cout << "Se inchide aplicatia...\n";
                break;
            default:
                std::cout << "Optiune invalida! Va rugam selectati 1, 2 sau 3.\n";
        }
    } while (optiune != 3);
    
    return 0;
}
