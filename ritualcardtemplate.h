#ifndef RITUALCARDTEMPLATE_H
#define RITUALCARDTEMPLATE_H

#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QSharedPointer>

class RitualCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit RitualCardTemplate(int x, int y, const QString &name, const QString &desc, int cost, int triggerCost, int triggerCharge, QWidget *parent = nullptr);

signals:

public slots:
private:
    QSharedPointer<QPalette> palette;
    QSharedPointer<QLabel> nameLabel;
    QSharedPointer<QLabel> costLabel;
    QSharedPointer<QLabel> triggerChargeLabel;
    QSharedPointer<QLabel> descLabel;
    QSharedPointer<QLabel> triggerCostLabel;
    QSharedPointer<QGridLayout> layout;

};

#endif // RITUALCARDTEMPLATE_H
