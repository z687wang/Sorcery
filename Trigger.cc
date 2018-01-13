#include "Trigger.h"
#include "randomNum.h"
#include "InvalidMoveException.h"

using namespace std;

Trigger::Trigger(TriggerType type, int trigger_id, int cost) : type{type}, trigger_id{trigger_id}, cost{cost} {
    owner = shared_ptr<Player>{nullptr};
    ritual = shared_ptr<Ritual>{nullptr};
}

Trigger::Trigger(const Trigger &trigger) : trigger_id{trigger.trigger_id}, cost{trigger.cost}, type{trigger.type} {
    owner = shared_ptr<Player>{nullptr};
    ritual = shared_ptr<Ritual>{nullptr};
}

int Trigger::getCost() { return cost; }

shared_ptr<Player> Trigger::getOwner() {
    return owner.lock();
}

void Trigger::setCost(int cost) { this->cost = cost; }

TriggerType Trigger::getType() const { return type; }

void Trigger::setRitual(shared_ptr<Ritual> ritual) { this->ritual = ritual; }

void Trigger::setOwner(shared_ptr<Player> owner) { this->owner = owner; }

void Trigger::notify(shared_ptr<Game> g) {
    // if the owner's ritual is not enough, the trigger is simply not triggered
    if (cost != 0) {
        if (ritual.lock()->getCharge() < cost) return;
    }
    
    try {
        switch (trigger_id) {
            case 1:
                if (g->getCurrentPlayer() != owner.lock()) {
                    shared_ptr<Minion> c = g->getCurrentPlayer()->getTheBoard()->last();
                    c->setDamage(c->getDamage() + 1);
                }
                break;
            case 2:
                if (g->getCurrentPlayer() == owner.lock()) {
                    shared_ptr<Board> d = g->getCurrentPlayer()->getTheBoard();
                    for (int i = 0; i < d->size(); ++i) {
                        // add 1 defense
                        d->at(i)->addDefense(1);
                    }
                }
                break;
            case 3:
                if (g->getCurrentPlayer() == owner.lock()) {
                    owner.lock()->setMagic(owner.lock()->getMagic() + 1);
                }
                break;
            case 4:
                if (g->getCurrentPlayer() == owner.lock()) {
                    shared_ptr<Minion> c = g->getCurrentPlayer()->getTheBoard()->last();
                    c->addDefense(1);
                    c->addAttack(1);
                }
                break;
            case 5:
            {
                shared_ptr<Minion> c = g->getCurrentPlayer()->getTheBoard()->last();
                if (c->getDefense() - c->getDamage() <= 0) throw InvalidMoveException{"Target Minion Already Dead."};
                c->setDamage(c->getDefense());
            }
                break;
            case 6:
                if (g->getCurrentPlayer() == owner.lock()) {
                    g->getNonCurrentPlayer()->takeDamage(g,2);
                }else {
                    g->getCurrentPlayer()->takeDamage(g,2);
                }
                break;
            case 7:
                {
                    int size_1 = g->getPlayer1()->getTheBoard()->size();
                    int size_2 = g->getPlayer2()->getTheBoard()->size();

                    if (size_1 <= 0 || size_2 <= 0) throw InvalidMoveException{"No minions to attack each other."};

                    int idx1 = randomGenerate(size_1);
                    int idx2 = randomGenerate(size_2);

                    shared_ptr<Player> p1 = g->getPlayer1();
                    shared_ptr<Player> p2 = g->getPlayer2();

                    int dam1 = p1->getTheBoard()->at(idx1)->getAttack();
                    int dam2 = p2->getTheBoard()->at(idx2)->getAttack();

                    p1->getTheBoard()->at(idx1)->setDamage(p1->getTheBoard()->at(idx1)->getDamage() + dam2);
                    p2->getTheBoard()->at(idx2)->setDamage(p2->getTheBoard()->at(idx2)->getDamage() + dam1);
                }
        }
        
        if (cost != 0) {
            ritual.lock()->setCharge(ritual.lock()->getCharge() - cost);
        }
    } catch (InvalidMoveException e) {
        
    }
    
}
