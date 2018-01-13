#include "playercardtemplate.h"
#include <QLabel>
#include <QGridLayout>

PlayerCardTemplate::PlayerCardTemplate(int x, int y, const QString &text, int health, int magic, QWidget *parent, bool player1) : CardTemplate(x, y, parent)
{
    this->setStyleSheet("background-color: white");
    name = QSharedPointer<QLabel>(new QLabel(this));
    healthLabel = QSharedPointer<QLabel>(new QLabel(this));
    magicLabel = QSharedPointer<QLabel>(new QLabel(this));
    name->setText(text);
    name->setAlignment(Qt::AlignCenter);
    healthLabel->setText(QString::number(health));
    healthLabel->setAlignment(Qt::AlignLeft);
    magicLabel->setText(QString::number(magic));
    magicLabel->setAlignment(Qt::AlignRight);
    layout = QSharedPointer<QGridLayout>(new QGridLayout());
    layout->addWidget(name.data(), (player1 ? 0 : 1), 0, 2, 2);
    layout->addWidget(healthLabel.data(), (player1 ? 2 : 0), 0, 1, 1);
    layout->addWidget(magicLabel.data(), (player1 ? 2 : 0), 1, 1, 1);
//    layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout.data());
}

void PlayerCardTemplate::setName(const QString &text) {
    name->setText(text);
}
