#include "Minion.h"
#include "Player.h"
#include "Card.h"
#include "InvalidMoveException.h"
#include "Enchantment.h"
#include <iostream>
#include <memory>
#include "minioncardtemplate.h"

using namespace std;

Minion::Minion(string name, int cost, string desc, int attack, int defense)
: Card{name, cost, desc}, attack{attack}, defense{defense}, damage{0}, activate{true} {}

Minion::Minion(string name, int cost, string desc, shared_ptr<Player> p, int attack, int defense)
: Card{name, cost, desc, p}, attack{attack}, defense{defense}, damage{0}, activate{true} {}

int Minion::getAttack() {return attack;}
int Minion::getDefense() {return defense;}
int Minion::getDamage() {return damage;}
void Minion::setDamage(int damage) { this->damage = damage; }
void Minion::setAttack(int attack) { this->attack = attack; }
void Minion::setDefense(int defense) { this->defense = defense; }
void Minion::addAttack(int attack) { this->attack += attack; }
void Minion::addDefense(int defense) { this->defense += defense; }
void Minion::setActivate(bool b) { activate = b; }
bool Minion::getActivate() { return activate; }
shared_ptr<Trigger> Minion::getTrigger() {return nullptr;}
void Minion::setTrigger(shared_ptr<Trigger> trigger) {}
void Minion::useSpell() {}
void Minion::setSpell(shared_ptr<Spell> spell) {}
shared_ptr<Spell> Minion::getSpell() { return nullptr; }
int Minion::getSpellCost() { return 0; }
shared_ptr<Minion> Minion::getBase() { return dynamic_pointer_cast<Minion>(shared_from_this()); }
shared_ptr<Minion> Minion::getNextBase() { return dynamic_pointer_cast<Minion>(shared_from_this()); }
void Minion::setBase(shared_ptr<Minion> m) {}
shared_ptr<Card> Minion::clone() const {
    return shared_ptr<Card>(new Minion{*this});
    //return new Minion{*this};
}

card_template_t Minion::getCardTemplate() {
    return display_minion_no_ability(getName(), getCost(), getAttack(), getDefense() - getDamage());
}

CardTemplate *Minion::getGraphicsCardTemplate(int x, int y, QWidget *parent) {
    return new MinionCardTemplate(x, y, QString::fromStdString(getName()), getCost(), getAttack(), getDefense() - getDamage(), parent);
}

vector<card_template_t> Minion::getTemplateArray() {
    vector<card_template_t> array;
    return array;
}

CardType Minion::getType() {
    return CardType::Minion;
}

void Minion::prettyPrint() {
    cout << "Minion: " << name << ", cost: " << cost << ", attack: " << attack << ", defense: " << defense << endl << "Description: " << desc << endl;
    
}

void Minion::takeDamage(shared_ptr<Game> g, int i) {
    damage += i;
    if (damage >= defense) {
        die(g);
    }
}

void Minion::die(shared_ptr<Game> g) {
    shared_ptr<Player> p = getOwner();
    if (p) {
        p->getTheBoard()->remove(dynamic_pointer_cast<Minion>(shared_from_this()));
        p->getGraveyard()->push(dynamic_pointer_cast<Minion>(shared_from_this()));
        damage = 0;
    }
}

void Minion::applyEnchantment(shared_ptr<Enchantment> e) {
    e->setBase(dynamic_pointer_cast<Minion>(shared_from_this()));
}

void Minion::useAbility(shared_ptr<Game> g) {
    throw InvalidMoveException{"Minion has no ability."};
}

void Minion::useAbility(shared_ptr<Game> g, int i, int j) {
    throw InvalidMoveException{"Minion has no ability."};
}

void Minion::attackOpponent(shared_ptr<Game> g) {
    if (activate == false) throw InvalidMoveException{"This minion cannot take actions this turn."};
    g->getNonCurrentPlayer()->takeDamage(g, getAttack());
    setActivate(false);
}

void Minion::attackOpponentMinion(shared_ptr<Game> g, int i) {
    if (activate == false) throw InvalidMoveException{"This minion cannot take actions this turn."};
    int damageMake = getAttack();
    int damageTake = g->getNonCurrentPlayer()->getTheBoard()->at(i)->getAttack();
    g->getNonCurrentPlayer()->getTheBoard()->at(i)->takeDamage(g, damageMake);
    takeDamage(g, damageTake);
    setActivate(false);
}

void Minion::inspect() {
    card_template_t t = getCardTemplate();
    for (auto it = t.begin(); it != t.end(); ++it) {
        cout << (*it) << endl;
    }
}

void Minion::play(shared_ptr<Game> g) {
    shared_ptr<Board> board = g->getCurrentPlayer()->getTheBoard();
    if (board->size() >= 5) {
        throw InvalidMoveException{"Board full."};
    } else {
        g->getCurrentPlayer()->promiseMagic(getCost());
        board->push(dynamic_pointer_cast<Minion>(shared_from_this()));
        setOwner(g->getCurrentPlayer());
        g->getCurrentPlayer()->spendMagic(getCost());
        
        
        g->notifyTriggers(TriggerType::MinionEnter);
    }
}

void Minion::play(shared_ptr<Game> g, int i, int j) {
    throw InvalidMoveException{"Invalid number of arguments."};
}
