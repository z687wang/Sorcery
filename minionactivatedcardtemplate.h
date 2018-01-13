#ifndef MINIONACTIVATEDCARDTEMPLATE_H
#define MINIONACTIVATEDCARDTEMPLATE_H
#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QSharedPointer>

class MinionActivatedCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit MinionActivatedCardTemplate(int x, int y, const QString &name,  int cost, int attack, int defense, int spellCost, const QString spellDesc, QWidget *parent = nullptr);

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
    QSharedPointer<QLabel> spellCostLabel;
};

#endif // MINIONACTIVATEDCARDTEMPLATE_H
