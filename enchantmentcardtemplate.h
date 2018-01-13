#ifndef ENCHANTMENTCARDTEMPLATE_H
#define ENCHANTMENTCARDTEMPLATE_H

#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QSharedPointer>

class EnchantmentCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit EnchantmentCardTemplate(int x, int y, const QString &name,  int cost, const QString desc, QWidget *parent = nullptr);

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

#endif // ENCHANTMENTCARDTEMPLATE_H
