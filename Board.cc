#include <iostream>
#include <sstream>
#include <vector>
#include "ascii_graphics.h"
#include "Card.h"
#include "Minion.h"
#include "Enchantment.h"
#include "Spell.h"
#include "Ritual.h"
#include "SorceryDex.h"
#include "Board.h"
#include "InvalidMoveException.h"
#include <algorithm>

using namespace std;

void Board::push(shared_ptr<Minion> c) {
    theBoard.emplace_back(c);
}

Board::~Board() {
    // for (auto it : theBoard) {
    //     //delete it;
    // }
}

shared_ptr<Minion> Board::pop() {
    if (size() <= 0) throw InvalidMoveException{"No Minion."};
    shared_ptr<Minion> result = theBoard.back();
    theBoard.pop_back();
    return result;
}



void Board::prettyPrint() {
    for (auto it = theBoard.begin(); it < theBoard.end(); it++) {
        (*it)->prettyPrint();
    }
}

void Board::render() {
    if (theBoard.size() == 0) return;
    vector<card_template_t> template_array;
    int size = this->size();
    int line = 0;
    while (line * 5 < size) {
        template_array.clear();
        for (int i = line * 5; i < theBoard.size() && i < line * 5 + 5; ++i) {
            template_array.emplace_back(theBoard.at(i)->getCardTemplate());
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

int Board::size() {
    return (int)theBoard.size();
}

bool Board::empty() {
    return theBoard.empty();
}

shared_ptr<Minion> Board::at(int i) {
    if (i > size() - 1 || i < 0) throw InvalidMoveException{"Invalid minion index."};
    return theBoard.at(i);
}

shared_ptr<Minion> Board::last() {
    return theBoard.at(theBoard.size() - 1);
}

void Board::remove(int i) {
    theBoard.erase(theBoard.begin() + i);
}

void Board::remove(shared_ptr<Minion> c) {
    theBoard.erase(std::remove(theBoard.begin(), theBoard.end(), c), theBoard.end());
}

void Board::insert(int i, shared_ptr<Minion> c) {
    theBoard.insert(theBoard.begin() + i, c);
}

void Board::activate() {
    for (auto it = theBoard.begin(); it != theBoard.end(); ++it) {
        (*it)->setActivate(true);
    }
}

void Board::swap(int i, int j) {
    iter_swap(theBoard.begin() + i, theBoard.begin() + j);
}
