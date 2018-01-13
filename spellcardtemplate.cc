#include "spellcardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>

SpellCardTemplate::SpellCardTemplate(int x, int y, const QString &name, const QString &desc, int cost, QWidget *parent) : CardTemplate(x, y, parent)
{
    this->setFrameStyle(QFrame::Box);
    this->setLineWidth(3);
    this->setStyleSheet("background-color: white;");
    palette = QSharedPointer<QPalette>(new QPalette());
    palette->setColor(QPalette::Foreground,Qt::blue);
    this->setPalette(*palette);

    this->setStyleSheet("background-color: white");
    nameLabel = QSharedPointer<QLabel>(new QLabel(this));
    costLabel = QSharedPointer<QLabel>(new QLabel(this));
    descLabel = QSharedPointer<QLabel>(new QLabel(this));
    nameLabel->setText(name);
    nameLabel->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    descLabel->setText(desc);
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    descLabel->setMaximumWidth(this->width());
    costLabel->setText(QString::number(cost));
    costLabel->setAlignment(Qt::AlignRight|Qt::AlignTop);

    layout = QSharedPointer<QGridLayout>(new QGridLayout());
    layout->addWidget(nameLabel.data(), 1, 1, 1, 3);
    layout->addWidget(costLabel.data(), 1, 4, 1, 1);
    layout->addWidget(descLabel.data(), 2, 0, 5, 5);
//    layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout.data());
}
