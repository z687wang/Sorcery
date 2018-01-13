#ifndef MINIONTRIGGEREDCARDTEMPLATE_H
#define MINIONTRIGGEREDCARDTEMPLATE_H
#include "cardtemplate.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QSharedPointer>

class MinionTriggeredCardTemplate : public CardTemplate
{
    Q_OBJECT
public:
    explicit MinionTriggeredCardTemplate(int x, int y, const QString &name, int cost, int attack, int defense, const QString &desc, QWidget *parent = nullptr);

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

#endif // MINIONTRIGGEREDCARDTEMPLATE_H
