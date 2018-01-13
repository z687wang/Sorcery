#ifndef CARDTEMPLATE_H
#define CARDTEMPLATE_H

#include <QFrame>
#include <QMouseEvent>

class CardTemplate : public QFrame
{
    Q_OBJECT
public:
    explicit CardTemplate(int x, int y, QWidget *parent = nullptr);

signals:

public slots:
protected:
    int x, y;

//    void mousePressEvent(QMouseEvent *eventPress);
//    void mouseReleaseEvent(QMouseEvent *eventPress);
};

#endif // CARDTEMPLATE_H
