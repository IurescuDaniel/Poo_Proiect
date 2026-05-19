#include <iostream>
#include <cassert>
#include <fstream>
#include <filesystem>
#include "../src/Index.h"

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

int main() {
    std::cout << "=== Start Teste Unitare ===\n";
    
    testCautareSimpla();
    testFisierInexistent();
    
    std::cout << "=== Toate testele au trecut! ===\n";
    return 0;
}
