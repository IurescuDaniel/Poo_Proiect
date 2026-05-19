#ifndef INDEX_H
#define INDEX_H

#include <map>
#include <vector>
#include <string>
#include "Document.h"

class Index {
private:
    std::map<std::string, std::vector<Document>> indexDate;
    std::string curataCuvant(const std::string& cuvant);

public:
    void adaugaDocument(const Document& doc);
    std::vector<Document> cauta(const std::string& cuvant);
};

#endif