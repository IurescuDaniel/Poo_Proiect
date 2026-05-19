#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>
#include <map>

class Index {
private:
    std::map<std::string, std::vector<std::string>> indexInversat;

public:
    Index() = default;
    
    void indexeazaDirector(const std::string& caleDir);
    
    std::vector<std::string> cauta(const std::string& cuvant) const;
};

#endif // INDEX_H
