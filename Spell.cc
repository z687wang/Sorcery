#include "Spell.h"
#include "Card.h"
#include "InvalidMoveException.h"
#include "SorceryDex.h"
#include "Game.h"
#include "randomNum.h"
#include <iostream>
#include <memory>
#include "spellcardtemplate.h"

using namespace std;

Spell::Spell(int spell_id, string name, int cost, string desc) : spell_id{spell_id}, Card{name, cost, desc} {}

Spell::Spell(int spell_id, string name, int cost, string desc, shared_ptr<Player> p) : spell_id{spell_id}, Card{name, cost, desc, p} {}

void Spell::prettyPrint() {
    cout << "Spell: " << name << ", cost: " << cost << endl << "Description: " << desc << endl;
}

shared_ptr<Card> Spell::clone() const {
    return shared_ptr<Card>(new Spell{*this});
}

CardType Spell::getType() {
    return CardType::Spell;
}

card_template_t Spell::getCardTemplate() {
    return display_spell(getName(), getCost(), getDesc());
}

CardTemplate *Spell::getGraphicsCardTemplate(int x, int y, QWidget *parent) {
    return new SpellCardTemplate(x, y, QString::fromStdString(getName()), QString::fromStdString(getDesc()), getCost(), parent);
}

void Spell::play(shared_ptr<Game> g) {
    shared_ptr<Player> targetPlayer = g->getCurrentPlayer();
    int size;
    int charge;
    int size_1;
    int size_2;
    int n;
    shared_ptr<Minion> m;

    targetPlayer->promiseMagic(getCost());

    switch (spell_id) {
        case 2:
            size = targetPlayer->getTheBoard()->size();
            if (size == 5) throw InvalidMoveException("Invalid ability utility.");
            else {
                shared_ptr<Card> airElemental = g->getSorceryDex()->get("Air Elemental")->clone();
                airElemental->setOwner(targetPlayer);
                airElemental->play(g);
            }
            break;
        case 3:
            size = targetPlayer->getTheBoard()->size();
            if (size == 5) throw InvalidMoveException("Invalid ability utility.");
            n = 0;
            for (int i = size; i < 5; ++i) {
                if (n <=2){
                    g->getSorceryDex()->get("Air Elemental")->clone()->play(g);
                    n++;
                }
            }
            break;
        case 6:
            charge = targetPlayer->getRitual()->getCharge();
            targetPlayer->getRitual()->setCharge(charge + 3);
            break;
        case 8:
            if (targetPlayer->getTheBoard()->size() < 5) {
                m = targetPlayer->getGraveyard()->pop();
                targetPlayer->getTheBoard()->push(m);
                g->notifyTriggers(TriggerType::MinionEnter);
                m->setActivate(true);
            } else {
                throw InvalidMoveException{"Cannot raise dead, board full."};
            }
            break;
        case 9:
            size_1  = targetPlayer->getTheBoard()->size();
            for (int i = 0; i < size_1; ++i) targetPlayer->getTheBoard()->at(i)->takeDamage(g, 2);
            size_2 = g->getNonCurrentPlayer()->getTheBoard()->size();
            for (int n = 0; n < size_2; ++n) g->getNonCurrentPlayer()->getTheBoard()->at(n)->takeDamage(g, 2);
            break;
        case 10:
            size_1 = g->getNonCurrentPlayer()->getTheBoard()->size();
            for (int n = 0; n < size_1; ++n) g->getNonCurrentPlayer()->getTheBoard()->at(n)->takeDamage(g,1);
            break;
        case 11:
        {
            int maxRec = 10;
            
            size_1 = g->getCurrentPlayer()->getTheBoard()->size();
            if (size_1 <= 0) throw InvalidMoveException{"No minion to add defense."};
            for (int n = 0; n < size_1 - 1; ++n) {
                int rec = randomGenerate(maxRec);
                g->getCurrentPlayer()->getTheBoard()->at(n)->addDefense(rec);
                maxRec -= rec;
            }
            g->getCurrentPlayer()->getTheBoard()->at(size_1 - 1)->addDefense(maxRec);
        }
            break;
        default:
            throw InvalidMoveException("Invalid number of target");
            break;
    }

    targetPlayer->spendMagic(getCost());
}

void Spell::play(shared_ptr<Game> g, int i, int j) {
    shared_ptr<Player> player = g->getCurrentPlayer();
    shared_ptr<Player> targetPlayer;
    shared_ptr<Minion> targetBase;
    string name;

    if (i == 1) targetPlayer = g->getPlayer1();
    else if (i == 2) targetPlayer = g->getPlayer2();
    else throw InvalidMoveException("Invalid target player.");


    player->promiseMagic(getCost());

    if (j == 6 && spell_id == 4) {
        if (targetPlayer->getRitual()) {
            targetPlayer->getRitual()->die(g);
            g->getCurrentPlayer()->spendMagic(getCost());
            return;
        } else {
            throw InvalidMoveException{"Invalid spell target."};
        }
    }

    shared_ptr<Minion> target = targetPlayer->getTheBoard()->at(j-1);
    switch (spell_id) {
        case 1:
            target->takeDamage(g, 1);
            break;
        case 4:
            target->die(g);
            break;
        case 5:
            targetBase = target->getBase();
            name = targetBase->getName();
            targetPlayer->getTheDeck()->push(g->getSorceryDex()->get(name)->clone());
            targetPlayer->getTheBoard()->remove(target);
            target->setBase(nullptr);
            //delete target;
            break;
        case 7:
            if (target->getBase() == target) throw InvalidMoveException{"Minion has no enchantment"};
            targetBase = static_pointer_cast<Minion>(target->getBase()->clone());
            targetPlayer->getTheBoard()->remove(j - 1);
            target->setBase(nullptr);
            //delete target;
            targetPlayer->getTheBoard()->insert(j - 1, targetBase);
            targetBase->takeDamage(g, 0);
            break;
        default:
            throw InvalidMoveException {"Invalid number of arguments."};
            break;
    }


    player->spendMagic(getCost());
}

//if (target->getBase() == target) throw InvalidMoveException{"Minion has no enchantment"};
