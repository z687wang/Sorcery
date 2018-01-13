#include "canvas.h"
#include "cardtemplate.h"
#include "playercardtemplate.h"
#include "centercardtemplate.h"
#include "minioncardtemplate.h"
#include <QGridLayout>
#include <iostream>
#include <QMouseEvent>
#include <QPushButton>
#include "Player.h"
#include "Game.h"
#include "SorceryDex.h"
#include "Deck.h"
#include "Board.h"
#include "Minion.h"
#include "ascii_graphics.h"
#include "InvalidMoveException.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    use = false;
    empty = QSharedPointer<CardTemplate>(new CardTemplate(-1, -1, this));
    r1 = QSharedPointer<CardTemplate>(new CardTemplate(1, 0, this));
    g1 = QSharedPointer<CardTemplate>(new CardTemplate(1, 4, this));
    for (int i = 0; i < 5; i++) {
        player1board[i] = QSharedPointer<CardTemplate>(new CardTemplate(2, i, this));
        player2board[i] = QSharedPointer<CardTemplate>(new CardTemplate(4, i, this));
        hand[i] = QSharedPointer<CardTemplate>(new CardTemplate(6, i, this));
    }

    r2 = QSharedPointer<CardTemplate>(new CardTemplate(5, 0, this));
    g2 = QSharedPointer<CardTemplate>(new CardTemplate(5, 4, this));

    p1 = QSharedPointer<PlayerCardTemplate>(new PlayerCardTemplate(1, 3, "", 20, 3, this, true));
    p2 = QSharedPointer<PlayerCardTemplate>(new PlayerCardTemplate(5, 3, "", 20, 3, this, false));

    c = QSharedPointer<CardTemplate>(new CenterCardTemplate(3, 0, this));
    endTurnButton = QSharedPointer<QPushButton>(new QPushButton(this));

    endTurnButton->setText("End Turn");
    endTurnButton->move(1100, 335);
    endTurnButton->setStyleSheet("background-color: white");


    mainLayout = QSharedPointer<QGridLayout>(new QGridLayout());

    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(10);
    this->setFixedSize(1320, 840);
    mainLayout->addWidget(r1.data(), 1, 0, 1, 1);
    mainLayout->addWidget(empty.data(), 1, 1, 1, 1);
    mainLayout->addWidget(p1.data(), 1, 2, 1, 1);
    mainLayout->addWidget(empty.data(), 1, 3, 1, 1);
    mainLayout->addWidget(g1.data(), 1, 4, 1, 1);

    for (int i = 0; i < 5; i++) {
        mainLayout->addWidget(player1board[i].data(), 2, i, 1, 1);
        mainLayout->addWidget(player2board[i].data(), 4, i, 1, 1);
        mainLayout->addWidget(hand[i].data(), 6, i, 1, 1);
    }

    mainLayout->addWidget(c.data(), 3, 0, 1, 5);

    mainLayout->addWidget(r2.data(), 5, 0, 1, 1);
    mainLayout->addWidget(empty.data(), 5, 1, 1, 1);
    mainLayout->addWidget(p2.data(), 5, 2, 1, 1);
    mainLayout->addWidget(empty.data(), 5, 3, 1, 1);
    mainLayout->addWidget(g2.data(), 5, 4, 1, 1);

    setLayout(mainLayout.data());

    connect(endTurnButton.data(), SIGNAL(released()), this, SLOT(endButton()));

    bool ok;
    QString player1name = "";
    while (player1name.isEmpty()) {
        player1name = QInputDialog::getText(this, tr("Name"),
                                            tr("Player 1 name:"), QLineEdit::Normal,
                                            "Player 1", &ok);
    }
    if (ok) p1->setName(player1name);
    ok = false;
    QString player2name = "";
    while (player2name.isEmpty()) {
        player2name = QInputDialog::getText(this, tr("Name"),
                                            tr("Player 2 name:"), QLineEdit::Normal,
                                            "Player 2", &ok);
    }
    if (ok) p2->setName(player2name);

    std::shared_ptr<Player> p_1 = std::shared_ptr<Player>(new Player{player1name.toStdString(), false});
    std::shared_ptr<Player> p_2 = std::shared_ptr<Player>(new Player{player2name.toStdString(), false});
    g = std::shared_ptr<Game>(new Game{p_1, p_2});

    std::shared_ptr<SorceryDex> dex = std::shared_ptr<SorceryDex>(new SorceryDex());
    std::ifstream cards{"cardInfo"};
    cards >> *dex;

    std::shared_ptr<Deck> p1_deck = std::shared_ptr<Deck>(new Deck());
    std::shared_ptr<Deck> p2_deck = std::shared_ptr<Deck>(new Deck());

    std::string deck1_file = "default.deck";
    std::string deck2_file = "default.deck";

    std::shared_ptr<std::istream> deck1_file_s {new std::ifstream{deck1_file}};
    std::shared_ptr<std::istream> deck2_file_s {new std::ifstream{deck2_file}};

    p1_deck->setDeck(*deck1_file_s, *dex);
    p2_deck->setDeck(*deck2_file_s, *dex);

    g->setSorceryDex(dex);

    p_1->setTheDeck(p1_deck);
    p_2->setTheDeck(p2_deck);

    p1_deck->shuffle(1);
    p2_deck->shuffle(2);

    p_1->draw(4);
    p_2->draw(4);

    render(g);
}

Canvas::~Canvas()
{
}

void Canvas::useAbility(QMouseEvent *eventPress) {
    use = true;
    mousePressEvent(eventPress);
}

void Canvas::endButton() {
    if (!g->getEnd()) {
        g->endTurn();
        render(g);
    }
}

void Canvas::mousePressEvent(QMouseEvent *eventPress) {
    startPosition = eventPress->pos();
    int sx = ptorow(startPosition.y());
    std::cout << "canvas press" << std::endl;
    if (432 <= startPosition.y() && startPosition.y() <= 500 && sx != 0) {
        use = true;
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *eventPress) {
    if (g->getEnd()) return;
    endPosition = eventPress->pos();
    std::cout << "canvas release" << std::endl;
    
    int sx, sy, ex, ey;
    std::shared_ptr<Card> c;
    sy = ptocol(startPosition.x());
    sx = ptorow(startPosition.y());
    ey = ptocol(endPosition.x());
    ex = ptorow(endPosition.y());

    std::cout << "from " << startPosition.x() << ", " << startPosition.y() << " to " << endPosition.x() << ", " << endPosition.y() << std::endl;
    std::cout << "from " << sx << ", " << sy << " to " << ex << ", " << ey << std::endl;
    if (sx == 0 || sy == 0) return;
    try {
        switch (sx) {
        case 3:
            switch (ex) {
            case 1:
                g->getCurrentPlayer()->getTheBoard()->at(sy - 1)->attackOpponent(g);
                break;
            case 2:
                if (use) {
                    try {
                        g->getCurrentPlayer()->getTheBoard()->at(sy - 1)->useAbility(g, (g->getCurrentPlayer() == g->getPlayer1() ? 2 : 1),  ey);
                    } catch (InvalidMoveException e) {
                        try {
                            g->getCurrentPlayer()->getTheBoard()->at(sy - 1)->useAbility(g);
                        } catch (InvalidMoveException e) {
                            g->getCurrentPlayer()->getTheBoard()->at(sy - 1)->attackOpponentMinion(g, ey - 1);
                        }
                    }
                }
                else g->getCurrentPlayer()->getTheBoard()->at(sy - 1)->attackOpponentMinion(g, ey - 1);
                break;
            case 3:
                std::cout << "testing3" << std::endl;
                if (use) {
                    try {
                        std::cout << "testing" << std::endl;
                        g->getCurrentPlayer()->getTheBoard()->at(sy - 1)->useAbility(g, (g->getCurrentPlayer() == g->getPlayer1() ? 1 : 2),  ey);
                        std::cout << "testing" << std::endl;
                    } catch (InvalidMoveException e) {
                        e.prettyprint();
                        try {
                            g->getCurrentPlayer()->getTheBoard()->at(sy - 1)->useAbility(g);
                        } catch (InvalidMoveException e) {
                        }
                    }
                }
            }
            break;
        case 5:
            c = g->getCurrentPlayer()->getHand()->at(sy - 1);
            switch (ex) {
            case 0:
                c->play(g);
                g->getCurrentPlayer()->getHand()->remove(sy - 1);
                break;
            case 2:
                if (ey != 0) c->play(g, (g->getCurrentPlayer() == g->getPlayer1() ? 2 : 1), ey);
                else c->play(g);
                g->getCurrentPlayer()->getHand()->remove(sy - 1);
                break;
            case 1:
                if (ey == 1) c->play(g, (g->getCurrentPlayer() == g->getPlayer1() ? 2 : 1), 6);
                else c->play(g);
                g->getCurrentPlayer()->getHand()->remove(sy - 1);
                break;
            case 3:
                if (ey != 0) c->play(g, (g->getCurrentPlayer() == g->getPlayer1() ? 1 : 2), ey);
                else c->play(g);
                g->getCurrentPlayer()->getHand()->remove(sy - 1);
                break;
            case 4:
                if (ey == 1) c->play(g, (g->getCurrentPlayer() == g->getPlayer1() ? 1 : 2), 6);
                else c->play(g);
                g->getCurrentPlayer()->getHand()->remove(sy - 1);
                break;
            }
            break;
        default:
            break;
        }
    }
    catch (InvalidMoveException e) {
        e.prettyprint();
    }
    try {
      render(g);
    } catch (std::bad_alloc e) {
    }
    use = false;
}

int Canvas::ptorow(int p) {
    if (p >= 20 && p <= 154) {
        return 1;
    } else if (p >= 164 && p <= 298) {
        return 2;
    } else if (p >= 398 && p <= 532) {
        return 3;
    } else if (p >= 542 && p <= 676) {
        return 4;
    } else if (p >= 686 && p <= 820) {
        return 5;
    }
    return 0;
}

int Canvas::ptocol(int p) {
    if (p >= 50 && p <= 269) {
        return 1;
    } else if (p >= 306 && p <= 525) {
        return 2;
    } else if (p >= 549 && p <= 768) {
        return 3;
    } else if (p >= 792 && p <= 1011) {
        return 4;
    } else if (p >= 1035 && p <= 1254) {
        return 5;
    }
    return 0;
}



void Canvas::render(std::shared_ptr<Game> g) {
    std::shared_ptr<Player> player1 = g->getNonCurrentPlayer();
    std::shared_ptr<Player> player2 = g->getCurrentPlayer();
    std::shared_ptr<Ritual> ritual1 = player1->getRitual();
    std::shared_ptr<Ritual >ritual2 = player2->getRitual();

    mainLayout->removeWidget(p1.data());
    mainLayout->removeWidget(p2.data());
    p1 = QSharedPointer<PlayerCardTemplate>(new PlayerCardTemplate(1, 3, QString::fromStdString(player1->getName()), player1->getLife() - player1->getDamage(), player1->getMagic(), this, true));
    p2 = QSharedPointer<PlayerCardTemplate>(new PlayerCardTemplate(5, 3, QString::fromStdString(player2->getName()), player2->getLife() - player2->getDamage(), player2->getMagic(), this, true));
    mainLayout->addWidget(p1.data(), 1, 2, 1, 1);
    mainLayout->addWidget(p2.data(), 5, 2, 1, 1);

    mainLayout->removeWidget(r1.data());
    if (ritual1) {
        r1 = QSharedPointer<CardTemplate>(ritual1->getGraphicsCardTemplate(1, 0, this));
    } else {
        r1 = QSharedPointer<CardTemplate>(new CardTemplate(1, 0, this));
    }
    mainLayout->addWidget(r1.data(), 1, 0);

    mainLayout->removeWidget(r2.data());
    if (ritual2) {
        r2 = QSharedPointer<CardTemplate>(ritual2->getGraphicsCardTemplate(5, 0, this));
    } else {
        r2 = QSharedPointer<CardTemplate>(new CardTemplate(5, 0, this));
    }
    mainLayout->addWidget(r2.data(), 5, 0);

    mainLayout->removeWidget(g1.data());
    mainLayout->removeWidget(g2.data());


    if (!player1->getGraveyard()->empty()) {
        g1 = QSharedPointer<CardTemplate>(player1->getGraveyard()->last()->getGraphicsCardTemplate(1, 4, this));
    } else {
        g1 = QSharedPointer<CardTemplate>(new CardTemplate(1, 4, this));
    }
    mainLayout->addWidget(g1.data(), 1, 4);

    if (!player2->getGraveyard()->empty()) {
        g2 = QSharedPointer<CardTemplate>(player2->getGraveyard()->last()->getGraphicsCardTemplate(5, 4, this));
    } else {
        g2 = QSharedPointer<CardTemplate>(new CardTemplate(5, 4, this));
    }
    mainLayout->addWidget(g2.data(), 5, 4);

    for (int i = 0; i < 5; i++) {
        mainLayout->removeWidget(player1board[i].data());
        mainLayout->removeWidget(player2board[i].data());
        mainLayout->removeWidget(hand[i].data());
        if (i < player1->getTheBoard()->size()) {
            player1board[i] = QSharedPointer<CardTemplate>(player1->getTheBoard()->at(i)->getGraphicsCardTemplate(2, i, this));
        } else {
            player1board[i] = QSharedPointer<CardTemplate>(new CardTemplate(2, i, this));
        }
        mainLayout->addWidget(player1board[i].data(), 2, i);
        if (i < player2->getTheBoard()->size()) {
            player2board[i] = QSharedPointer<CardTemplate>(player2->getTheBoard()->at(i)->getGraphicsCardTemplate(4, i,this));
        } else {
            player2board[i] = QSharedPointer<CardTemplate>(new CardTemplate(4, i, this));
        }
        mainLayout->addWidget(player2board[i].data(), 4, i);
        if (i < g->getCurrentPlayer()->getHand()->size()) {
            hand[i] = QSharedPointer<CardTemplate>(g->getCurrentPlayer()->getHand()->at(i)->getGraphicsCardTemplate(6, i, this));
        } else {
            hand[i] = QSharedPointer<CardTemplate>(new CardTemplate(6, i, this));
        }
        mainLayout->addWidget(hand[i].data(), 6, i);
    }
}
