#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Document {
private:
    std::string caleFisier;
    std::string continut;

public:
    Document() = default;
    
    bool citesteFisier(const std::string& cale);
    
    std::vector<std::string> getNumeCuvinte() const;
    
    std::string getCaleFisier() const { return caleFisier; }
};

#endif // DOCUMENT_H
