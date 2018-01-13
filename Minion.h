#ifndef Minion_h
#define Minion_h

#include "Card.h"
#include "CardType.h"
#include "Game.h"
#include <vector>
#include <memory>
#include <cardtemplate.h>

class Enchantment;

class Minion : public Card {
protected:
    int attack;
    int defense;
    int damage;
    bool activate;
public:
    // Constructor and destructor
    Minion(std::string name, int cost, std::string desc, int attack, int defense);
    Minion(std::string name, int cost, std::string desc, std::shared_ptr<Player> p, int attack, int defense);
    virtual ~Minion() = default;

    // Getter and setter
    virtual int getAttack();
    virtual int getDefense();
    virtual int getDamage();
    virtual void setDamage(int damage);
    virtual void setAttack(int attack);
    virtual void setDefense(int defense);
    virtual void addAttack(int attack);
    virtual void addDefense(int defense);
    virtual void setActivate(bool b);
    virtual bool getActivate();
    virtual std::shared_ptr<Minion> getBase();
    virtual std::shared_ptr<Minion> getNextBase();
    virtual void setBase(std::shared_ptr<Minion> m);
    virtual std::shared_ptr<Trigger> getTrigger();
    virtual void setTrigger(std::shared_ptr<Trigger> trigger);
    virtual void useSpell();
    virtual std::shared_ptr<Spell> getSpell();
    virtual void setSpell(std::shared_ptr<Spell> spell);
    virtual int getSpellCost();

    // Utility methods
    std::shared_ptr<Card> clone() const override;
    virtual card_template_t getCardTemplate() override;
    virtual std::vector<card_template_t> getTemplateArray();
    CardType getType() override;
    void prettyPrint() override;
    CardTemplate *getGraphicsCardTemplate(int x, int y, QWidget *parent) override;

    // Action of minions
    virtual void takeDamage(std::shared_ptr<Game> g, int i);
    virtual void die(std::shared_ptr<Game> g);
    virtual void applyEnchantment(std::shared_ptr<Enchantment> e);
    virtual void useAbility(std::shared_ptr<Game> g);
    virtual void useAbility(std::shared_ptr<Game> g, int i, int j);
    virtual void attackOpponent(std::shared_ptr<Game> g);
    virtual void attackOpponentMinion(std::shared_ptr<Game> g, int i);
    virtual void inspect();

    // Override action of cards
    void play(std::shared_ptr<Game> g) override;
    void play(std::shared_ptr<Game> g, int i, int j) override;
};

#endif /* Minion_h */
