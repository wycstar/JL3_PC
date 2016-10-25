#ifndef QCUSTOMTREEVIEW_H
#define QCUSTOMTREEVIEW_H
#include <QTreeView>
#include <QMouseEvent>
#include <QDebug>
#include <dialog.h>
#include <QMap>
using std::sort;

class QCustomTreeView : public QTreeView
{
public:
    explicit QCustomTreeView(QWidget *parent = 0);
    void setVelLevelSheet();
    void setVelTestData(vtrMsg &msg);
    QVector<vtrMsg> vtrMsgSet;
    float vel[GV::VEL_TEST_SPEC][GV::AXIS_NUM];
    int timeVal[GV::VEL_TEST_SPEC];
    float averageVel[GV::VEL_TEST_SPEC][GV::AXIS_NUM];
    double square[GV::VEL_TEST_SPEC][GV::AXIS_NUM];
    double precision[GV::VEL_TEST_SPEC][GV::AXIS_NUM];
    double smoothness[GV::VEL_TEST_SPEC][GV::AXIS_NUM];
    int totalVtrResultCount;
#if 0
signals:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *ev);
#endif
private:
    QMap<int, QStandardItem *> headerItemMap;
    QMap<int, QMap<int, QStandardItem *>> axisItemMap;
};

#endif // QCUSTOMTREEVIEW_H
