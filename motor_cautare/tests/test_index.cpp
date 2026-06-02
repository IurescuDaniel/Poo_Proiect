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

// NOU: testCautareAvansata
void testCautareAvansata() {
    std::cout << "Rulare testCautareAvansata()...\n";
    
    std::string testDir = "temp_test_advanced_dir";
    fs::create_directory(testDir);
    
    creazaFisierTest(testDir + "/doc1.txt", "mere pere banane cirese");
    creazaFisierTest(testDir + "/doc2.txt", "mere struguri prune cirese");
    creazaFisierTest(testDir + "/doc3.txt", "prune caise cirese");
    
    Index idx;
    idx.indexeazaDirector(testDir);
    
    // Test AND
    {
        auto rez = idx.cautaAvansat("mere AND cirese");
        assert(rez.size() == 2);
        assert(rez[testDir + "/doc1.txt"] == 2); // 1 + 1
        assert(rez[testDir + "/doc2.txt"] == 2); // 1 + 1
        assert(rez.find(testDir + "/doc3.txt") == rez.end());
    }
    
    // Test OR
    {
        auto rez = idx.cautaAvansat("mere OR prune");
        assert(rez.size() == 3);
        assert(rez[testDir + "/doc1.txt"] == 1); // doar 'mere' (1)
        assert(rez[testDir + "/doc2.txt"] == 2); // 'mere' (1) + 'prune' (1)
        assert(rez[testDir + "/doc3.txt"] == 1); // doar 'prune' (1)
    }

    // Curățare
    fs::remove_all(testDir);
    std::cout << "testCautareAvansata() trecut cu succes!\n";
}

// NOU: testStopWords
void testStopWords() {
    std::cout << "Rulare testStopWords()...\n";
    
    std::string testDir = "temp_test_stopwords_dir";
    fs::create_directory(testDir);
    
    creazaFisierTest(testDir + "/doc1.txt", "mere si pere pentru ca cirese");
    
    Index idx;
    idx.indexeazaDirector(testDir);
    
    // "si", "pentru", "ca" sunt stop-words și NU trebuie indexate
    assert(idx.cauta("si").empty());
    assert(idx.cauta("pentru").empty());
    assert(idx.cauta("ca").empty());
    
    // "mere", "pere", "cirese" sunt cuvinte normale și trebuie indexate
    assert(!idx.cauta("mere").empty());
    assert(!idx.cauta("pere").empty());
    assert(!idx.cauta("cirese").empty());
    
    fs::remove_all(testDir);
    std::cout << "testStopWords() trecut cu succes!\n";
}

int main() {
    std::cout << "=== Start Teste Unitare ===\n";
    
    testCautareSimpla();
    testFisierInexistent();
    testObserverLogger();
    testCautareAvansata();
    testStopWords();
    
    std::cout << "=== Toate testele au trecut! ===\n";
    return 0;
}
