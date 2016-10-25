#ifndef ANIMATEQPUSHBUTTON_H
#define ANIMATEQPUSHBUTTON_H

#include "global.h"

#define VAR_STR_GEN(n) #n
#define VAR_GEN(type,prefix,order) type prefix##order
#define VAR_PTR_GEN(type,prefix,order) type##* prefix##order
#define VAR_PTR_GEN_LINE_NUMBER(type,prefix) type##* prefix##__LINE__


class animateQPushButton : public QPushButton
{
Q_OBJECT

public:
    ~animateQPushButton();
    explicit animateQPushButton(QWidget *parent = 0);
    void fadeOut(size_t timeVal);
    void paintEvent(QPaintEvent *event);

private:
    QTimer        *animationTimer;
    QStateMachine *animateStateSet;
    QState        *animateState01;
    QState        *animateState02;
    QState        *animateState03;
    QState        *animateState04;
    QState        *animateState05;
    QState        *animateState06;
    QState        *animateState07;
    QState        *animateState08;
    QState        *animateState09;
    QState        *animateState10;
    QState        *animateState11;

signals:
    void fadeOutFinished(bool);

private slots:
    void closeAnimateAfter();
};

#endif // ANIMATEQPUSHBUTTON_H
