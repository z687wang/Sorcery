#include "Player.h"
#include "InvalidMoveException.h"
#include "TriggerType.h"
#include <algorithm>

using namespace std;

Player::Player(string name, bool testMode, int magic, int life) : name{name}, magic{magic}, life{life}, damage{0}, testMode{testMode} {
    ritual = nullptr;
    hand = shared_ptr<Deck>(new Deck());
    graveyard = shared_ptr<Board>(new Board());
    theDeck = shared_ptr<Deck>(new Deck());
    theBoard = shared_ptr<Board>(new Board());
}

Player::~Player() {
    // delete ritual;
    // delete theDeck;
    // delete theBoard;
    // delete hand;
    // delete graveyard;
}

void Player::draw(int time) {
    time = min(5 - hand->size(), time);
    time = min(theDeck->size(), time);
    for(int i = 0; i < time; ++i) {
        hand->push(theDeck->pop());
    }
}

string Player::getName() { return this->name; }

void Player::setMagic(int magic) { this->magic = magic; }

int Player::getMagic() { return this->magic; }

void Player::setLife(int life) { this->life = life; }

int Player::getLife() { return this->life; }

void Player::setTheBoard(shared_ptr<Board> board) {
  //delete this->theBoard;
  this->theBoard = board;
}

shared_ptr<Board> Player::getTheBoard() { return this->theBoard; }

void Player::setGraveyard(shared_ptr<Board> graveyard) {
  //delete this->graveyard;
  this->graveyard = graveyard;
}

shared_ptr<Board> Player::getGraveyard() { return this->graveyard; }

void Player::setHand(shared_ptr<Deck> hand) {
  //delete this->hand;
  this->hand = hand;
}

shared_ptr<Deck> Player::getHand() { return this->hand; }

void Player::setTheDeck(shared_ptr<Deck> theDeck) {
  //delete this->theDeck;
  this->theDeck = theDeck;
}

shared_ptr<Deck> Player::getTheDeck() { return this->theDeck; }

void Player::setRitual(shared_ptr<Game> g, shared_ptr<Ritual> ritual) {
    if (this->ritual) {
        g->removeTrigger(this->ritual->getTrigger());
        //delete this->ritual;
    }

    this->ritual = ritual;
}

shared_ptr<Ritual> Player::getRitual() { return this->ritual; }

void Player::takeDamage(shared_ptr<Game> g, int i) {
    damage += i;
    //if (damage > life) g->end();
    if (damage >= life) g->EndGame(shared_from_this());
}


void Player::setDamage(int damage) { this->damage = damage; }
int Player::getDamage() { return this->damage; }

void Player::spendMagic(int i) {
    if (magic >= i) {
        magic -= i;
    } else if (testMode) {
        magic = 0;
    } else {
        throw InvalidMoveException{"Not enough magic."};
    }
}

void Player::promiseMagic(int i) {
    if (magic < i) {
        if (testMode) return;
        throw InvalidMoveException{"Not enough magic."};
    }
}

void Player::addTrigger(shared_ptr<Trigger> tr) {
    triggers.emplace_back(tr);
}

void Player::removeTrigger(shared_ptr<Trigger> tr) {
    if (find(triggers.begin(), triggers.end(), tr) != triggers.end()){
        triggers.erase(std::remove(triggers.begin(), triggers.end(), tr), triggers.end());
    }
}

void Player::notifyTrigger(TriggerType t, shared_ptr<Game> g) {
    for (auto it = triggers.begin(); it != triggers.end(); ++it) {
        if ((*it)->getType() == t) {
            (*it)->notify(g);
        }
    }
}
