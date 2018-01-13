#include "Ritual.h"
#include "Card.h"
#include "Game.h"
#include "InvalidMoveException.h"
#include <iostream>
#include <memory>
#include "ritualcardtemplate.h"

using namespace std;

Ritual::Ritual(string name, int cost, string desc, int charge, shared_ptr<Trigger> trigger) : Card{name, cost, desc}, charge{charge}, trigger{trigger} {
}

Ritual::Ritual(string name, int cost, string desc, shared_ptr<Player> p, int charge, shared_ptr<Trigger> trigger) : Card{name, cost, desc, p}, charge{charge}, trigger{trigger} {
    trigger = nullptr;
}

Ritual::Ritual(const Ritual &ritual) : Card{ritual}, charge{ritual.charge}, trigger{new Trigger{*ritual.trigger}} {}

Ritual::~Ritual() {
}

int Ritual::getCharge() { return charge; }
void Ritual::setCharge(int charge) { this->charge = charge; }
shared_ptr<Trigger> Ritual::getTrigger() { return this->trigger; }
void Ritual::setTrigger(shared_ptr<Trigger> trigger) { this->trigger = trigger; }

void Ritual::prettyPrint() {
    cout << "Ritual: " << name << ", cost: " << cost << ", charge: " << charge << endl << "Description: " << desc << endl;
}

shared_ptr<Card> Ritual::clone() const {
    return shared_ptr<Card>(new Ritual{*this});
}

CardType Ritual::getType() {
    return CardType::Ritual;
}

card_template_t Ritual::getCardTemplate() {
    return display_ritual(getName(), getCost(), getTrigger()->getCost(), getDesc(), getCharge());
}

CardTemplate *Ritual::getGraphicsCardTemplate(int x, int y, QWidget *parent) {
    return new RitualCardTemplate(x, y, QString::fromStdString(getName()), QString::fromStdString(getDesc()), getCost(), getTrigger()->getCost(), getCharge(), parent);
}

void Ritual::play(shared_ptr<Game> g) {
    g->getCurrentPlayer()->promiseMagic(getCost());

    g->getCurrentPlayer()->setRitual(g, dynamic_pointer_cast<Ritual>(shared_from_this()));
    setOwner(g->getCurrentPlayer());

    g->getCurrentPlayer()->spendMagic(getCost());

    trigger->setOwner(g->getCurrentPlayer());
    trigger->setRitual(dynamic_pointer_cast<Ritual>(shared_from_this()));
}

void Ritual::play(shared_ptr<Game> g, int i, int j) {
    throw InvalidMoveException{"Invalid number of arguments."};
}

void Ritual::die(shared_ptr<Game> g) {
    if (getOwner()) getOwner()->setRitual(g, nullptr);
}
