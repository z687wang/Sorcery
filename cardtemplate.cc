#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <iostream>

CardTemplate::CardTemplate(int x, int y, QWidget *parent) : QFrame(parent), x(x), y(y)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setFixedSize(220, 135);
}
