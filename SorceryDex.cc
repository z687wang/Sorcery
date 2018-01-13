#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include "SorceryDex.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantment.h"

using namespace std;

SorceryDex::~SorceryDex() {
    // for (auto &pair : database) {
    //     delete pair.second;
    // }
}

void SorceryDex::set(string s, shared_ptr<Card> c) {
    //cout<<c->getName()<<endl;
    database[s] = c;
    //cout<<"I have done this"<<endl;
}

shared_ptr<Card> SorceryDex::get(string s) {
    return database.at(s);
}

istream &operator>>(istream &in, SorceryDex &dex){
    string line;
    char separator = '|';
    while (getline(in, line)) {
        istringstream ss {line};
        string type;
        string info;
        int index = 0;
        int attack = 0, defense = 0, cost = 0, actCost = 0, id = 0;
        string name, effects, abType, triggerType;
        while (getline(ss, info, separator)) {
            if (info[0] == '#') getline(ss, info);
            istringstream convert {info};
            switch (index) {
                case 0:
                    type = info;
                    break;
                case 1:
                    name = info;
                    break;
                case 2:
                    convert >> cost;
                    break;
                case 3:
                    convert >> attack;
                    break;
                case 4:
                    convert >> defense;
                    break;
                case 5:
                    if (info == "None") effects = "";
                    else effects = info;
                    break;
                case 6:
                    abType = info;
                    break;
                case 7:
                    convert >> actCost;
                    break;
                case 8:
                    convert >> id;
                    break;
                case 9:
                    triggerType = info;
                    break;
            }
            index++;
        }
        if (type == "Minion") {
            if (abType == "Triggered") {
                shared_ptr<Trigger> newTrigger;
                if (triggerType == "Start") newTrigger = make_shared<Trigger> (TriggerType::Start, id, actCost);
                else if (triggerType == "End") newTrigger = make_shared<Trigger> (TriggerType::End, id, actCost);
                else if (triggerType == "MinionEnter") newTrigger = make_shared<Trigger> (TriggerType::MinionEnter, id, actCost);
                else if (triggerType == "MinionDead") newTrigger = make_shared<Trigger> (TriggerType::MinionDead, id, actCost);
                shared_ptr<Minion> newMinion (new Minion {name, cost, effects, attack, defense});
                shared_ptr<Card> newCard {new Enchantment(newMinion, name, cost, effects, 0, 0, nullptr, newTrigger, 0, true)};
                dex.set(name, newCard);
            }
            else if (abType == "Activated") {
                shared_ptr<Spell> newSpell {new Spell (id, name, actCost, effects)};
                shared_ptr<Minion> newMinion {new Minion (name, cost, effects, attack, defense)};
                shared_ptr<Enchantment> newCard {new Enchantment (newMinion, name, cost, effects, 0, 0, newSpell, nullptr, 0, true)};
                dex.set(name, static_pointer_cast<Card>(newCard));
            }
            else {
                shared_ptr<Card> newCard {new Minion (name, cost, effects, attack, defense)};
                dex.set(name, newCard);
                //return in;
            }
        }
        else if (type == "Spell") {
            shared_ptr<Spell> newCard {new Spell (id, name, cost, effects)};
            dex.set(name, static_pointer_cast<Card>(newCard));
        }
        else if (type == "Ritual") {
            shared_ptr<Trigger> newTrigger;
            if (triggerType == "Start") newTrigger = make_shared <Trigger> (TriggerType::Start, id, actCost);
            else if (triggerType == "End") newTrigger = make_shared <Trigger> (TriggerType::End, id, actCost);
            else if (triggerType == "MinionEnter") newTrigger = make_shared <Trigger> (TriggerType::MinionEnter, id, actCost);
            shared_ptr<Card> newCard {new Ritual (name, cost, effects, defense, newTrigger)};
            dex.set(name, newCard);
        }
        else {
            shared_ptr<Spell> newSpell;
            if (abType == "Activated") {
                newSpell = make_shared<Spell> (id, "", actCost, effects);
            }
            shared_ptr<Card> newCard {new Enchantment (nullptr, name, cost, effects, attack, defense, newSpell, nullptr, id, false)};
            dex.set(name, newCard);
        }
    }
    return in;
}
