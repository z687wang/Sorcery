#include "minioncardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>

MinionCardTemplate::MinionCardTemplate(int x, int y, const QString &text, int cost, int attack, int defense, QWidget *parent) : CardTemplate(x, y, parent)
{
    this->setFrameStyle(QFrame::Box);
    this->setLineWidth(3);
    this->setStyleSheet("background-color: white;");
    palette = QSharedPointer<QPalette>(new QPalette());
    palette->setColor(QPalette::Foreground,Qt::yellow);
    this->setPalette(*palette);

    this->setStyleSheet("background-color: white");
    nameLabel = QSharedPointer<QLabel>(new QLabel(this));
    costLabel = QSharedPointer<QLabel>(new QLabel(this));
    attackLabel = QSharedPointer<QLabel>(new QLabel(this));
    defenseLabel = QSharedPointer<QLabel>(new QLabel(this));
    descLabel = QSharedPointer<QLabel>(new QLabel(this));
    nameLabel->setText(text);
    nameLabel->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    descLabel->setText("");
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    descLabel->setMaximumWidth(this->width());
    costLabel->setText(QString::number(cost));
    costLabel->setAlignment(Qt::AlignRight|Qt::AlignTop);

    attackLabel->setText(QString::number(attack));
    attackLabel->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    defenseLabel->setText(QString::number(defense));
    defenseLabel->setAlignment(Qt::AlignRight|Qt::AlignBottom);
    layout = QSharedPointer<QGridLayout>(new QGridLayout());
    layout->addWidget(nameLabel.data(), 1, 1, 1, 3);
    layout->addWidget(costLabel.data(), 1, 4, 1, 1);

    layout->addWidget(descLabel.data(), 2, 0, 5, 5);
    layout->addWidget(attackLabel.data(), 7, 0, 1, 1);
    layout->addWidget(defenseLabel.data(), 7, 4, 1, 1);
//    layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout.data());
}
