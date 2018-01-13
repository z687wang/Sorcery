#include "ritualcardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>

RitualCardTemplate::RitualCardTemplate(int x, int y, const QString &name, const QString &desc, int cost, int triggerCost, int triggerCharge, QWidget *parent) : CardTemplate(x, y, parent)
{
    this->setFrameStyle(QFrame::Box);
    this->setLineWidth(3);
    this->setStyleSheet("background-color: white;");
    palette = QSharedPointer<QPalette>(new QPalette());
    palette->setColor(QPalette::Foreground, Qt::magenta);
    this->setPalette(*palette);

    this->setStyleSheet("background-color: white");
    nameLabel = QSharedPointer<QLabel>(new QLabel(this));
    costLabel = QSharedPointer<QLabel>(new QLabel(this));
    triggerChargeLabel = QSharedPointer<QLabel>(new QLabel(this));
    descLabel = QSharedPointer<QLabel>(new QLabel(this));
    triggerCostLabel = QSharedPointer<QLabel>(new QLabel(this));

    nameLabel->setText(name);
    nameLabel->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    descLabel->setText(desc);
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    descLabel->setMaximumWidth(this->width());
    costLabel->setText(QString::number(cost));
    costLabel->setAlignment(Qt::AlignRight|Qt::AlignTop);

    triggerCostLabel->setText(QString::number(triggerCost));
    triggerCostLabel->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);


    triggerChargeLabel->setText(QString::number(triggerCharge));
    triggerChargeLabel->setAlignment(Qt::AlignRight|Qt::AlignBottom);
    layout = QSharedPointer<QGridLayout>(new QGridLayout());
    layout->addWidget(nameLabel.data(), 1, 1, 1, 3);
    layout->addWidget(costLabel.data(), 1, 4, 1, 1);
    layout->addWidget(triggerCostLabel.data(), 2, 0, 5, 1);
    layout->addWidget(descLabel.data(), 2, 1, 5, 4);
    layout->addWidget(triggerChargeLabel.data(), 7, 4, 1, 1);
//    layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout.data());
}
