#include <iostream>
#include "Document.h"
#include "Index.h"

using namespace std; 

int main() {
    Index motorCautare;

    cout << "--- Incarcare Documente de Test ---" << endl;
    
    Document d1("doc1.txt");
    Document d2("doc2.txt");

    motorCautare.adaugaDocument(d1);
    motorCautare.adaugaDocument(d2);

    string cuvantCautat;
    while (true) {
        cout << "\nIntroduceti un cuvant de cautat (sau 'iesire'): ";
        cin >> cuvantCautat;

        if (cuvantCautat == "iesire") {
            break;
        }

        auto rezultate = motorCautare.cauta(cuvantCautat);

        if (rezultate.empty()) {
            cout << "Cuvantul nu a fost gasit in niciun document." << endl;
        } else {
            cout << "Cuvantul a fost gasit in urmatoarele documente:" << endl;
            for (const auto& doc : rezultate) {
                cout << "- " << doc.getCaleFisier() << endl;
            }
        }
    }

    return 0;
}