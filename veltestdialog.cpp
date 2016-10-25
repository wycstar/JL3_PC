#include "veltestdialog.h"
#include "ui_veltestdialog.h"

velTestDialog::velTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::velTestDialog),
    openAnimation(new QPropertyAnimation(this, "windowOpacity")),
    addWidgetNum(4)
{
    ui->setupUi(this);
    connect(ui->BUTTON_VELTEST_CONFIG_ADD,SIGNAL(clicked(bool)),this,SLOT(addVelTestItem()));
    connect(ui->BUTTON_VELTEST_CONFIG_CANCEL,SIGNAL(clicked(bool)),this,SLOT(cancelOp()));
    connect(ui->BUTTON_VELTEST_CONFIG_OK,SIGNAL(clicked(bool)),this,SLOT(okOp()));
    ui->LCD_VELTEST_ORDER_1->display(1);
    ui->LCD_VELTEST_ORDER_2->display(2);
    ui->LCD_VELTEST_ORDER_3->display(3);
    ui->LINEEDIT_CTRL_VEL_1->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_VEL_2->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_VEL_3->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_POS_1->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_POS_2->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_POS_3->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_NUM_1->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_NUM_2->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_NUM_3->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LABEL_VELTEST_ORDER_1->setStyleSheet("color:#7A9A95");
    ui->LABEL_VELTEST_ORDER_2->setStyleSheet("color:#7A9A95");
    ui->LABEL_VELTEST_ORDER_3->setStyleSheet("color:#7A9A95");
    ui->LCD_VELTEST_ORDER_1->setStyleSheet("color:#7A9A95");
    ui->LCD_VELTEST_ORDER_2->setStyleSheet("color:#7A9A95");
    ui->LCD_VELTEST_ORDER_3->setStyleSheet("color:#7A9A95");
    ui->LINEEDIT_CTRL_NUM_1->setText(QString::number(5));
    ui->LINEEDIT_CTRL_NUM_2->setText(QString::number(5));
    ui->LINEEDIT_CTRL_NUM_3->setText(QString::number(5));
    ui->LINEEDIT_CTRL_VEL_1->setText(QString::number(1));
    ui->LINEEDIT_CTRL_VEL_2->setText(QString::number(2));
    ui->LINEEDIT_CTRL_VEL_3->setText(QString::number(5));
    ui->LINEEDIT_CTRL_POS_1->setText(QString::number(30));
    ui->LINEEDIT_CTRL_POS_2->setText(QString::number(60));
    ui->LINEEDIT_CTRL_POS_3->setText(QString::number(150));
    ui->BUTTON_VELTEST_CONFIG_OK->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                           QPushButton:hover{background-color:#7A9A95} \
                                         QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->BUTTON_VELTEST_CONFIG_CANCEL->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                               QPushButton:hover{background-color:#7A9A95} \
                                             QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->BUTTON_VELTEST_CONFIG_ADD->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                            QPushButton:hover{background-color:#7A9A95} \
                                          QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
}

velTestDialog::~velTestDialog()
{
    delete ui;
    delete openAnimation;
}

void velTestDialog::cancelOp()
{
    this->close();
}

void velTestDialog::okOp()
{
#if 0
    for(int i = 1;i < addWidgetNum;i++)
    {
        vtcMsg tempVtcMsg;
        memset(&tempVtcMsg,0,VTCMSG_SIZE);
        for(QObjectList::const_iterator it = this->children().begin();it != this->children().end();it++)
        {
            if(!((*it)->objectName()).compare("LINEEDIT_CTRL_VEL_" + QString::number(i)))
            {
                QString str = reinterpret_cast<QLineEdit *>(*it)->text();
                tempVtcMsg.vel = str.toFloat();
            }
            if(!((*it)->objectName()).compare("LINEEDIT_CTRL_POS_" + QString::number(i)))
            {
                QString str = reinterpret_cast<QLineEdit *>(*it)->text();
                tempVtcMsg.pos = str.toFloat();
            }
            if(!((*it)->objectName()).compare("LINEEDIT_CTRL_NUM_" + QString::number(i)))
            {
                QString str = reinterpret_cast<QLineEdit *>(*it)->text();
                tempVtcMsg.num = str.toFloat();
            }
        }
        GV::vtcMsgSet.push_back(tempVtcMsg);
    }
    for(QVector<vtcMsg>::iterator it = GV::vtcMsgSet.begin();it != GV::vtcMsgSet.end();it++)
    {
        qDebug() << it->num << it->vel << it->pos;
    }
    this->close();
#endif
}

void velTestDialog::addVelTestItem()
{
    QRect originRect = this->geometry();
    static const int blankVal = 45;
    this->setGeometry(QRect(originRect.x(),originRect.y(),originRect.width(),originRect.height() + blankVal));
    ui->BUTTON_VELTEST_CONFIG_OK->setGeometry(QRect(ui->BUTTON_VELTEST_CONFIG_OK->geometry().x(),
                                                    ui->BUTTON_VELTEST_CONFIG_OK->geometry().y() + blankVal,
                                                    ui->BUTTON_VELTEST_CONFIG_OK->width(),
                                                    ui->BUTTON_VELTEST_CONFIG_OK->height()));
    ui->BUTTON_VELTEST_CONFIG_CANCEL->setGeometry(QRect(ui->BUTTON_VELTEST_CONFIG_CANCEL->geometry().x(),
                                                        ui->BUTTON_VELTEST_CONFIG_CANCEL->geometry().y() + blankVal,
                                                        ui->BUTTON_VELTEST_CONFIG_CANCEL->width(),
                                                        ui->BUTTON_VELTEST_CONFIG_CANCEL->height()));
    QLineEdit  *tempVelLineEdit    = new QLineEdit(this);
    QLineEdit  *tempPosLineEdit    = new QLineEdit(this);
    QLineEdit  *tempNumLineEdit    = new QLineEdit(this);
    QLCDNumber *tempLineOrderLcd   = new QLCDNumber(this);
    QLabel     *tempLineOrderLabel = new QLabel(this);
    QString tempLineOrderLcdObjName   = "LCD_VELTEST_ORDER_" + QString::number(addWidgetNum);
    QString tempVelLineEditObjName    = "LINEEDIT_CTRL_VEL_" + QString::number(addWidgetNum);
    QString tempPosLineEditObjName    = "LINEEDIT_CTRL_POS_" + QString::number(addWidgetNum);
    QString tempNumLineEditObjName    = "LINEEDIT_CTRL_NUM_" + QString::number(addWidgetNum);
    QString tempLineOrderLabelObjName = "LABEL_VELTEST_ORDER_" + QString::number(addWidgetNum++);
    tempVelLineEdit->setObjectName(tempVelLineEditObjName);
    tempPosLineEdit->setObjectName(tempPosLineEditObjName);
    tempNumLineEdit->setObjectName(tempNumLineEditObjName);
    tempLineOrderLcd->setObjectName(tempLineOrderLcdObjName);
    tempLineOrderLabel->setObjectName(tempLineOrderLabelObjName);
    tempLineOrderLabel->setGeometry(QRect(ui->LABEL_VELTEST_ORDER_3->geometry().x(),
                                          ui->LABEL_VELTEST_ORDER_3->geometry().y() + blankVal * (addWidgetNum - 4),
                                          ui->LABEL_VELTEST_ORDER_3->width(),
                                          ui->LABEL_VELTEST_ORDER_3->height()));
    tempLineOrderLcd->setGeometry(QRect(ui->LCD_VELTEST_ORDER_3->geometry().x(),
                                        ui->LCD_VELTEST_ORDER_3->geometry().y() + blankVal * (addWidgetNum - 4),
                                        ui->LCD_VELTEST_ORDER_3->width(),
                                        ui->LCD_VELTEST_ORDER_3->height()));
    tempVelLineEdit->setGeometry(QRect(ui->LINEEDIT_CTRL_VEL_3->geometry().x(),
                                       ui->LINEEDIT_CTRL_VEL_3->geometry().y() + blankVal * (addWidgetNum - 4),
                                       ui->LINEEDIT_CTRL_VEL_3->width(),
                                       ui->LINEEDIT_CTRL_VEL_3->height()));
    tempPosLineEdit->setGeometry(QRect(ui->LINEEDIT_CTRL_POS_3->geometry().x(),
                                       ui->LINEEDIT_CTRL_POS_3->geometry().y() + blankVal * (addWidgetNum - 4),
                                       ui->LINEEDIT_CTRL_POS_3->width(),
                                       ui->LINEEDIT_CTRL_POS_3->height()));
    tempNumLineEdit->setGeometry(QRect(ui->LINEEDIT_CTRL_NUM_3->geometry().x(),
                                       ui->LINEEDIT_CTRL_NUM_3->geometry().y() + blankVal * (addWidgetNum - 4),
                                       ui->LINEEDIT_CTRL_NUM_3->width(),
                                       ui->LINEEDIT_CTRL_NUM_3->height()));
    tempVelLineEdit->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    tempPosLineEdit->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    tempNumLineEdit->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    tempLineOrderLcd->setSegmentStyle(QLCDNumber::Flat);
    tempLineOrderLcd->setFrameStyle(QLCDNumber::NoFrame);
    tempLineOrderLcd->setStyleSheet("color:#7A9A95");
    tempLineOrderLcd->setDigitCount(2);
    tempLineOrderLcd->setSmallDecimalPoint(false);
    tempLineOrderLcd->display(addWidgetNum - 1);
    tempLineOrderLabel->setStyleSheet("color:#7A9A95");
    tempLineOrderLabel->setText(":");
    QFont ft;
    ft.setPointSize(20);
    ft.setFamily("Microsoft YaHei");
    tempLineOrderLabel->setFont(ft);
    tempVelLineEdit->setText(QString::number(0));
    tempPosLineEdit->setText(QString::number(0));
    tempNumLineEdit->setText(QString::number(5));
    tempVelLineEdit->show();
    tempPosLineEdit->show();
    tempNumLineEdit->show();
    tempLineOrderLcd->show();
    tempLineOrderLabel->show();
}
