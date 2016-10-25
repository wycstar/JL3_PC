#include "presettrjdialog.h"
#include "ui_presettrjdialog.h"

extern QUdpSocket  sendSocket;
extern QUdpSocket  recvSocket;
extern QHostAddress clientAddr;
extern int msgCount;

presetTrjDialog::presetTrjDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::presetTrjDialog)
{
    ui->setupUi(this);
    connect(ui->BUTTON_VELTEST_CONFIG_OK,     SIGNAL(clicked(bool)), this, SLOT(sendTrj()));
    connect(ui->BUTTON_VELTEST_CONFIG_CANCEL, SIGNAL(clicked(bool)), this, SLOT(sendCancel()));
    ui->BUTTON_VELTEST_CONFIG_OK->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                           QPushButton:hover{background-color:#7A9A95} \
                                         QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    ui->BUTTON_VELTEST_CONFIG_CANCEL->setStyleSheet("QPushButton{background-color:#73AFB6;border-radius:5px;border:2px groove grey;border-style:outset;color:white} \
                                               QPushButton:hover{background-color:#7A9A95} \
                                             QPushButton:pressed{background-color:#7A9A95;border-style:inset}");
    for(QObjectList::const_iterator it = this->children().begin();it != this->children().end();it++){
        if(((*it)->objectName()).contains("RADIO_TRJTYPE_A")){
            radioMap.insert(std::make_pair(atoi((*it)->objectName().toStdString().substr(15).c_str()),
                                           reinterpret_cast<QRadioButton *>(*it)));}
        else if(((*it)->objectName()).contains("GROUP_CH")){
            gb = reinterpret_cast<QGroupBox *>(*it);}}
    for(QObjectList::const_iterator it = gb->children().begin();it != gb->children().end();it++){
        chMap.insert(std::make_pair(atoi((*it)->objectName().toStdString().substr(12).c_str()),
                                    reinterpret_cast<QRadioButton *>(*it)));}
}

presetTrjDialog::~presetTrjDialog()
{
    delete ui;
}

void presetTrjDialog::sendTrj()
{
    int trjNum = 0;
    int chNum = 0;
    for(trjNum = 0;trjNum < 14;trjNum++){
        if(radioMap[trjNum]->isChecked())
            break;}
    for(chNum = 0;chNum < 5;chNum++){
        if(chMap[chNum]->isChecked())
            break;}
    wCtlMsg wcMsg;
    memset(&wcMsg, 0xff, WCTLMSG_SIZE);
    UCHAR value = 0xa0 + trjNum;
    wcMsg.msgCount = msgCount++;
    wcMsg.msgType = 0x82;
    memcpy(((UCHAR *)&wcMsg.tPitchWord + chNum), &value, 1);
    wcMsg.checkSum = checkSum(wcMsg);
    unsigned char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);
    memcpy(buf, &wcMsg, WCTLMSG_SIZE);
    for(int i = 0;i < WCTLMSG_SIZE;i++){
       qDebug() << static_cast<unsigned char>(buf[i]);}
    sendSocket.writeDatagram((char *)buf, WCTLMSG_SIZE, clientAddr, PORT);
}

void presetTrjDialog::sendCancel()
{

}
