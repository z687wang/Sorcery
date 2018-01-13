#ifndef Card_h
#define Card_h

#include <string>
#include <memory>
#include "CardType.h"
#include "ascii_graphics.h"
#include <cardtemplate.h>
#include <QSharedPointer>
#include <QWidget>

class Player;
class Trigger;
class Spell;
class Game;
class Minion;
class Enchantment;

class Card: public std::enable_shared_from_this <Card> {
protected:
    std::string name;
    int cost;
    std::string desc;
    std::weak_ptr<Player> owner;
public:
    // Constructor and destructor
    Card(std::string name, int cost, std::string desc);
    Card(std::string name, int cost, std::string desc, std::shared_ptr<Player> p);
    virtual ~Card() = default;

    // Getter and setter
    virtual std::string getName();
    void setName(std::string name);
    virtual int getCost();
    void setCost(int cost);
    virtual std::string getDesc();
    void setDesc(std::string desc);
    std::shared_ptr<Player> getOwner();
    void setOwner(std::shared_ptr<Player> owner);

    // Utility methods
    virtual std::shared_ptr<Card> clone() const = 0;
    virtual void prettyPrint() = 0;
    virtual card_template_t getCardTemplate();
    virtual CardType getType() = 0;

    // Action methods
    virtual void play(std::shared_ptr<Game> g) = 0;
    virtual void play(std::shared_ptr<Game> g, int i, int j) = 0;
    virtual CardTemplate *getGraphicsCardTemplate(int x, int y, QWidget *parent) = 0;

};


#endif /* Card_h */
