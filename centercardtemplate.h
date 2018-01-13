#ifndef CENTERCARDTEMPLATE_H
#define CENTERCARDTEMPLATE_H

#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QSharedPointer>

class CenterCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit CenterCardTemplate(int x, int y, QWidget *parent = nullptr);

signals:

public slots:
private:
    QSharedPointer<QLabel> l;
    QSharedPointer<QGridLayout> layout;
};

#endif // CENTERCARDTEMPLATE_H
