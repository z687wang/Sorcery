#ifndef MINIONCARDTEMPLATE_H
#define MINIONCARDTEMPLATE_H

#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QSharedPointer>

class MinionCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit MinionCardTemplate(int x, int y, const QString &name, int cost, int attack, int defense, QWidget *parent = nullptr);

signals:

public slots:
private:
    QSharedPointer<QPalette> palette;
    QSharedPointer<QLabel> nameLabel;
    QSharedPointer<QLabel> costLabel;
    QSharedPointer<QLabel> attackLabel;
    QSharedPointer<QLabel> defenseLabel;
    QSharedPointer<QLabel> descLabel;
    QSharedPointer<QGridLayout> layout;
};

#endif // MINIONCARDTEMPLATE_H
