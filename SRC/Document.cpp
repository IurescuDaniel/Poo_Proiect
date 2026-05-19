#include "Document.h"
#include <fstream>
#include <sstream>

using namespace std; 

Document::Document() {
    caleFisier = "";
    continut = "";
}

Document::Document(const string& cale) {
    caleFisier = cale;
    continut = "";
    incarcaContinut();
}

bool Document::incarcaContinut() {
    ifstream fisier(caleFisier);
    if (!fisier.is_open()) {
        return false;
    }

    stringstream buffer;
    buffer << fisier.rdbuf();
    continut = buffer.str();
    
    fisier.close();
    return true;
}

string Document::getCaleFisier() const {
    return caleFisier;
}

string Document::getContinut() const {
    return continut;
}