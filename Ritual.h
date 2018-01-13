#ifndef Ritual_h
#define Ritual_h

#include <memory>
#include "Card.h"

class Trigger;
class Game;

class Ritual : public Card {
    int charge;
    std::shared_ptr<Trigger> trigger;

public:
    // Constructor and destructor
    Ritual(std::string name, int cost, std::string desc, int charge, std::shared_ptr<Trigger> trigger);
    Ritual(std::string name, int cost, std::string desc, std::shared_ptr<Player> p, int charge, std::shared_ptr<Trigger> trigger);
    virtual ~Ritual();
    // override copy constructor
    Ritual(const Ritual &ritual);

    // Setter and getter
    std::shared_ptr<Trigger> getTrigger();
    void setTrigger(std::shared_ptr<Trigger> trigger);
    int getCharge();
    void setCharge(int charge);

    // Utility methods
    std::shared_ptr<Card> clone() const override;
    card_template_t getCardTemplate() override;
    void prettyPrint() override;
    CardType getType() override;
    CardTemplate *getGraphicsCardTemplate(int x, int y, QWidget *parent) override;

    // Override Card actions
    void play(std::shared_ptr<Game> g) override;
    void play(std::shared_ptr<Game> g, int i, int j) override;

    // Actions
    void die(std::shared_ptr<Game> g);
};

#endif /* Ritual_h */
