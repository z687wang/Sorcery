#ifndef Board_h
#define Board_h

#include <vector>
#include <iostream>
#include <memory>
#include "Minion.h"
#include "SorceryDex.h"

/**************************************
Board.h

This is a header file for Board class which controls
the apperance of all minions on the board (what is
currently on board etc.)
 - A vector of every minion on the board
 - methods to get cards onto the board and off
   the board

**************************************/

class Board {
    std::vector<std::shared_ptr<Minion>> theBoard;
public:
    ~Board();

    void push(std::shared_ptr<Minion> c);
    std::shared_ptr<Minion> pop();
    int size();
    bool empty();
    void prettyPrint();
    void render();
    std::shared_ptr<Minion> at(int i);
    std::shared_ptr<Minion> last();
    void remove(int i);
    void remove(std::shared_ptr<Minion> c);
    void insert(int i, std::shared_ptr<Minion> c);
    void activate();
    void swap(int i, int j);
};

#endif /* Board_h */
