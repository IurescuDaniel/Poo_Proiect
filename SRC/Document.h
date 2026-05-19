#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

class Document {
private:
    std::string caleFisier;
    std::string continut;

public:
    Document();
    Document(const std::string& cale);

    bool incarcaContinut();

    std::string getCaleFisier() const;
    std::string getContinut() const;
};

#endif