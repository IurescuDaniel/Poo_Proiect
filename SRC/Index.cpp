#include "Index.h"
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std; 

string Index::curataCuvant(const string& cuvant) {
    string rezultat = "";
    for (char c : cuvant) {
        if (isalnum(c)) { 
            rezultat += tolower(c); 
        }
    }
    return rezultat;
}

void Index::adaugaDocument(const Document& doc) {
    stringstream ss(doc.getContinut());
    string cuvant;

    while (ss >> cuvant) {
        string cuvantCurat = curataCuvant(cuvant);
        if (cuvantCurat.empty()) {
            continue;
        }

        auto& listaDoc = indexDate[cuvantCurat];
        bool exista = false;
        
        for (const auto& d : listaDoc) {
            if (d.getCaleFisier() == doc.getCaleFisier()) {
                exista = true;
                break;
            }
        }
        
        if (!exista) {
            listaDoc.push_back(doc);
        }
    }
}

vector<Document> Index::cauta(const string& cuvant) {
    string cuvantCautat = curataCuvant(cuvant);
    if (indexDate.find(cuvantCautat) != indexDate.end()) {
        return indexDate[cuvantCautat];
    }
    return vector<Document>(); 
}