#include <iostream>
#include "Enchantment.h"
#include "InvalidMoveException.h"
#include "Card.h"
#include "minioncardtemplate.h"
#include "minionactivatedcardtemplate.h"
#include "miniontriggeredcardtemplate.h"
#include "enchantmentadcardtemplate.h"
#include "enchantmentcardtemplate.h"

using namespace std;

Enchantment::Enchantment(shared_ptr<Minion> minion, string name, int cost, string desc, int attack, int defense, shared_ptr<Spell>  spell, shared_ptr<Trigger> trigger, int enchantmentId, bool isBaseMinion)
: base{minion}, Minion{name, cost, desc, attack, defense}, spell{spell}, trigger{trigger}, enchantmentId{enchantmentId}, isBaseMinion{isBaseMinion} {
}

Enchantment::Enchantment(shared_ptr<Minion> minion, string name, int cost, string desc, shared_ptr<Player> p, int attack, int defense, shared_ptr<Spell>
                          spell, shared_ptr<Trigger> trigger, int enchantmentId, bool isBaseMinion)
    : base{minion}, Minion{name, cost, desc, attack, defense}, spell{spell},
     trigger{trigger}, enchantmentId{enchantmentId}, isBaseMinion{isBaseMinion} {
}

Enchantment::Enchantment(const Enchantment &enchantment) : Minion{enchantment}, enchantmentId{enchantment.enchantmentId}, isBaseMinion{enchantment.isBaseMinion}  {
    if (enchantment.base != nullptr) base = shared_ptr<Minion>(new Minion{*enchantment.base});
    else base = nullptr;
    if (enchantment.spell != nullptr) spell = shared_ptr<Spell>(new Spell{*enchantment.spell});
    else spell = nullptr;
    if (enchantment.trigger != nullptr) trigger = shared_ptr<Trigger>(new Trigger{*enchantment.trigger});
    else trigger = nullptr;
}

Enchantment::~Enchantment() {
    // delete base;
    // delete trigger;
    // delete spell;
}

void Enchantment::setActivate(bool b) {
    Minion::setActivate(b);
    base->setActivate(b);
}

bool Enchantment::getActivate() {
    return Minion::getActivate();
}

CardType Enchantment::getType() {
    return CardType::Enchantment;
}

string Enchantment::getName() {
    if (base) {
        return base->getName();
    } else {
        return Card::getName();
    }
}

int Enchantment::getCost() {
    if (base) {
        return base->getCost();
    } else {
        return Card::getCost();
    }
}

string Enchantment::getDesc() {
    if (trigger || spell) {
        return Card::getDesc();
    } else {
        if (base) {
            return base->getDesc();
        } else {
            return Card::getDesc();
        }
    }
}

int Enchantment::getDamage() {
    if (base) {
        return this->damage + base->getDamage();
    } else {
        return this->damage;
    }
}

int Enchantment::getAttack() {
    if (base) {
        return this->attack + base->getAttack();
    } else {
        return this->attack;
    }
}

int Enchantment::getDefense() {
    if (base) {
        return this->defense + base->getDefense();
    } else {
        return this->defense;
    }
}

void Enchantment::setAttack(int attack) { base->setAttack(attack); }
void Enchantment::setDefense(int defense) { base->setDefense(defense); }
void Enchantment::addAttack(int attack) { base->addAttack(attack); }
void Enchantment::addDefense(int defense) { base->addDefense(defense); }

shared_ptr<Trigger> Enchantment::getTrigger() {
    if (trigger != nullptr) return trigger;
    else {
        if (base != nullptr) return base->getTrigger();
        else return nullptr;
    }
}

void Enchantment::setTrigger(shared_ptr<Trigger> trigger) {
  //delete this->trigger;
  this->trigger = trigger;
}

shared_ptr<Spell> Enchantment::getSpell() {
    if (spell != nullptr) return spell;
    else {
        if (base != nullptr) return base->getSpell();
        else return nullptr;
    }
}
void Enchantment::setSpell(shared_ptr<Spell> spell) {
  //delete this->spell;
  this->spell = spell;
}

int Enchantment::getSpellCost() {
    if (enchantmentId == 1) {
        if (spell != nullptr) return spell->getCost() + 2;
        else {
            if (base != nullptr) return base->getSpellCost() + 2;
            else return 2;
        }
    }
    if (spell != nullptr) return spell->getCost();
    else {
        if (base != nullptr) return base->getSpellCost();
        else return 0;
    }
}

void Enchantment::setDamage(int damage) {
    if (base != nullptr) {
        base->setDamage(damage);
    }
}

shared_ptr<Minion> Enchantment::getBase() {
    if (base != nullptr) {
        if (isBaseMinion) return base;
        else return base->getBase();
    } else {
        return nullptr;
    }
}

shared_ptr<Minion> Enchantment::getNextBase() {
    if (base != nullptr) {
        return base;
    } else {
        return shared_ptr<Minion>(new Minion{*this});
    }

}
void Enchantment::setBase(shared_ptr<Minion> m) {
    //delete this->base;
    base = m;
}

void Enchantment::prettyPrint() {
    cout << "Enchantment: " << name << ", cost: " << cost << ", attack: " << attack << ", defense: " << defense << endl << "Description: " << desc << endl;
}

shared_ptr<Card> Enchantment::clone() const {
    return shared_ptr<Card>(new Enchantment{*this});
}

vector<card_template_t> Enchantment::getTemplateArray() {
    if (isBaseMinion) {
        vector<card_template_t> array;
        return array;
    } else {
        vector<card_template_t> array = base->getTemplateArray();
        if (Minion::getAttack() == 0 && Minion::getDefense() == 0) {
            array.emplace_back(display_enchantment(Card::getName(), Card::getCost(), Card::getDesc()));
        } else {
            array.emplace_back(display_enchantment_attack_defence(Card::getName(), Card::getCost(), Card::getDesc(), "+" + to_string(Minion::getAttack()), "+" + to_string(Minion::getDefense())));
        }
        return array;
    }
}

card_template_t Enchantment::getCardTemplate() {
    if (getBase()) {
        if (getTrigger() != nullptr) {
            return display_minion_triggered_ability(getName(), getCost(), getAttack(), getDefense() - getDamage(), getDesc());
        } else if (getSpell() != nullptr) {
            return display_minion_activated_ability(getName(), getCost(), getAttack(), getDefense() - getDamage(), getSpellCost(), getSpell()->getDesc());
        } else {
            return display_minion_no_ability(getName(), getCost(), getAttack(), getDefense() - getDamage());
        }
    } else {
        if (Minion::getAttack() == 0 && Minion::getDefense() == 0) {
            return display_enchantment(getName(), getCost(), getDesc());
        } else {
            return display_enchantment_attack_defence(getName(), getCost(), getDesc(), "+" + to_string(getAttack()), "+" + to_string(getDefense() - getDamage()));
        }
    }
}

CardTemplate *Enchantment::getGraphicsCardTemplate(int x, int y, QWidget *parent) {
    if (getBase()) {
        if (getTrigger() != nullptr) {
            return new MinionTriggeredCardTemplate(x, y, QString::fromStdString(getName()), getCost(), getAttack(), getDefense() - getDamage(), QString::fromStdString(getDesc()), parent);
        } else if (getSpell() != nullptr) {
            return new MinionActivatedCardTemplate(x, y, QString::fromStdString(getName()), getCost(), getAttack(), getDefense() - getDamage(), getSpellCost(), QString::fromStdString(getSpell()->getDesc()), parent);
        } else {
            return new MinionCardTemplate(x, y, QString::fromStdString(getName()), getCost(), getAttack(), getDefense() - getDamage(), parent);
        }
    } else {
        if (Minion::getAttack() == 0 && Minion::getDefense() == 0) {
            return new EnchantmentCardTemplate(x, y, QString::fromStdString(getName()), getCost(), QString::fromStdString(getDesc()), parent);
        } else {
            return new EnchantmentADCardTemplate(x, y, QString::fromStdString(getName()), QString::fromStdString(getDesc()), getCost(), getAttack(), getDefense() - getDamage(), parent);
        }
    }
}

void Enchantment::play(shared_ptr<Game> g) {
    if (!isBaseMinion) {
        throw InvalidMoveException{"Invalid number of arguments."};
    }

    shared_ptr<Board> board = g->getCurrentPlayer()->getTheBoard();
    if (board->size() >= 5) {
        throw InvalidMoveException{"Board full."};
    } else {
        g->getCurrentPlayer()->promiseMagic(Card::getCost());

        board->push(dynamic_pointer_cast<Minion>(shared_from_this()));
        setOwner(g->getCurrentPlayer());

        g->getCurrentPlayer()->spendMagic(Card::getCost());
        if (trigger) {
            trigger->setOwner(g->getCurrentPlayer());
        }

        g->notifyTriggers(TriggerType::MinionEnter);

        if (trigger) {
            g->addTrigger(trigger);
        }

        // the order there doesn't work
    }
}

void Enchantment::play(shared_ptr<Game> g, int i, int j) {
    if (isBaseMinion) {
        throw InvalidMoveException{"Invalid number of arguments."};
    }

    shared_ptr<Player> p;
    if (i == 1) {
        p = g->getPlayer1();
    } else if (i == 2) {
        p = g->getPlayer2();
    } else {
        throw InvalidMoveException{"Invalid player number."};
    }

    if (j < 1 || j > p->getTheBoard()->size()) {
        throw InvalidMoveException{"Invalid minion index."};
    } else {
        p->promiseMagic(Card::getCost());

        // if there is a new trigger, remove the old one and add the new one
        if (getTrigger()) {
            g->removeTrigger(p->getTheBoard()->at(j - 1)->getTrigger());
            g->addTrigger(getTrigger());
        }

        p->getTheBoard()->at(j - 1)->applyEnchantment(dynamic_pointer_cast<Enchantment>(shared_from_this()));
        p->getTheBoard()->remove(j - 1);
        p->getTheBoard()->insert(j - 1, dynamic_pointer_cast<Minion>(shared_from_this()));

        p->spendMagic(Card::getCost());

        setOwner(p);
    }
}

void Enchantment::takeDamage(shared_ptr<Game> g, int i) {
    if (base != nullptr) {
        base->setDamage(base->getDamage() + i);
    } else {
        throw InvalidMoveException{"This message will never show"};
    }
    if (getDamage() >= getDefense()) die(g);
}

void Enchantment::die(shared_ptr<Game> g) {
    shared_ptr<Player> p = getOwner();
    if (p) {
        if (trigger != nullptr && trigger -> getType() == TriggerType::MinionDead) {
            trigger -> notify(g);
        }
        if (trigger) g->removeTrigger(trigger);
        p->getTheBoard()->remove(dynamic_pointer_cast<Minion>(shared_from_this()));
        if (isBaseMinion) {
            p->getGraveyard()->push(dynamic_pointer_cast<Minion>(shared_from_this()));
        } else {
            base->die(g);
        }
        this->base->setDamage(0);
    }
}

void Enchantment::useAbility(shared_ptr<Game> g) {
    if (enchantmentId == 2) throw InvalidMoveException{"Silenced minion cannot use abilities."};
    if (spell) {
        if (activate == false) throw InvalidMoveException{"This minion cannot take actions this turn."};

        g->getCurrentPlayer()->promiseMagic(getSpellCost());
        spell->play(g);
        if (enchantmentId == 1) g->getCurrentPlayer()->spendMagic(2);

        setActivate(false);
    } else {
        g->getCurrentPlayer()->promiseMagic(getSpellCost());
        base->useAbility(g);
        if (enchantmentId == 1) g->getCurrentPlayer()->spendMagic(2);
    }
}

void Enchantment::useAbility(shared_ptr<Game> g, int i, int j) {
    if (enchantmentId == 2) throw InvalidMoveException{"Silenced minion cannot use abilities."};

    if (spell) {
        if (activate == false) throw InvalidMoveException{"This minion cannot take actions this turn."};

        g->getCurrentPlayer()->promiseMagic(getSpellCost());
        spell->play(g, i, j);
        if (enchantmentId == 1) g->getCurrentPlayer()->spendMagic(2);

        setActivate(false);
    } else {
        g->getCurrentPlayer()->promiseMagic(getSpellCost());
        base->useAbility(g, i, j);
        if (enchantmentId == 1) g->getCurrentPlayer()->spendMagic(2);
    }
}

void Enchantment::inspect() {
    card_template_t all = getCardTemplate();
    for (auto it = all.begin(); it != all.end(); ++it) {
        cout << (*it) << endl;
    }

    vector<card_template_t> card_array = getTemplateArray();
    vector<card_template_t> template_array;

    int size = (int)card_array.size();
    int line = 0;

    while (line * 5 < size) {
        template_array.clear();
        for (int i = line * 5; i < size && i < line * 5 + 5; ++i) {
            template_array.emplace_back(card_array.at(i));

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
