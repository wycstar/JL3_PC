#ifndef DIALOG_H
#define DIALOG_H

#include "global.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public:
    vtrMsg      tVtrMsg;
    staMsg      tStaMsg;

private slots:
    void sendCtrlPack();
    void sendClearCMD();
    void sendCloseCMD();
    void sendStartCMD();
    void sendResetCMD();
    void sendCheckCMD();
    void sendPauseCMD();
    void recvTableStatus();
    void autoTestStart();
    void autoTestStop();
    void autoTestOp();
    void workTimeCount();
    void sendVelTestCMD();
    void velTestOp();
    void sendCtrlType();

private:
    Ui::Dialog *ui;
     QImage *statusLEDGreenImage;
     QGraphicsScene *statusLEDGreenScene;
     QImage *statusLEDRedImage;
     QGraphicsScene *statusLEDRedScene;
     QImage *statusLEDBlueImage;
     QGraphicsScene *statusLEDBlueScene;
     QStandardItemModel *velTestResultModel;
     QPropertyAnimation *openAnimation;
     bool isVelTestStart;
     QDateTime workingStartTime;
     QDateTime workingEndTime;
     QDateTime restStartTime;
     QDateTime restEndTime;
     int kjLastTime;
     std::vector<actionScript> action;
     std::vector<actionScript>::iterator it;
     float pos[GV::AXIS_NUM];
     float vel[GV::AXIS_NUM];
     QTimer		  *timer;
     QTimer		  *timeTimer;
     autoTestOpDialog *atoDialog;
     float runningTime;
     std::map<QString, QLCDNumber *> LCDMap;
};

#endif // DIALOG_H
