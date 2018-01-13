#ifndef SPELLCARDTEMPLATE_H
#define SPELLCARDTEMPLATE_H

#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QSharedPointer>

class SpellCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit SpellCardTemplate(int x, int y, const QString &name, const QString &desc, int cost, QWidget *parent = nullptr);

signals:

public slots:
private:
    QSharedPointer<QPalette> palette;
    QSharedPointer<QLabel> nameLabel;
    QSharedPointer<QLabel> costLabel;
    QSharedPointer<QLabel> descLabel;
    QSharedPointer<QGridLayout> layout;
};

#endif // SPELLCARDTEMPLATE_H
