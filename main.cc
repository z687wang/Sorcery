#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include "Player.h"
#include "Game.h"
#include "SorceryDex.h"
#include "Deck.h"
#include "ascii_graphics.h"
#include "InvalidMoveException.h"
#include "canvas.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{

    string deck1_file = "default.deck";
    string deck2_file = "default.deck";
    string init_file = "";
    bool testing = false;
    bool graphics = false;

    for (int i = 1; i < argc; i++) {
        try {
            if (string(argv[i]) == "-deck1") {
                if (i + 1 >= argc) throw out_of_range("");
                deck1_file = string(argv[i+1]);
                ++i;
            } else if (string(argv[i]) == "-deck2") {
                if (i + 1 >= argc) throw out_of_range("");
                deck2_file = string(argv[i+1]);
                ++i;
            } else if (string(argv[i]) == "-init") {
                if (i + 1 >= argc) throw out_of_range("");
                init_file = string(argv[i+1]);
                ++i;
            } else if (string(argv[i]) == "-testing") {
                testing = true;
            } else if (string(argv[i]) == "-graphics") {
                graphics = true;
            }
        }
        catch (out_of_range e) {
            cerr << "Wrong command line arguments" << endl;
        }
    }

    if (graphics) {
        QApplication a(argc, argv);
        Canvas w;
        w.setStyleSheet("background-color: gray;");
        w.setWindowTitle("Sorcery");
        w.show();
        return a.exec();
    } else {
//        cout << "Deck 1: " << deck1_file << endl;
//        cout << "Deck 2: " << deck2_file << endl;
//        cout << "Init file: " << init_file << endl;
//        cout << "Testing mode: " << (testing ? "true" : "false") << endl;

        ifstream fin{init_file};
        istream * stream_ptr = &fin;

        string p1_name, p2_name;
        cout << "Enter player 1 name:" << endl;
        if (!getline(*stream_ptr, p1_name)) {
            if (stream_ptr == &cin) {
                return 1;
            }
            fin.close();
            stream_ptr = &cin;
            getline(*stream_ptr, p1_name);
        }
        cout << "Enter player 2 name:" << endl;
        if (!getline(*stream_ptr, p2_name)) {
            if (stream_ptr == &cin) {
                return 1;
            }
            fin.close();
            stream_ptr = &cin;
            getline(*stream_ptr, p2_name);
        }

        shared_ptr<Player> p_1 {new Player{p1_name, testing}};
        shared_ptr<Player> p_2 {new Player{p2_name, testing}};

        shared_ptr<Game> g {new Game{p_1, p_2}};

        shared_ptr<SorceryDex> dex {new SorceryDex()};
        ifstream cards{"cardInfo"};
        cards >> *dex;

        shared_ptr<Deck> p1_deck {new Deck()};
        shared_ptr<Deck> p2_deck {new Deck()};

        shared_ptr<istream> deck1_file_s {new ifstream{deck1_file}};
        shared_ptr<istream> deck2_file_s {new ifstream{deck2_file}};

        p1_deck->setDeck(*deck1_file_s, *dex);
        p2_deck->setDeck(*deck2_file_s, *dex);

        //delete deck1_file_s; delete deck2_file_s;

        g->setSorceryDex(dex);

        p_1->setTheDeck(p1_deck);
        p_2->setTheDeck(p2_deck);

        if (!testing) {
            p1_deck->shuffle(1);
            p2_deck->shuffle(2);
        }

        p_1->draw(3);
        p_2->draw(3);

        string message = "";
        // GAME LOOP
        string line;
        while (true) {
            if (g->getEnd() == true) break;
            cout << g->getCurrentPlayer()->getName() << ": ";
            if (!getline(*stream_ptr, line)) {
                if (stream_ptr == &cin) {
                    break;
                }
                fin.close();
                stream_ptr = &cin;
                getline(*stream_ptr, line);
            }
            istringstream iss{line};
            string cmd;
            int card = 0, minion = 0;
            int target_player = 0, target_card = 0;
            string target_card_string;
            int i = 0, j = 0;
            iss >> cmd;

            if (cmd == "message") {
                cout<<"Please leave the message here for the other player"<<endl;
                getline(cin,message);
            } else if (cmd == "help") {
                cout << setw(10) << "Commands: " << "help -- Display this message." << endl;
                cout << setw(10) << "" << "end -- End the current player's turn." << endl;
                cout << setw(10) << "" << "quit -- End the game." << endl;
                cout << setw(10) << "" << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
                cout << setw(10) << "" << "attack minion -- Orders minion to attack the opponent." << endl;
                cout << setw(10) << "" << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
                cout << setw(10) << "" << "use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << endl;
                cout << setw(10) << "" << "inspect minion -- View a minion's card and all enchantments on that minion." << endl;
                cout << setw(10) << "" << "hand -- Describe all cards in your hand." << endl;
                cout << setw(10) << "" << "board -- Describe all cards on the board." << endl;
                cout << "Testing commands:" << endl;
                cout << setw(10) << "" << "discard card -- discard a card in our hand." << endl;
                cout << setw(10) << "" << "draw -- draw a card from your deck." << endl;
            } else if (cmd == "end") {
                g->endTurn();
                cout<<endl<<"********************************************************************\n"<<endl;
                if (message != "")
                    cout<<g->getNonCurrentPlayer()->getName()<<" said: "<<message<<endl;
                message = "";

            } else if (cmd == "quit") {
                cout << "Game end." << endl;
                break;
            } else if (cmd == "attack") {
                iss >> i;
                try {
                    if (iss.eof()) {
                        g->getCurrentPlayer()->getTheBoard()->at(i-1)->attackOpponent(g);
                    } else {
                        iss >> j;
                        g->getCurrentPlayer()->getTheBoard()->at(i-1)->attackOpponentMinion(g, i - 1);
                    }
                } catch (InvalidMoveException e) {
                    e.prettyprint();
                }
            } else if (cmd == "play") {
                iss >> card;
                try {
                    shared_ptr<Card> c = g->getCurrentPlayer()->getHand()->at(card - 1);
                    if (iss.eof()) {
                        c->play(g);
                        g->getCurrentPlayer()->getHand()->remove(card - 1);
                    } else {
                        iss >> target_player >> target_card_string;
                        if (target_card_string == "r") target_card = 6;
                        else {
                            istringstream itcs{target_card_string};
                            itcs >> target_card;
                        }
                        c->play(g, target_player, target_card);
                        g->getCurrentPlayer()->getHand()->remove(card - 1);
                    }
                    // if (c->getType() == CardType::Spell) {
                    // }
                } catch (InvalidMoveException e) {
                    e.prettyprint();
                }

            } else if (cmd == "use") {
                iss >> minion;
                try {
                    shared_ptr<Minion> m = g->getCurrentPlayer()->getTheBoard()->at(minion - 1);
                    if (iss.eof()) {
                        m->useAbility(g);
                    } else {
                        iss >> target_player >> target_card_string;
                        if (target_card_string == "r") target_card = 6;
                        else {
                            istringstream itcs{target_card_string};
                            itcs >> target_card;
                        }
                        m->useAbility(g, target_player, target_card);
                    }
                } catch (InvalidMoveException e) {
                    e.prettyprint();
                }
            } else if (cmd == "inspect") {
                iss >> minion;
                try {
                    g->getCurrentPlayer()->getTheBoard()->at(minion - 1)->inspect();
                } catch (InvalidMoveException e) {
                    e.prettyprint();
                }
            } else if (cmd == "hand") {
                g->getCurrentPlayer()->getHand()->render();
            } else if (cmd == "board") {
                g->render();
            } else if (cmd == "discard") {
                iss >> card;
                if (testing) {
                    g->getCurrentPlayer()->getHand()->remove(card - 1);
                } else {
                    InvalidMoveException{"Not in test mode."}.prettyprint();
                }
            } else if (cmd == "draw") {
                if (testing) {
                    g->getCurrentPlayer()->draw(1);
                } else {
                    InvalidMoveException{"Not in test mode."}.prettyprint();
                }
            }
        }
    }
}
