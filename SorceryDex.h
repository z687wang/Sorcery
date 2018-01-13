#ifndef SorceryDex_h
#define SorceryDex_h

#include <map>
#include "Card.h"

class SorceryDex {
    std::map<std::string, std::shared_ptr<Card>> database;
public:
    ~SorceryDex();
    void set(std::string, std::shared_ptr<Card>);
    std::shared_ptr<Card> get(std::string);
    friend std::istream &operator>>(std::istream &in, SorceryDex &dex);
};

#endif /* SorceryDex_h */
