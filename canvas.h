#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "cardtemplate.h"
#include "playercardtemplate.h"
#include <QPushButton>
#include "Game.h"
#include <QGridLayout>
#include <QPoint>
#include <QSharedPointer>
#include <QScopedArrayPointer>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0);
    ~Canvas();
private:
    QSharedPointer<CardTemplate> empty, r1, g1;
    QSharedPointer<CardTemplate> player1board[5];
    QSharedPointer<CardTemplate> player2board[5];
    QSharedPointer<CardTemplate> r2, g2, c;
    QSharedPointer<CardTemplate> hand[5];
    QSharedPointer<PlayerCardTemplate> p1, p2;
    QSharedPointer<QPushButton> endTurnButton;
    std::shared_ptr<Game> g;
    QSharedPointer<QGridLayout> mainLayout;
    QPoint startPosition, endPosition;
    bool use;
public:
    void useAbility(QMouseEvent *eventPress);
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *eventPress);
    void render(std::shared_ptr<Game> g);

    static int ptorow(int p);
    static int ptocol(int p);
private slots:
    void endButton();
};

#endif // CANVAS_H
