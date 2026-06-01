#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>
#include <map>

#include "Observer.h"

// MODIFICAT: Pentru a stoca numarul de aparitii folosim o structura pereche
// Cheia interna va fi calea fisierului, valoarea numarul de aparitii
class Index {
private:
    std::map<std::string, std::map<std::string, int>> indexInversat;
    int totalDocumenteIndexate = 0; // NOU: Tine evidenta numarului total de documente
    std::vector<Observer*> observers; // NOU: Lista de observatori

public:
    Index() = default;
    
    // Iterează recursiv prin director și indexează toate fișierele .txt
    void indexeazaDirector(const std::string& caleDir);
    
    // Caută un cuvânt și returnează map-ul de fișiere și numărul lor de apariții
    // MODIFICAT: Returnează un map cu cheia fișierul și valoarea numărul de apariții
    std::map<std::string, int> cauta(const std::string& cuvant) const;

    // NOU: Metode pentru pattern-ul Observer
    void attach(Observer* obs);
    void notify(const std::string& cuvant, int nrRezultate) const;

    // NOU: Getter pentru statistici
    int getTotalDocumente() const { return totalDocumenteIndexate; }
    size_t getDimensiuneIndex() const { return indexInversat.size(); }
};

#endif // INDEX_H
