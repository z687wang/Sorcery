#ifndef Enchantment_h
#define Enchantment_h

#include <memory>
#include "Card.h"
#include "Minion.h"
#include "Spell.h"
#include "Trigger.h"
#include "Game.h"

class Minion;

class Enchantment : public Minion {
    std::shared_ptr<Minion> base;
    std::shared_ptr<Spell> spell;
    std::shared_ptr<Trigger> trigger;
    int enchantmentId;
    bool isBaseMinion;

public:
    // Constructor and destructor
    Enchantment(std::shared_ptr<Minion> minion, std::string name, int cost, std::string desc, int attack, int defense, std::shared_ptr<Spell> spell, std::shared_ptr<Trigger> trigger, int enchantmentId, bool isBaseMinion);
    Enchantment(std::shared_ptr<Minion> minion, std::string name, int cost, std::string desc, std::shared_ptr<Player> p, int attack, int defense, std::shared_ptr<Spell> spell, std::shared_ptr<Trigger> trigger, int enchantmentId, bool isBaseMinion);
    virtual ~Enchantment();
    // Override copy constructor
    Enchantment(const Enchantment &enchantment);

    // Override Minion getter and setter
    void setActivate(bool b) override;
    bool getActivate() override;
    int getAttack() override;
    int getDefense() override;
    int getDamage() override;
    void setDamage(int damage) override;
    void setAttack(int attack) override;
    void setDefense(int defense) override;
    void addAttack(int attack) override;
    void addDefense(int defense) override;
    std::shared_ptr<Trigger> getTrigger() override;
    void setTrigger(std::shared_ptr<Trigger> trigger) override;
    std::shared_ptr<Spell> getSpell() override;
    void setSpell(std::shared_ptr<Spell> spell) override;
    int getSpellCost() override;
    std::shared_ptr<Minion> getBase() override;
    std::shared_ptr<Minion> getNextBase() override;
    void setBase(std::shared_ptr<Minion> m) override;
    std::string getName() override;
    std::string getDesc() override;
    int getCost() override;

    // Override Minion utility methods
    std::shared_ptr<Card> clone() const override;
    void prettyPrint() override;
    CardType getType() override;
    std::vector<card_template_t> getTemplateArray() override;
    virtual card_template_t getCardTemplate() override;
    CardTemplate *getGraphicsCardTemplate(int x, int y, QWidget *parent) override;

    // Overrride Minion actions
    void play(std::shared_ptr<Game> g) override;
    void play(std::shared_ptr<Game> g, int i, int j) override;
    void takeDamage(std::shared_ptr<Game> g, int i) override;
    void die(std::shared_ptr<Game> g) override;
    void useAbility(std::shared_ptr<Game> g) override;
    void useAbility(std::shared_ptr<Game> g, int i, int j) override;
    void inspect() override;
};

#endif /* Enchantment_h */
