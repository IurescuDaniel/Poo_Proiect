#include <iostream>
#include <cassert>
#include <fstream>
#include <filesystem>
#include "../src/Index.h"

#include "../src/Logger.h"

namespace fs = std::filesystem;

// Funcție utilitară pentru a crea fișiere de test local
void creazaFisierTest(const std::string& nume, const std::string& continut) {
    std::ofstream f(nume);
    f << continut;
    f.close();
}

// NOU: testCautareSimpla
void testCautareSimpla() {
    std::cout << "Rulare testCautareSimpla()...\n";
    
    std::string testDir = "temp_test_dir";
    fs::create_directory(testDir);
    
    creazaFisierTest(testDir + "/doc1.txt", "Acesta este un test simplu. Test functional.");
    creazaFisierTest(testDir + "/doc2.txt", "Inca un fisier simplu. Fara cuvinte magice.");
    
    Index idx;
    idx.indexeazaDirector(testDir);
    
    auto rez = idx.cauta("simplu");
    assert(rez.size() == 2);
    // Verificam aparitiile (cuvantul "simplu" are 1 aparitie per fisier)
    assert(rez[testDir + "/doc1.txt"] == 1);
    
    auto rez2 = idx.cauta("test");
    assert(rez2.size() == 1);
    // "Test" apare de 2 ori in doc1.txt (test si Test, convertit lower)
    assert(rez2[testDir + "/doc1.txt"] == 2);
    
    std::cout << "testCautareSimpla() trecut cu succes!\n";
    
    // Curatam fisierele
    fs::remove_all(testDir);
}

// NOU: testFisierInexistent
void testFisierInexistent() {
    std::cout << "Rulare testFisierInexistent()...\n";
    Index idx;
    bool exceptieAruncata = false;
    
    try {
        idx.indexeazaDirector("director_care_nu_exista_12345");
    } catch (const std::invalid_argument& e) {
        exceptieAruncata = true;
    }
    
    assert(exceptieAruncata == true);
    std::cout << "testFisierInexistent() trecut cu succes!\n";
}

// NOU: testObserverLogger
void testObserverLogger() {
    std::cout << "Rulare testObserverLogger()...\n";
    
    std::string numeLog = "log.txt";
    fs::remove(numeLog);
    
    std::string testDir = "temp_test_observer_dir";
    fs::create_directory(testDir);
    creazaFisierTest(testDir + "/doc1.txt", "mere pere banane");
    creazaFisierTest(testDir + "/doc2.txt", "mere struguri prune");
    
    Index idx;
    Logger logger;
    idx.attach(&logger);
    
    idx.indexeazaDirector(testDir);
    
    // Căutări
    idx.cauta("mere");       // rezultat: în 2 fișiere
    idx.cauta("portocale");  // rezultat: în 0 fișiere
    
    assert(fs::exists(numeLog));
    
    std::ifstream f(numeLog);
    std::string linie;
    
    std::getline(f, linie);
    assert(linie.find("mere") != std::string::npos);
    assert(linie.find("2") != std::string::npos);
    
    std::getline(f, linie);
    assert(linie.find("portocale") != std::string::npos);
    assert(linie.find("0") != std::string::npos);
    
    f.close();
    
    // Curățare
    fs::remove(numeLog);
    fs::remove_all(testDir);
    
    std::cout << "testObserverLogger() trecut cu succes!\n";
}

int main() {
    std::cout << "=== Start Teste Unitare ===\n";
    
    testCautareSimpla();
    testFisierInexistent();
    testObserverLogger();
    
    std::cout << "=== Toate testele au trecut! ===\n";
    return 0;
}
