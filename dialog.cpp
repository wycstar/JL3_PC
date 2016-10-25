#include "dialog.h"
#include "ui_dialog.h"

using namespace std;

QUdpSocket  sendSocket;
QUdpSocket  recvSocket;
QTcpSocket  hocket;
QHostAddress clientAddr;
int			msgCount;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    statusLEDGreenImage(new QImage(":/image/LED/LED_GREEN.png")),
    statusLEDGreenScene(new QGraphicsScene),
    statusLEDRedImage(new QImage(":/image/LED/LED_RED.png")),
    statusLEDRedScene(new QGraphicsScene),
    statusLEDBlueImage(new QImage(":/i mage/LED/LED_BLUE.png")),
    statusLEDBlueScene(new QGraphicsScene),
    velTestResultModel(new QStandardItemModel(this)),
    openAnimation(new QPropertyAnimation(this, "windowOpacity")),
    atoDialog(new autoTestOpDialog(this)),
    runningTime(0.0),
    isVelTestStart(false),
    timer(new QTimer(this)),
    timeTimer(new QTimer(this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setWindowFlags(Qt::WindowCloseButtonHint);
    recvSocket.bind(QHostAddress::Any, 0, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    sendSocket.bind(QHostAddress::Broadcast, PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    clientAddr = QHostAddress("192.1.1.208");
    openAnimation->setDuration(1500);
    openAnimation->setStartValue(0);
    openAnimation->setEndValue(1);
    openAnimation->start();
    statusLEDRedScene  ->addPixmap(QPixmap::fromImage(*statusLEDRedImage  ));
    statusLEDBlueScene ->addPixmap(QPixmap::fromImage(*statusLEDBlueImage ));
    statusLEDGreenScene->addPixmap(QPixmap::fromImage(*statusLEDGreenImage));
    ui->IMAGE_STATUS_DRIVER_FAULT->setScene(statusLEDGreenScene);
    ui->IMAGE_STATUS_BOLT_ON->setScene(statusLEDGreenScene);
    ui->IMAGE_STATUS_CAN_COMM->setScene(statusLEDGreenScene);
    ui->IMAGE_STATUS_EMER_STOP->setScene(statusLEDGreenScene);
    ui->IMAGE_STATUS_IS_ENABLE->setScene(statusLEDGreenScene);
    ui->IMAGE_STATUS_IS_RUNNING->setScene(statusLEDGreenScene);
    ui->IMAGE_STATUS_POWER_ON->setScene(statusLEDGreenScene);
    ui->IMAGE_STATUS_REACH_LIMIT->setScene(statusLEDGreenScene);
    ui->IMAGE_STATUS_ZERO_POS->setScene(statusLEDGreenScene);

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
                                 QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->Button_CTRL_Stop->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                   QPushButton:hover{background-color:#7A9A95} \
                                 QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->TABLE_VEL_TEST_RESULT->setStyleSheet("border:0px;background-color:#f0f0f0;color:#73AFB6;font-size:15px");
    ui->SEL->setTabText(0,QString::fromLocal8Bit("位置速率曲线"));
    ui->SEL->setTabText(1,QString::fromLocal8Bit("速率检测结果"));
    ui->SEL->setStyleSheet("QTabBar::tab{width:30ex;height:10ex;background-color:#73AFB6;color:white;border:2px groove grey;border-radius:3ex;border-style:outset;margin-left:5px} \
                      QTabBar::tab:hover{width:30ex;height:10ex;background-color:#7A9A95} \
                   QTabBar::tab:selected{width:30ex;height:10ex;background-color:#7A9A95;border-style:inset} \
                  QTabBar::tab:!selected{width:30ex;height:10ex;background-color:#73AFB6} \
                         QTabWidget:pane{border:0px}"); \
    velTestResultModel->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("轴编号")));
    velTestResultModel->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("目标速度")));
    velTestResultModel->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("实际速度")));
    velTestResultModel->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("速率精度")));
    velTestResultModel->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("其他标识")));
    QStandardItem *axisAItem = new QStandardItem(QString::fromLocal8Bit("轴A"));
    QStandardItem *axisBItem = new QStandardItem(QString::fromLocal8Bit("轴B"));
    QStandardItem *axisCItem = new QStandardItem(QString::fromLocal8Bit("轴C"));
    QStandardItem *axisDItem = new QStandardItem(QString::fromLocal8Bit("轴D"));
    QStandardItem *axisEItem = new QStandardItem(QString::fromLocal8Bit("轴E"));
    axisAItem->setIcon(QIcon(":/ICON/ARROW_BOLD_RIGHT.png"));
    axisBItem->setIcon(QIcon(":/ICON/ARROW_BOLD_RIGHT.png"));
    axisCItem->setIcon(QIcon(":/ICON/ARROW_BOLD_RIGHT.png"));
    axisDItem->setIcon(QIcon(":/ICON/ARROW_BOLD_RIGHT.png"));
    axisEItem->setIcon(QIcon(":/ICON/ARROW_BOLD_RIGHT.png"));
    velTestResultModel->appendRow(axisAItem);
    velTestResultModel->appendRow(axisBItem);
    velTestResultModel->appendRow(axisCItem);
    velTestResultModel->appendRow(axisDItem);
    velTestResultModel->appendRow(axisEItem);
    ui->TABLE_VEL_TEST_RESULT->setModel(velTestResultModel);
    ui->TABLE_VEL_TEST_RESULT->setFont(QFont("Microsoft YaHei"));
    ui->TABLE_VEL_TEST_RESULT->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TABLE_VEL_TEST_RESULT->setRootIsDecorated(false);

    QPixmap plotBack(ui->SEL->width(),ui->SEL->height());
    plotBack.fill(QColor(240,240,240));
    ui->axisPlot->setBackground(plotBack);
    ui->axisPlot->resize(ui->SEL->width() - 10,ui->SEL->height() - 25);
    ui->axisPlot->addGraph();
    ui->axisPlot->addGraph();
    ui->axisPlot->addGraph();
    ui->axisPlot->addGraph();
    ui->axisPlot->addGraph();
    ui->axisPlot->xAxis->setRange(0,30);
    ui->axisPlot->yAxis->setRange(-153,153);
    ui->axisPlot->xAxis->setLabelFont(QFont("Microsoft YaHei"));
    ui->axisPlot->yAxis->setLabelFont(QFont("Microsoft YaHei"));
    ui->axisPlot->xAxis->setLabel(QString::fromLocal8Bit("时间"));
    ui->axisPlot->yAxis->setLabel(QString::fromLocal8Bit("角度"));
    ui->axisPlot->graph(0)->setPen(QPen(QRgb(0xff)));
    ui->axisPlot->graph(1)->setPen(QPen(QRgb(0xaa)));
    ui->axisPlot->graph(2)->setPen(QPen(QRgb(0xff00)));
    ui->axisPlot->graph(3)->setPen(QPen(QRgb(0xaa00)));
    ui->axisPlot->graph(4)->setPen(QPen(QRgb(0xff0000)));
    ui->TABLE_VEL_TEST_RESULT->resize(ui->SEL->width() - 10,ui->SEL->height() - 25);
    connect(ui->Button_CTRL_MSGSEND, SIGNAL(clicked()), this, SLOT(sendCtrlPack()));
    connect(ui->Button_Gen_Clear,   SIGNAL(clicked()), this, SLOT(sendClearCMD()));
    connect(ui->Button_CTRL_Stop,   SIGNAL(clicked()), this, SLOT(sendPauseCMD()));
    connect(&recvSocket, SIGNAL(readyRead()), this, SLOT(recvTableStatus()));
    connect(ui->Button_Gen_AutoTest_Start, SIGNAL(clicked()), this, SLOT(autoTestStart()));
    connect(ui->Button_Gen_AutoTest_Stop, SIGNAL(clicked()), this, SLOT(sendCtrlType()));
    connect(ui->Button_CTRL_VELTEST_START,SIGNAL(clicked()),this,SLOT(sendVelTestCMD()));
    connect(ui->Button_CTRL_VELTEST_CONFIG,SIGNAL(clicked(bool)),this,SLOT(velTestOp()));
    connect(timer, SIGNAL(timeout()), this, SLOT(autoTestOp()));

    ui->LCD_STATUS_POSITION_A->display(QString::fromLocal8Bit("0.0000"));
    ui->LCD_STATUS_POSITION_B->display(QString::fromLocal8Bit("0.0000"));
    ui->LCD_STATUS_POSITION_C->display(QString::fromLocal8Bit("0.0000"));
    ui->LCD_STATUS_POSITION_D->display(QString::fromLocal8Bit("0.0000"));
    ui->LCD_STATUS_POSITION_E->display(QString::fromLocal8Bit("0.0000"));

    ui->LINEEDIT_CTRL_POSITION_A->setText(QString::number(0));
    ui->LINEEDIT_CTRL_POSITION_B->setText(QString::number(0));
    ui->LINEEDIT_CTRL_POSITION_C->setText(QString::number(0));
    ui->LINEEDIT_CTRL_POSITION_D->setText(QString::number(0));
    ui->LINEEDIT_CTRL_POSITION_E->setText(QString::number(0));

    ui->LINEEDIT_CTRL_VELOCITY_A->setText(QString::number(10));
    ui->LINEEDIT_CTRL_VELOCITY_B->setText(QString::number(10));
    ui->LINEEDIT_CTRL_VELOCITY_C->setText(QString::number(10));
    ui->LINEEDIT_CTRL_VELOCITY_D->setText(QString::number(10));
    ui->LINEEDIT_CTRL_VELOCITY_E->setText(QString::number(10));

    for(QObjectList::const_iterator it = this->children().begin();it != this->children().end();it++)
    {
        if(((*it)->objectName()).startsWith("LCD_STATUS_POSITION_"))
            LCDMap.insert(std::make_pair<QString, QLCDNumber *>((*it)->objectName(),dynamic_cast<QLCDNumber *>(*it)));
    }
    ui->TABLE_VEL_TEST_RESULT->setVelLevelSheet();
}

Dialog::~Dialog()
{
    sendSocket.close();
    recvSocket.close();
    delete statusLEDRedScene;
    delete statusLEDRedImage;
    delete statusLEDBlueScene;
    delete statusLEDBlueImage;
    delete statusLEDGreenScene;
    delete statusLEDGreenImage;
    delete ui;
}

void Dialog::sendCtrlType()
{
    presetTrjDialog *ptDialog = new presetTrjDialog(this);
    ptDialog->exec();
}


void Dialog::velTestOp()
{
    if(isVelTestStart)
    {
        QMessageBox::warning(NULL,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("请先停止速率检测!"),QMessageBox::Ok,QMessageBox::Ok);
        return;
    }
    velTestDialog *vtDialog = new velTestDialog(this);
    vtDialog->openAnimation->setDuration(1000);
    vtDialog->openAnimation->setStartValue(0);
    vtDialog->openAnimation->setEndValue(1);
    vtDialog->openAnimation->start();
    vtDialog->exec();
}

void Dialog::sendVelTestCMD()
{
    if(GV::vtcMsgSet.size() == 0)
    {
        QMessageBox::warning(NULL,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("请先设置速率检测参数!"),QMessageBox::Ok,QMessageBox::Ok);
        return;
    }
    if(ui->Button_CTRL_VELTEST_START->text() == QString::fromLocal8Bit("开始速率检测"))
    {
        vtcMsg tVtcMsg;
        for(QVector<vtcMsg>::iterator it = GV::vtcMsgSet.begin();it != GV::vtcMsgSet.end();it++)
        {
            memset(&tVtcMsg,0,VTCMSG_SIZE);
            tVtcMsg = *it;
            tVtcMsg.msgType = TABLE_VELTEST_REQ_MSG;
            tVtcMsg.msgCount = msgCount++;
            if(it == GV::vtcMsgSet.end() - 1)
               tVtcMsg.isStart = true;
            char *buf = new char[VTCMSG_SIZE];
            memset(buf,0,VTCMSG_SIZE);
            memcpy(buf, &tVtcMsg, VTCMSG_SIZE);
            sendSocket.writeDatagram(buf, VTCMSG_SIZE, clientAddr, PORT);
            delete[] buf;
            buf = NULL;
            Sleep(100);
        }
        ui->TABLE_VEL_TEST_RESULT->setVelLevelSheet();
        ui->Button_CTRL_VELTEST_START->setText(QString::fromLocal8Bit("停止速率检测"));
    }
    else
    {
        ui->Button_CTRL_VELTEST_START->setText(QString::fromLocal8Bit("开始速率检测"));
        char *buf = new char[VTSMSG_SIZE];
        buf[0] = TABLE_VELTEST_STOP_MSG;
        buf[1] = msgCount++;
        sendSocket.writeDatagram(buf, VTCMSG_SIZE, clientAddr, PORT);
        delete[] buf;
        buf = NULL;
        Sleep(100);
        GV::vtcMsgSet.clear();
    }
    isVelTestStart = !isVelTestStart;
    ui->TABLE_VEL_TEST_RESULT->vtrMsgSet.clear();
    ui->TABLE_VEL_TEST_RESULT->totalVtrResultCount = 0;
}

void Dialog::workTimeCount()
{
    ui->Button_Gen_AutoTest_Config->hide();
}

void Dialog::autoTestOp()
{
    static bool isStop = false;
    if(isStop){
        workingStartTime = QDateTime::currentDateTime();
        isStop = false;}
    ctlMsg tCtrlMsg;
    memset(&tCtrlMsg, 0, sizeof(tCtrlMsg));
    tCtrlMsg.tPitchPos = it->pos.a;
    tCtrlMsg.tPitchVel = it->vel.a;
    tCtrlMsg.tDriftPos = it->pos.b;
    tCtrlMsg.tDriftVel = it->vel.b;
    tCtrlMsg.tRollPos  = it->pos.c;
    tCtrlMsg.tRollVel  = it->vel.c;
    tCtrlMsg.gPitchPos = it->pos.d;
    tCtrlMsg.gPitchVel = it->vel.d;
    tCtrlMsg.gDriftPos = it->pos.e;
    tCtrlMsg.gDriftVel = it->vel.e;
    tCtrlMsg.msgCount = msgCount++;
    tCtrlMsg.msgType = 0x81;
    tCtrlMsg.checkSum = checkSum(tCtrlMsg);
    char *buf = new char[sizeof(tCtrlMsg)];
    memcpy(buf, &tCtrlMsg, sizeof(tCtrlMsg));
    sendSocket.writeDatagram(buf, sizeof(tCtrlMsg), clientAddr, PORT);
    it++;
    if (it == action.end()){
        action.reserve(action.size());
        it = action.begin();}
    delete[] buf;
    buf = NULL;
    if(((workingEndTime = QDateTime::currentDateTime()).toTime_t() - workingStartTime.toTime_t()) >= 1800){
        timer->setInterval(3600000);
        isStop = true;}
    else
         timer->setInterval(8000);
}

void Dialog::autoTestStart()
{
    if(tStaMsg.gDrift > 1
            || tStaMsg.gPitch > 1
            || tStaMsg.tDrift > 1
            || tStaMsg.tPitch > 1
            || tStaMsg.tRoll  > 1
            || tStaMsg.gDrift < -1
            || tStaMsg.gPitch < -1
            || tStaMsg.tDrift < -1
            || tStaMsg.tPitch < -1
            || tStaMsg.tRoll  < -1)
    {
        QMessageBox::warning(NULL,"警告","请先运行至零点位置!",QMessageBox::Ok,QMessageBox::Ok);
        return;
    }
    ifstream fp("d:\\action.json");
    string jsonString;
    string line;
    while(getline(fp,line))
    {
        jsonString.append(line + "\n");
    }
    using rapidjson::Document;
    using rapidjson::Value;
    Document doc;
    doc.Parse<0>(jsonString.c_str());
    for(UINT i = 1;i <= doc.MemberCount();i++)
    {
        actionScript tAs;
        stringstream ss;
        ss << i;
        tAs.time = doc[ss.str().c_str()]["time"].GetInt();
        for(int j = 0;j < GV::AXIS_NUM;j++)
        {
            float tPos = static_cast<float>(doc[ss.str().c_str()]["position"][j].GetDouble());
            float tVel = static_cast<float>(doc[ss.str().c_str()]["velocity"][j].GetDouble());
            float tAcc = static_cast<float>(doc[ss.str().c_str()]["acceleration"][j].GetDouble());
            memcpy((float *)&(tAs.pos) + j, &tPos, sizeof(float));
            memcpy((float *)&(tAs.vel) + j, &tVel, sizeof(float));
            memcpy((float *)&(tAs.acc) + j, &tAcc, sizeof(float));
        }
        action.push_back(tAs);
    }
    fp.close();
    timer->start();
    timer->setInterval(8000);
    timeTimer->start();
    timeTimer->setInterval(1000);
    it = action.begin();
    _sleep(1000);
    workingStartTime = QDateTime::currentDateTime();
}

void Dialog::autoTestStop()
{
    timer->stop();
    timeTimer->stop();
    kjLastTime = 0;
}

void Dialog::sendPauseCMD()
{
    genMsg tGenMsg;
    memset(&tGenMsg, 0, sizeof(tGenMsg));
    tGenMsg.msgType = 0xC5;
    tGenMsg.msgCount = msgCount++;
    tGenMsg.command = 0x4;
    tGenMsg.checkSum = checkSum(tGenMsg);
    char *buf = new char[sizeof(tGenMsg)];
    memcpy(buf, &tGenMsg, sizeof(tGenMsg));
    sendSocket.writeDatagram(buf, sizeof(tGenMsg), clientAddr, PORT);
    delete[] buf;
    buf = NULL;
}

void Dialog::sendCtrlPack()
{
    ctlMsg tCtrlMsg;
    char buf[BUF_SIZE];
    memset(&tCtrlMsg, 0, CTLMSG_SIZE);
    memset(buf,       0, BUF_SIZE);
    tCtrlMsg.msgType   = 0x81;
    tCtrlMsg.msgCount  = msgCount++;
    tCtrlMsg.tPitchPos = (ui->LINEEDIT_CTRL_POSITION_A->text()).toFloat();
    tCtrlMsg.tPitchVel = (ui->LINEEDIT_CTRL_VELOCITY_A->text()).toFloat();
    tCtrlMsg.tDriftPos = (ui->LINEEDIT_CTRL_POSITION_B->text()).toFloat();
    tCtrlMsg.tDriftVel = (ui->LINEEDIT_CTRL_VELOCITY_B->text()).toFloat();
    tCtrlMsg.tRollPos  = (ui->LINEEDIT_CTRL_POSITION_C->text()).toFloat();
    tCtrlMsg.tRollVel  = (ui->LINEEDIT_CTRL_VELOCITY_C->text()).toFloat();
    tCtrlMsg.gPitchPos = (ui->LINEEDIT_CTRL_POSITION_D->text()).toFloat();
    tCtrlMsg.gPitchVel = (ui->LINEEDIT_CTRL_VELOCITY_D->text()).toFloat();
    tCtrlMsg.gDriftPos = (ui->LINEEDIT_CTRL_POSITION_E->text()).toFloat();
    tCtrlMsg.gDriftVel = (ui->LINEEDIT_CTRL_VELOCITY_E->text()).toFloat();
    tCtrlMsg.checkSum  = checkSum(tCtrlMsg);
    memcpy(buf, &tCtrlMsg, CTLMSG_SIZE);
    sendSocket.writeDatagram(buf, CTLMSG_SIZE, clientAddr, PORT);
}

void Dialog::sendStartCMD()
{
    genMsg tGenMsg;
    memset(&tGenMsg, 0, sizeof(tGenMsg));
    tGenMsg.msgType = 0xC5;
    tGenMsg.msgCount = msgCount++;
    tGenMsg.command = 0x3;
    tGenMsg.checkSum = checkSum(tGenMsg);

    char *buf = new char[sizeof(tGenMsg)];
    memcpy(buf, &tGenMsg, sizeof(tGenMsg));
    sendSocket.writeDatagram(buf, sizeof(tGenMsg), clientAddr, PORT);
    delete[] buf;
    buf = NULL;
}

void Dialog::sendCloseCMD()
{
    genMsg tGenMsg;
    memset(&tGenMsg, 0, sizeof(tGenMsg));
    tGenMsg.msgType = 0xC5;
    tGenMsg.msgCount = msgCount++;
    tGenMsg.command = 0x2;
    tGenMsg.checkSum = checkSum(tGenMsg);

    char *buf = new char[sizeof(tGenMsg)];
    memcpy(buf, &tGenMsg, sizeof(tGenMsg));
    sendSocket.writeDatagram(buf, sizeof(tGenMsg), clientAddr, PORT);
    delete[] buf;
    buf = NULL;
}

void Dialog::sendClearCMD()
{
    genMsg tGenMsg;
    memset(&tGenMsg, 0, sizeof(tGenMsg));
    tGenMsg.msgType = 0xC5;
    tGenMsg.msgCount = msgCount++;
    tGenMsg.command = 0x1;
    tGenMsg.checkSum = checkSum(tGenMsg);

    char *buf = new char[sizeof(tGenMsg)];
    memcpy(buf, &tGenMsg, sizeof(tGenMsg));
    sendSocket.writeDatagram(buf, sizeof(tGenMsg), clientAddr, PORT);
    delete[] buf;
    buf = NULL;
}

void Dialog::sendResetCMD()
{
    genMsg tGenMsg;
    memset(&tGenMsg, 0, sizeof(tGenMsg));
    tGenMsg.msgType = 0xC5;
    tGenMsg.msgCount = msgCount++;
    tGenMsg.command = 0x5;
    tGenMsg.checkSum = checkSum(tGenMsg);

    char *buf = new char[sizeof(tGenMsg)];
    memcpy(buf, &tGenMsg, sizeof(tGenMsg));
    sendSocket.writeDatagram(buf, sizeof(tGenMsg), clientAddr, PORT);
    delete[] buf;
    buf = NULL;
}

void Dialog::sendCheckCMD()
{
    stcMsg tStcMsg;
    memset(&tStcMsg, 0, sizeof(tStcMsg));
    tStcMsg.msgCount = msgCount++;
    tStcMsg.msgType = 0xC1;
    tStcMsg.command = 0xAA;
    tStcMsg.checkSum = checkSum(tStcMsg);

    char *buf = new char[sizeof(tStcMsg)];
    memcpy(buf, &tStcMsg, sizeof(tStcMsg));
    sendSocket.writeDatagram(buf, sizeof(tStcMsg), clientAddr, PORT);
    delete[] buf;
    buf = NULL;
}

void Dialog::recvTableStatus()
{
    unsigned char buf[BUF_SIZE];
    do
    {
        recvSocket.readDatagram(reinterpret_cast<char *>(buf), BUF_SIZE);
    } while (recvSocket.hasPendingDatagrams());
    if((buf[0] >> 7) & 0x1)
    {
        char pBuf[ACKMSG_SIZE];
        memset(pBuf, 0, ACKMSG_SIZE);
        ackMsg tAckMsg;
        tAckMsg.msgType  = 0x7F;
        tAckMsg.msgCount = buf[1];
        tAckMsg.checkSum = checkSum(tAckMsg);
        memcpy(pBuf, &tAckMsg, ACKMSG_SIZE);
        sendSocket.writeDatagram(pBuf, ACKMSG_SIZE, clientAddr, PORT);
    }
    switch (buf[0])
    {
        case 0xc4:
        {
            ftMsg tFtMsg;
            memcpy(&tFtMsg, buf, sizeof(tFtMsg));
            //qDebug() << buf[2] << buf[3] << buf[10] << buf[11];
            if((((tFtMsg.FaultInfoNormal) & 0xff) >> 0) & 0x1)
                ui->IMAGE_STATUS_DRIVER_FAULT->setScene(statusLEDRedScene);
            if((((tFtMsg.FaultInfoNormal) & 0xff) >> 1) & 0x1)
                ui->IMAGE_STATUS_REACH_LIMIT->setScene(statusLEDRedScene);
            if((((tFtMsg.FaultInfoNormal) & 0xff) >> 2) & 0x1)
                ui->IMAGE_STATUS_BOLT_ON->setScene(statusLEDRedScene);
            if((((tFtMsg.FaultInfoNormal) & 0xff) >> 3) & 0x1)
                ui->IMAGE_STATUS_POWER_ON->setScene(statusLEDRedScene);
            if((((tFtMsg.FaultInfoNormal) & 0xff) >> 4) & 0x1)
                ui->IMAGE_STATUS_EMER_STOP->setScene(statusLEDRedScene);
            if((((tFtMsg.FaultInfoNormal) & 0xff) >> 5) & 0x1)
                 ui->IMAGE_STATUS_IS_ENABLE->setScene(statusLEDRedScene);
            if((((tFtMsg.FaultInfoNormal) & 0xff) >> 6) & 0x1)
                ui->IMAGE_STATUS_ZERO_POS->setScene(statusLEDRedScene);
            if((((tFtMsg.FaultInfoNormal) & 0xff) >> 7) & 0x1)
                ui->IMAGE_STATUS_CAN_COMM->setScene(statusLEDRedScene);
            qDebug() << "start" << tFtMsg.name;
        }
        break;
        case 0xC0:
        {
            stMsg tStMsg;
            memcpy(&tStMsg, buf, STMSG_SIZE);
            switch (tStMsg.stInfo & 0xff)
            {
            case 0xAA:
            {

            }
            break;
            case 0xFF:
            {

            }
            break;
            case 0x0:
            {

            }
            break;
            default:
            {

            }}}
        break;
        case 0x7f:
        {
            ackMsg ack;
            memcpy(&ack, buf, ACKMSG_SIZE);
            if(ack.checkSum != checkSum(ack))
                qDebug() << QString::fromLocal8Bit("确认信息校验位不符合!") << endl;
        }
        break;
        case 0x02:
        {
            memcpy(&tStaMsg, buf, STAMSG_SIZE);
            if(tStaMsg.checkSum != checkSum(tStaMsg))
                qDebug() << "Stauts CheckSum ERROR!" << endl;
            else{
                stringstream displayStr[GV::AXIS_NUM];
                for(int i = 0;i < GV::AXIS_NUM;i++)
                {
                    displayStr[i] << setprecision(4) << setiosflags(ios_base::fixed) << *reinterpret_cast<float *>(buf + 4 + i * sizeof(float));
                    (LCDMap[QString("LCD_STATUS_POSITION_") + QString(static_cast<char>('A' + i))])->display(QString::fromLocal8Bit(displayStr[i].str().c_str()));
                    ui->axisPlot->graph(i)->addData(runningTime,*reinterpret_cast<float *>(buf + 4 + i * sizeof(float)));
                };
                if((runningTime += 0.5) > 30)
                    ui->axisPlot->xAxis->setRange(runningTime - 30,runningTime);
                ui->axisPlot->replot();}
        }
        break;
        case TABLE_VELTEST_RES_MSG:
        {
            memset(&tVtrMsg, 0,   VTRMSG_SIZE);
            memcpy(&tVtrMsg, buf, VTRMSG_SIZE);
            ofstream file("d:/velResult.txt");
            stringstream ss;
            ss << "第" << tVtrMsg.currentNum << "次测试\r\n";
            for(int i = 0;i < 5;i++)
                ss << tVtrMsg.actVel[i] << "    ";
            file << ss.str();
            ui->TABLE_VEL_TEST_RESULT->setVelTestData(tVtrMsg);
        }
        break;
        default:
        {

        }
    }
}

