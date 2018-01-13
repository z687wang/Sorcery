#ifndef ENCHANTMENTADCARDTEMPLATE_H
#define ENCHANTMENTADCARDTEMPLATE_H

#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QSharedPointer>

class EnchantmentADCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit EnchantmentADCardTemplate(int x, int y, const QString &name, const QString &desc, int cost, int attack, int defense, QWidget *parent = nullptr);

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

#endif // ENCHANTMENTADCARDTEMPLATE_H
