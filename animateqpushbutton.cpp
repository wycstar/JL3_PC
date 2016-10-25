#include "animateqpushbutton.h"

animateQPushButton::animateQPushButton(QWidget *parent):QPushButton(parent)
{
    animateStateSet = new QStateMachine;
    animationTimer = new QTimer(this);
    animateState01 = new QState(animateStateSet);
    animateState02 = new QState(animateStateSet);
    animateState03 = new QState(animateStateSet);
    animateState04 = new QState(animateStateSet);
    animateState05 = new QState(animateStateSet);
    animateState06 = new QState(animateStateSet);
    animateState07 = new QState(animateStateSet);
    animateState08 = new QState(animateStateSet);
    animateState09 = new QState(animateStateSet);
    animateState10 = new QState(animateStateSet);
    animateState11 = new QState(animateStateSet);
    animationTimer->setInterval(50);
    animationTimer->setSingleShot(false);
    connect(animateStateSet,SIGNAL(finished()),animationTimer,SLOT(stop()             ));
    connect(animateState11 ,SIGNAL(exited()  ),this          ,SLOT(closeAnimateAfter()));
    //connect
    animateState01->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(255) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(255) + ");border-style:outset;color:white}");
    animateState02->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(230) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(230) + ");border-style:outset;color:white}");
    animateState03->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(205) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(205) + ");border-style:outset;color:white}");
    animateState04->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(180) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(180) + ");border-style:outset;color:white}");
    animateState05->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(155) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(155) + ");border-style:outset;color:white}");
    animateState06->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(130) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(130) + ");border-style:outset;color:white}");
    animateState07->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(105) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(105) + ");border-style:outset;color:white}");
    animateState08->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(80 ) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(80 ) + ");border-style:outset;color:white}");
    animateState09->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(55 ) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(55 ) + ");border-style:outset;color:white}");
    animateState10->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(30 ) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(30 ) + ");border-style:outset;color:white}");
    animateState11->assignProperty(this,"styleSheet","QPushButton{background-color:rgb(115,175,182," + QString::number(0  ) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0," + QString::number(0  ) + ");border-style:outset;color:white}");
    animateState01->addTransition(animationTimer,SIGNAL(timeout()),animateState02);
    animateState02->addTransition(animationTimer,SIGNAL(timeout()),animateState03);
    animateState03->addTransition(animationTimer,SIGNAL(timeout()),animateState04);
    animateState04->addTransition(animationTimer,SIGNAL(timeout()),animateState05);
    animateState05->addTransition(animationTimer,SIGNAL(timeout()),animateState06);
    animateState06->addTransition(animationTimer,SIGNAL(timeout()),animateState07);
    animateState07->addTransition(animationTimer,SIGNAL(timeout()),animateState08);
    animateState08->addTransition(animationTimer,SIGNAL(timeout()),animateState09);
    animateState09->addTransition(animationTimer,SIGNAL(timeout()),animateState10);
    animateState10->addTransition(animationTimer,SIGNAL(timeout()),animateState11);
    animateState11->addTransition(animationTimer,SIGNAL(timeout()),animateState01);
    animateStateSet->setInitialState(animateState01);
    this->setStyleSheet("QPushButton{background-color:rgb(115,175,182," + QString::number(250) + ");border-radius:5px;border-width:2px;border-color:rgb(255,0,0,50);border-style:outset;color:white} \
                                        QPushButton:hover{background-color:#7A9A95} \
                                      QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
}

void animateQPushButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
}

animateQPushButton::~animateQPushButton()
{
    delete animationTimer;
    delete animateStateSet;
}

void animateQPushButton::fadeOut(size_t timeVal)
{
    animateStateSet->start();
    animationTimer->start();
}

void animateQPushButton::closeAnimateAfter()
{
    this->hide();
    emit fadeOutFinished(true);
}

