#include "centercardtemplate.h"

CenterCardTemplate::CenterCardTemplate(int x, int y, QWidget *parent) : CardTemplate(x, y, parent)
{
    QString s("Sorcery!");
    this->setStyleSheet("background-color: transparent");
    l = QSharedPointer<QLabel>(new QLabel(this));
    l->setText(s);
    l->setWordWrap(true);
    l->setAlignment(Qt::AlignCenter);
    QFont font = l->font();
    font.setPointSize(40);
    font.setItalic(true);
    l->setFont(font);
    layout = QSharedPointer<QGridLayout>(new QGridLayout());
    layout->addWidget(l.data());
//    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setAlignment(Qt::AlignCenter);
    this->setFixedWidth(1220);
    this->setFixedHeight(80);
    setLayout(layout.data());
}
