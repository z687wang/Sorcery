#include "Card.h"
#include <string>
#include "Player.h"
#include <utility>
#include "Spell.h"

using namespace std;

Card::Card(string name, int cost, string desc) : name{name}, cost{cost}, desc{desc} {}

Card::Card(string name, int cost, string desc, shared_ptr<Player> p) : name{name}, cost{cost}, desc{desc}, owner{p} {}

string Card::getName() { return name; }

void Card::setName(string name) { this->name = name; }

int Card::getCost() { return cost; }

void Card::setCost(int cost) { this->cost = cost; }

string Card::getDesc() { return desc; }

void Card::setDesc(string desc) { this->desc = desc; }

shared_ptr<Player> Card::getOwner() { return owner.lock(); }

void Card::setOwner(shared_ptr<Player> owner) { this->owner = owner; }

card_template_t Card::getCardTemplate() {
    return CARD_TEMPLATE_EMPTY;
}
