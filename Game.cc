#include "Game.h"
#include "Player.h"
#include "ascii_graphics.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;


Game::Game(shared_ptr<Player> player1, shared_ptr<Player> player2) : player1{player1}, player2{player2}, currentPlayer{1}, dex{nullptr}, gameEnd{false} {}

Game::~Game() {
    // delete player1;
    // delete player2;
    // delete dex;
    // triggers will be deleted when the minion or ritual that owns them is deleted.
}

void Game::render() const {
    cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for (int i = 0; i < 5 * 33; ++i) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;

    vector<vector<card_template_t>> template_array;
    for (int i = 0; i < 5; ++i){
        template_array.emplace_back(vector<card_template_t>());
    }

    template_array[0].emplace_back((player1->getRitual() ?
                                    player1->getRitual()->getCardTemplate()
                                    : CARD_TEMPLATE_BORDER));
    template_array[0].emplace_back(CARD_TEMPLATE_EMPTY);
    template_array[0].emplace_back(display_player_card(1, player1->getName(), player1->getLife() - player1->getDamage(), player1->getMagic()));
    template_array[0].emplace_back(CARD_TEMPLATE_EMPTY);

    if (player1->getGraveyard()->empty()) {
        template_array[0].emplace_back(CARD_TEMPLATE_BORDER);
    } else {
        shared_ptr<Card> c = player1->getGraveyard()->last();
        template_array[0].emplace_back(c->getCardTemplate());
    }

    for (int i = 0; i < player1->getTheBoard()->size(); ++i) {
        template_array[1].emplace_back(player1->getTheBoard()->at(i)->getCardTemplate());
    }

    for (int i = 0; i < 5 - player1->getTheBoard()->size(); ++i) {
        template_array[1].emplace_back(CARD_TEMPLATE_BORDER);
    }


    template_array[2].emplace_back(CENTRE_GRAPHIC);

    for (int i = 0; i < player2->getTheBoard()->size(); ++i) {
        template_array[3].emplace_back(player2->getTheBoard()->at(i)->getCardTemplate());
    }

    for (int i = 0; i < 5 - player2->getTheBoard()->size(); ++i) {
        template_array[3].emplace_back(CARD_TEMPLATE_BORDER);
    }

    template_array[4].emplace_back((player2->getRitual() ?
                                    player2->getRitual()->getCardTemplate()
                                    : CARD_TEMPLATE_BORDER));
    template_array[4].emplace_back(CARD_TEMPLATE_EMPTY);
    template_array[4].emplace_back(display_player_card(2, player2->getName(), player2->getLife() - player2->getDamage(), player2->getMagic()));
    template_array[4].emplace_back(CARD_TEMPLATE_EMPTY);
    if (player2->getGraveyard()->empty()) {
        template_array[4].emplace_back(CARD_TEMPLATE_BORDER);
    } else {
        shared_ptr<Card> c = player2->getGraveyard()->last();
        template_array[4].emplace_back(c->getCardTemplate());
    }

    for (auto it = template_array.begin(); it != template_array.end(); ++it) {
        for (int i = 0; i < (*it)[0].size(); ++i) {
            if ((*it).size() != 1) cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
            for (auto it1 = (*it).begin(); it1 != (*it).end(); ++it1) {
                cout << (*it1)[i];
            }
            if ((*it).size() != 1) cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
            cout << endl;
        }
    }

    cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (int i = 0; i < 5 * 33; ++i) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;

}

shared_ptr<Player> Game::getCurrentPlayer() {
    if (currentPlayer == 1) {
        return player1;
    } else {
        return player2;
    }
}

shared_ptr<Player> Game::getNonCurrentPlayer() {
    if (currentPlayer == 1) {
        return player2;
    } else {
        return player1;
    }
}

shared_ptr<Player> Game::getPlayer1() {
    return player1;
}

shared_ptr<Player> Game::getPlayer2() {
    return player2;
}

void Game::endTurn() {
    notifyTriggers(TriggerType::End);
    if (currentPlayer == 1) {
        currentPlayer = 2;
        player2->draw(1);
        player2->setMagic(player2->getMagic() + 1);
        player2->getTheBoard()->activate();
    } else {
        currentPlayer = 1;
        player1->draw(1);
        player1->setMagic(player1->getMagic() + 1);
        player1->getTheBoard()->activate();
    }
    notifyTriggers(TriggerType::Start);
}

void Game::addTrigger(shared_ptr<Trigger> trigger) {
    if (trigger != nullptr) {
        trigger->getOwner()->addTrigger(trigger);
    }
}

void Game::removeTrigger(shared_ptr<Trigger> trigger) {
    trigger->getOwner()->removeTrigger(trigger);
}

void Game::notifyTriggers(TriggerType t) {
    getCurrentPlayer()->notifyTrigger(t, shared_from_this());
    if (getCurrentPlayer()->getRitual()) {
        if (getCurrentPlayer()->getRitual()->getTrigger()->getType() == t) {
          getCurrentPlayer()->getRitual()->getTrigger()->notify(shared_from_this());
        }
    }
    getNonCurrentPlayer()->notifyTrigger(t, shared_from_this());
    if (getNonCurrentPlayer()->getRitual()) {
        if (getNonCurrentPlayer()->getRitual()->getTrigger()->getType() == t){
            getNonCurrentPlayer()->getRitual()->getTrigger()->notify(shared_from_this());
        }
    }
    
    for (int i = 0; i < getCurrentPlayer()->getTheBoard()->size(); i++) {
        getCurrentPlayer()->getTheBoard()->at(i)->takeDamage(shared_from_this(), 0);
    }
    
    for (int i = 0; i < getNonCurrentPlayer()->getTheBoard()->size(); i++) {
        getNonCurrentPlayer()->getTheBoard()->at(i)->takeDamage(shared_from_this(), 0);
    }
}

void Game::setSorceryDex(shared_ptr<SorceryDex> dex) {
    //delete this->dex;
    this->dex = dex;
}

shared_ptr<SorceryDex> Game::getSorceryDex() {
    return dex;
}

void Game::EndGame(shared_ptr<Player> losePlayer) {
    cout << "GG" << endl;
    if (losePlayer->getName() != player1->getName()) cout << player1->getName() << " wins the game!" << endl;
    else cout << player2->getName() << " wins the game!" << endl;
    gameEnd = true;
}

bool Game::getEnd() { return gameEnd; }
