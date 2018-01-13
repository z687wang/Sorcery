#ifndef PLAYERCARDTEMPLATE_H
#define PLAYERCARDTEMPLATE_H

#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QSharedPointer>

class PlayerCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit PlayerCardTemplate(int x, int y, const QString &text, int health = 20, int magic = 3, QWidget *parent = nullptr, bool player1 = true);
    void setName(const QString &text);
signals:

public slots:
private:
    QSharedPointer<QLabel> name;
    QSharedPointer<QLabel> healthLabel;
    QSharedPointer<QLabel> magicLabel;
    QSharedPointer<QGridLayout> layout;
};

#endif // PLAYERCARDTEMPLATE_H
