#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <QDialog>
#include <QImage>
#include <QGraphicsScene>
#include <qcustomplot.h>
#include <QVector>
#include <QPalette>
#include <QVector>
#include "json/json.h"
#include <iostream>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpSocket>
#include <QTimer>
#include <qmessagebox.h>
#include <qtextcodec.h>
#include <qtextstream.h>
#include <qtimer.h>
#include <fstream>
#include <QVector>
#include <QString>
#include <sstream>
#include <iomanip>
#include <vector>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>
#include <veltestdialog.h>
#include <autotestopdialog.h>
#include <presettrjdialog.h>
#include <QDebug>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QString>
#include <map>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

/*指令相关结构体*/
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned int  UINT;

static const int PORT = 10000;
static const int BUF_SIZE = 200;

template <typename T>
inline int checkSum(T &a)
{
    UCHAR sum = 0;
    for(UINT i = 0;i < sizeof(a) - 1;i++)
        sum += *((unsigned char *)&a + i);
    return sum;
}

/*日期时间相关的结构体变量*/
typedef struct
{
    WORD wYear;
    BYTE ucMonth;
    BYTE ucDay;
    BYTE ucHour;
    BYTE ucMinute;
    BYTE ucSecond;
    WORD wMilliSecond;
    WORD wMarcoSecond;
    WORD wType;
}ST_DATETIME;

#pragma pack(1)
typedef struct _tSelfTestCMD
{
    UCHAR msgType;
    UCHAR msgCount;
    UCHAR command;
    UCHAR checkSum;
}stcMsg;
#define STCMSG_SIZE sizeof(stcMsg)

typedef struct _tSelfTestResult
{
    UCHAR msgType;
    UCHAR msgCount;
    WORD  stInfo;
    DWORD stDetail;
    DWORD remain;
    char  name[52];
    UCHAR checkSum;
}stMsg;
#define STMSG_SIZE sizeof(stMsg)

typedef struct _tFaultMsg 
{
    UCHAR msgType;
    UCHAR msgCount;
    WORD  msgClass;
    WORD  statusInfoA;
    WORD  statusInfoB;
    WORD  warnInfo;
    WORD  FaultInfoNormal;
    WORD  FaultInfoEmergency;
    WORD  remain;
    char  name[48];
    UCHAR checkSum;
}ftMsg;
#define FTMSG_SIZE sizeof(ftMsg)

typedef struct _tAckMsg
{
    UCHAR msgType;
    UCHAR msgCount;
    UCHAR serverMsgType;
    UCHAR checkSum;
}ackMsg;
#define ACKMSG_SIZE sizeof(ackMsg)

typedef struct _tGenMsg
{
    UCHAR msgType;
    UCHAR msgCount;
    WORD  command;
    UCHAR remain[12];
    UCHAR checkSum;
}genMsg;
#define GENMSG_SIZE sizeof(genMsg)

typedef struct _tCtlMsg
{
    UCHAR msgType;
    UCHAR msgCount;
    WORD  remain;
    float tPitchPos;
    float tDriftPos;
    float tRollPos;
    float gPitchPos;
    float gDriftPos;
    float tPitchVel;
    float tDriftVel;
    float tRollVel;
    float gPitchVel;
    float gDriftVel;
    UCHAR checkSum;
}ctlMsg;

#define CTLMSG_SIZE sizeof(ctlMsg)

typedef struct _tCtlMsgWord
{
    UCHAR msgType;
    UCHAR msgCount;
    UCHAR tPitchWord;
    UCHAR tDriftWord;
    UCHAR tRollWord;
    UCHAR gPitchWord;
    UCHAR gDriftWord;
    UCHAR checkSum;
}wCtlMsg;

#define WCTLMSG_SIZE sizeof(wCtlMsg)

typedef struct _tStaMsg
{
    UCHAR msgType;
    UCHAR msgCount;
    WORD  remain;
    float tPitch;
    float tDrift;
    float tRoll;
    float gPitch;
    float gDrift;
    UCHAR checkSum;
}staMsg;
#define STAMSG_SIZE sizeof(staMsg)

typedef struct _autoTestStruct
{
	int time;
	struct _ctrlParam{
	float  a;
	float  b;
	float  c;
	float  d;
	float  e;
	}pos,vel,acc;
}actionScript;

/**************************************/
union type
{
    unsigned char data[sizeof(int) * 5];
    float pos[5];
    int   timeVal[5];
};
typedef union type TYPE;
typedef struct _tVelTestCMDMsg
{
    UCHAR msgType;
    UCHAR msgCount;
    TYPE  type;
    float vel[5];
    float num;
    float acc[5];
    bool  isTimeVal;
    bool  isStart;
}vtcMsg;

namespace GV
{
    static const int AXIS_NUM = 5;
    extern QVector<vtcMsg> vtcMsgSet;
    static const int VEL_TEST_NUM  = 10;
    static const int VEL_TEST_SPEC = 8;
}

typedef struct _tVelTestResultMsg
{
    UCHAR msgType;
    UCHAR msgCount;
    float targetVel[GV::AXIS_NUM];
    float actVel[GV::AXIS_NUM];
    int   currentNum;
}vtrMsg;

typedef struct _tVelTestStopMsg
{
    UCHAR msgType;
    UCHAR msgCount;
}vtsMsg;

static const UCHAR TABLE_VELTEST_REQ_MSG = 0xCA;
static const UCHAR TABLE_VELTEST_RES_MSG = 0xCB;
static const UCHAR TABLE_VELTEST_STOP_MSG = 0xCC;
static const int VTCMSG_SIZE = sizeof(vtcMsg);
static const int VTRMSG_SIZE = sizeof(vtrMsg);
static const int VTSMSG_SIZE = sizeof(vtsMsg);
/**************************************/
#pragma pack()
#endif
