#include "autotestopdialog.h"
#include "ui_autotestopdialog.h"
#include <QPainter>

autoTestOpDialog::autoTestOpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::autoTestOpDialog)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;

    QPainter painter(this);
    //painter.set
    painter.drawArc(rectangle, startAngle, spanAngle);
}

autoTestOpDialog::~autoTestOpDialog()
{
    delete ui;
}

void autoTestOpDialog::paintEvent(QPaintEvent *event)
{
    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;

    QPainter painter(this);
    //painter.set
    painter.drawArc(rectangle, startAngle, spanAngle);
    QDialog::paintEvent(event);
}
