#ifndef Game_h
#define Game_h

#include <vector>
#include <memory>
#include "Player.h"
#include "Trigger.h"
#include "SorceryDex.h"

class Game : public std::enable_shared_from_this<Game> {
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    int currentPlayer;
    std::shared_ptr<SorceryDex> dex;
    bool gameEnd;
public:
    Game(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2);
    ~Game();
    std::shared_ptr<Player> getCurrentPlayer();
    std::shared_ptr<Player> getNonCurrentPlayer();
    std::shared_ptr<Player> getPlayer1();
    std::shared_ptr<Player> getPlayer2();
    void render() const;
    void endTurn();

    void setSorceryDex(std::shared_ptr<SorceryDex> dex);
    std::shared_ptr<SorceryDex> getSorceryDex();

    void addTrigger(std::shared_ptr<Trigger> trigger);
    void removeTrigger(std::shared_ptr<Trigger> trigger);
    void notifyTriggers(TriggerType t);
    void EndGame(std::shared_ptr<Player> losePlayer);
    bool getEnd();
};


#endif /* Game_h */
