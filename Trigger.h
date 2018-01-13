#ifndef Trigger_h
#define Trigger_h

#include "Card.h"
#include "TriggerType.h"
#include "Ritual.h"
#include "Game.h"
#include <memory>
class Player;

/************************************
Trigger.h

This header file includes the class about triggers
Explain: this is one of the core execution block, where every
         ability with a trigger would be in type of Trigger, and
         will be executed through method "notify(Gmae *g)"
         detail of how the method works will be avaliable in
         the implementation
 - Type of trigger (one of: Start, End, Minion Enter, Minion Dead)
 - Who owns the trigger (ie, which player, used to determine in cases
                         where target is player specified, ie not attack him
                         self, that which player should get attacked)
 - Which ritual it represents: since
************************************/
class Trigger {
    int trigger_id;
    int cost;
    TriggerType type;
    std::weak_ptr<Player> owner;
    std::weak_ptr<Ritual> ritual;

public:
    Trigger(TriggerType type, int trigger_id, int cost);
    Trigger(const Trigger &trigger);
    ~Trigger() = default;

    int getCost();
    TriggerType getType() const;

    void setOwner(std::shared_ptr<Player> owner);

    void setRitual(std::shared_ptr<Ritual> ritual);

    void setCost(int cost);

    std::shared_ptr<Player> getOwner();

    void notify(std::shared_ptr<Game> g);
};

#endif /* Trigger_h */
