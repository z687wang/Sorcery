#ifndef Player_h
#define Player_h

#include <string>
#include <vector>
#include "Deck.h"
#include "Board.h"
#include "TriggerType.h"
#include "Ritual.h"


/************************************************
Player.h

This header contains everything relate to the actual player, including
 - Player basic data (name, life, magic...)
 - Trigger specify to the player (to make APNAP order easier)
 - Cards (hand, on board, in deck) belongs to the player

************************************************/

class Player : public std::enable_shared_from_this <Player> {
    std::string name;
    int magic;
    int life;
    int damage;
    bool testMode;
    std::shared_ptr<Board> theBoard;
    std::shared_ptr<Board> graveyard;
    std::shared_ptr<Deck> theDeck;
    std::shared_ptr<Deck> hand;
    std::shared_ptr<Ritual> ritual;
    std::vector<std::shared_ptr<Trigger>> triggers;


public:
    // Constructor and destructor
    Player(std::string name, bool testMode, int magic = 3, int life = 20);
    ~Player();

    // Getter and setter
    std::string getName();
    int getMagic();
    void setMagic(int m);
    int getLife();
    void setLife(int l);
    std::shared_ptr<Board> getTheBoard();
    void setTheBoard(std::shared_ptr<Board> d);
    std::shared_ptr<Board> getGraveyard();
    void setGraveyard(std::shared_ptr<Board> d);
    std::shared_ptr<Deck> getTheDeck();
    void setTheDeck(std::shared_ptr<Deck> d);
    std::shared_ptr<Deck> getHand();
    void setHand(std::shared_ptr<Deck> d);
    void setDamage(int i);
    int getDamage();
    std::shared_ptr<Ritual> getRitual();
    void setRitual(std::shared_ptr<Game> g, std::shared_ptr<Ritual> ritual);

    // Action
    void draw(int time);
    void takeDamage(std::shared_ptr<Game> g, int i);

    // promiseMagic: to check if player has enough
    //               magic to play certain card
    // Note: this doesn't change player's magic
    //       it is just a check
    void promiseMagic(int i);

    // spendMagic: actually spend the amount of magic
    void spendMagic(int i);

    // method relate to triggers player has
    void addTrigger(std::shared_ptr<Trigger> tr);
    void removeTrigger(std::shared_ptr<Trigger> tr);
    void notifyTrigger(TriggerType t, std::shared_ptr<Game> g);
};


#endif /* Player_h */
