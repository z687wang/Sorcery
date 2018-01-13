#include <iostream>
#include <sstream>
#include <vector>
#include "ascii_graphics.h"
#include "Deck.h"
#include "Card.h"
#include "Minion.h"
#include "Enchantment.h"
#include "Spell.h"
#include "Ritual.h"
#include "SorceryDex.h"
#include "InvalidMoveException.h"
#include <algorithm>
#include <cstdlib>
#include "randomNum.h"
using namespace std;

Deck::~Deck() {
    // for (auto it : theDeck) {
       //  delete it;
    // }
}

void Deck::push(shared_ptr<Card> c) {
    theDeck.emplace_back(c);
}

shared_ptr<Card> Deck::pop() {
    if (size() == 0) throw InvalidMoveException("No minion.");
    shared_ptr<Card> result = theDeck.front();
    theDeck.erase(theDeck.begin());
    return result;
}

void Deck::setDeck(std::istream &in, SorceryDex &d) {
    string name;
    while (true) {
        getline(in, name, '\n');
        if (in.eof()) break;
        try {
            if (name != "") {
              push(d.get(name)->clone());
            }
        } catch (out_of_range e) {
            cout << name << " not found" << endl;
        }

    }
}

void Deck::prettyPrint() {
    for (auto it = theDeck.begin(); it < theDeck.end(); it++) {
        (*it)->prettyPrint();
    }
}

void Deck::render() {
    if (theDeck.size() == 0) return;
    vector<card_template_t> template_array;
    int size = this->size();
    int line = 0;
    while (line * 5 < size) {
        template_array.clear();
        for (int i = line * 5; i < theDeck.size() && i < line * 5 + 5; ++i) {
            template_array.emplace_back(theDeck.at(i)->getCardTemplate());

        }
        for (int i = 0; i < template_array[0].size(); ++i) {
            for (auto it1 = template_array.begin(); it1 != template_array.end(); ++it1) {
                cout << (*it1)[i];
            }
            cout << endl;
        }
        ++line;
    }

}

int Deck::size() {
    return (int)theDeck.size();
}

bool Deck::empty() {
    return theDeck.empty();
}

shared_ptr<Card> Deck::at(int i) {
    if (i > size() - 1 || i < 0) throw InvalidMoveException{"Invalid card index."};
    return theDeck.at(i);
}

shared_ptr<Card> Deck::last() {
    return theDeck.at(theDeck.size() - 1);
}

void Deck::remove(int i) {
    theDeck.erase(theDeck.begin() + i);
}

void Deck::remove(shared_ptr<Card> c) {
    theDeck.erase(std::remove(theDeck.begin(), theDeck.end(), c), theDeck.end());
}

void Deck::insert(int i, shared_ptr<Card> c) {
    theDeck.insert(theDeck.begin() + i, c);
}

void Deck::shuffle(int i) {
    srand(time(0) + i);
    random_shuffle(theDeck.begin(), theDeck.end(), [](int n) { return rand() % n; });
}
