#ifndef Deck_h
#define Deck_h

#include <vector>
#include <iostream>
#include <memory>
#include "Card.h"
#include "SorceryDex.h"


class Deck {
    std::vector<std::shared_ptr<Card>> theDeck;
public:
    ~Deck();

    void push(std::shared_ptr<Card> c);
    std::shared_ptr<Card> pop();
    int size();
    bool empty();
    void prettyPrint();
    void render();
    std::shared_ptr<Card> at(int i);
    std::shared_ptr<Card> last();
    void remove(int i);
    void remove(std::shared_ptr<Card> c);
    void insert(int i, std::shared_ptr<Card> c);
    void shuffle(int i);

    void setDeck(std::istream &in, SorceryDex &d);
};



#endif /* Deck_h */
