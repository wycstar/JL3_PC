#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    statusLEDImage(new QImage(":/image/LED/LED_GREEN.png")),
    statusLEDScene(new QGraphicsScene)
{
    ui->setupUi(this);
    statusLEDScene->addPixmap(QPixmap::fromImage(*statusLEDImage));
    ui->IMAGE_STATUS_DRIVER_FAULT->setScene(statusLEDScene);
    ui->IMAGE_STATUS_BOLT_ON->setScene(statusLEDScene);
    ui->IMAGE_STATUS_CAN_COMM->setScene(statusLEDScene);
    ui->IMAGE_STATUS_EMER_STOP->setScene(statusLEDScene);
    ui->IMAGE_STATUS_IS_ENABLE->setScene(statusLEDScene);
    ui->IMAGE_STATUS_IS_RUNNING->setScene(statusLEDScene);
    ui->IMAGE_STATUS_POWER_ON->setScene(statusLEDScene);
    ui->IMAGE_STATUS_REACH_LIMIT->setScene(statusLEDScene);
    ui->IMAGE_STATUS_ZERO_POS->setScene(statusLEDScene);

    ui->IMAGE_STATUS_DRIVER_FAULT->show();
    ui->IMAGE_STATUS_BOLT_ON->show();
    ui->IMAGE_STATUS_CAN_COMM->show();
    ui->IMAGE_STATUS_EMER_STOP->show();
    ui->IMAGE_STATUS_IS_ENABLE->show();
    ui->IMAGE_STATUS_IS_RUNNING->show();
    ui->IMAGE_STATUS_POWER_ON->show();
    ui->IMAGE_STATUS_REACH_LIMIT->show();
    ui->IMAGE_STATUS_ZERO_POS->show();

    ui->LINEEDIT_CTRL_POSITION_A->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_POSITION_B->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_POSITION_C->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_POSITION_D->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_POSITION_E->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_VELOCITY_A->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_VELOCITY_B->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_VELOCITY_C->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_VELOCITY_D->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");
    ui->LINEEDIT_CTRL_VELOCITY_E->setStyleSheet("border-radius:10px;border-width:2px;border-style:solid;border-color:#7A9A95");

    ui->Button_CTRL_Stop->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                        QPushButton:hover{background-color:#7A9A95} \
                                      QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->Button_CTRL_VELTEST_CONFIG->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                                  QPushButton:hover{background-color:#7A9A95} \
                                                QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->Button_CTRL_VELTEST_START->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                                 QPushButton:hover{background-color:#7A9A95} \
                                               QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->Button_Gen_AutoTest_Config->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                                  QPushButton:hover{background-color:#7A9A95} \
                                                QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->Button_Gen_AutoTest_Start->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                                 QPushButton:hover{background-color:#7A9A95} \
                                               QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->Button_Gen_AutoTest_Stop->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                                QPushButton:hover{background-color:#7A9A95} \
                                              QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->Button_CTRL_MSGSEND->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                      QPushButton:hover{background-color:#7A9A95} \
                                    QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->Button_Gen_Clear->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                   QPushButton:hover{background-color:#7A9A95} \
                                 QPushButton:pressed{background-color:#7A9A95;border-style:inset}");\
    ui->SEL->setTabText(0,QString("位置速率曲线"));
    ui->SEL->setTabText(1,QString::fromUtf8("速率检测"));
    ui->SEL->setStyleSheet("QTabBar::tab{width:30ex;height:10ex;background-color:#73AFB6;color:white;border:2px groove grey;border-radius:3ex;border-style:outset;margin-left:5px} \
                      QTabBar::tab:hover{width:30ex;height:10ex;background-color:#7A9A95} \
                   QTabBar::tab:selected{width:30ex;height:10ex;background-color:#7A9A95;border-style:inset} \
                  QTabBar::tab:!selected{width:30ex;height:10ex;background-color:#73AFB6} \
                         QTabWidget:pane{border:0px}"); \
    QPixmap plotBack(ui->SEL->width(),ui->SEL->height());
    plotBack.fill(QColor(240,240,240));
    ui->axisPlot->setBackground(plotBack);
    ui->axisPlot->resize(ui->SEL->width(),ui->SEL->height());
    ui->axisPlot->addGraph();
    QVector<double> x(101),y(101);
    for(int i = 0;i <= 100;i++)
    {
        y[i] = (x[i] = i);
    }
    ui->axisPlot->graph(0)->addData(x,y);
}

Dialog::~Dialog()
{
    delete statusLEDScene;
    delete statusLEDImage;
    delete ui;
}
