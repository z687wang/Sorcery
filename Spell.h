#ifndef Spell_h
#define Spell_h

#include "Card.h"
#include "Game.h"
#include <memory>

class Spell : public Card {
    int spell_id;
public:
    // Constructor and destructor
    Spell(int spell_id, std::string name, int cost, std::string desc);
    Spell(int spell_id, std::string name, int cost, std::string desc, std::shared_ptr<Player> p);
    virtual ~Spell() = default;

    // Utility methods
    std::shared_ptr<Card> clone() const override;
    void prettyPrint() override;
    CardType getType() override;
    card_template_t getCardTemplate() override;
    CardTemplate *getGraphicsCardTemplate(int x, int y, QWidget *parent) override;

    // Override Card actions
    void play(std::shared_ptr<Game> g) override;
    void play(std::shared_ptr<Game> g, int i, int j) override;
};

#endif /* Spell_h */
