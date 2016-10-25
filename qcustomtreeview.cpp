#include "qcustomtreeview.h"

QCustomTreeView::QCustomTreeView(QWidget *parent) : QTreeView(parent)
{

}
#if 0
void QCustomTreeView::mousePressEvent(QMouseEvent *ev)
{
     QModelIndex index = indexAt(QPoint(ev->pos()));
     if (ev->button() == Qt::LeftButton)
     {
         if(!isExpanded(index.sibling(index.row(),0)) && index.parent().row() == -1)
         {
             this->expand(index.sibling(index.row(),0));
             reinterpret_cast<QStandardItemModel *>(this->model())->itemFromIndex(index.sibling(index.row(),0))->setIcon(QIcon(":/ICON/ARROW_BOLD_DOWN.png"));
         }
         else if(isExpanded(index.sibling(index.row(),0)) && index.parent().row() == -1)
         {
             this->collapse(index.sibling(index.row(),0));
             reinterpret_cast<QStandardItemModel *>(this->model())->itemFromIndex(index.sibling(index.row(),0))->setIcon(QIcon(":/ICON/ARROW_BOLD_RIGHT.png"));
         }
     }
}

void QCustomTreeView::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        this->expandAll();
        for(int j = 0;j < GV::AXIS_NUM;j++)
        {
            reinterpret_cast<QStandardItemModel *>(this->model())->item(j,0)->setIcon(QIcon(":/ICON/ARROW_BOLD_DOWN.png"));
        }
    }
}
#endif
void QCustomTreeView::setVelLevelSheet()
{
    for(int i = 0;i < GV::AXIS_NUM;i++)
    {
        int count;
        if((count = reinterpret_cast<QStandardItemModel *>(this->model())->item(i,0)->rowCount()) != 0)
            reinterpret_cast<QStandardItemModel *>(this->model())->item(i,0)->removeRows(0, count);
    }
    float tempVel[8][5] = {
            {1,1,1,3,3},
            {-1,-1,-1,-3,-3},
            {2,2,2,5,5},
            {-2,-2,-2,-5,-5},
            {10,10,10,10,10},
            {-10,-10,-10,-10,-10},
            {20,20,20,20,20},
            {-20,-20,-20,-20,-20}
    };
    int tempTimeVal[8] = {10,10,5,5,1,1,1,1};
    memcpy(vel, tempVel, sizeof(vel));
    memcpy(timeVal, tempTimeVal, sizeof(tempTimeVal));
    for(int i = 0;i < 8;i++)
    {
        vtcMsg msg;
        memset(&msg,0,sizeof(msg));
        for(int j = 0;j < 5;j++)
        {
            msg.acc[i] = 50;
            msg.isTimeVal = true;
            msg.num = 10;
            msg.type.timeVal[j] = timeVal[i];
            msg.vel[j] = vel[i][j];
        }
        GV::vtcMsgSet.push_back(msg);
    }
    for(int j = 0;j < GV::AXIS_NUM;j++)
    {

        for(int i = 0;i < GV::vtcMsgSet.size();i++)
        {
            reinterpret_cast<QStandardItemModel *>(this->model())->item(j,0)->setChild(i,\
                                                                                       new QStandardItem(QString("%1%2%3").\
                                                                                                         arg(QString::fromLocal8Bit("速率档:")).\
                                                                                                         arg(GV::vtcMsgSet[i].vel[j]).\
                                                                                                         arg(QString::fromLocal8Bit("°/s"))));
            reinterpret_cast<QStandardItemModel *>(this->model())->item(j,0)->child(i)->setIcon(QIcon(":/ICON/ARROW_BOLD_RIGHT.png"));
            headerItemMap.insert(static_cast<int>(GV::vtcMsgSet[i].vel[j]), reinterpret_cast<QStandardItemModel *>(this->model())->item(j,0)->child(i, 0));
        }
        axisItemMap.insert(j,headerItemMap);
        headerItemMap.clear();
    }
    totalVtrResultCount = 0;
    memset(square, 0, sizeof(square));
    memset(precision, 0, sizeof(precision));
    memset(smoothness, 0, sizeof(smoothness));
    vtrMsgSet.clear();
}

void QCustomTreeView::setVelTestData(vtrMsg &msg)
{
    for(int i = 0;i < GV::AXIS_NUM;i++)
    {
        axisItemMap[i][static_cast<int>(msg.targetVel[i])]->setChild(msg.currentNum - 1, 0,\
                                                                  new QStandardItem(QString("%1%2%3").\
                                                                                    arg(QString::fromLocal8Bit("第")).\
                                                                                    arg(msg.currentNum).\
                                                                                    arg(QString::fromLocal8Bit("次测试"))));

        axisItemMap[i][static_cast<int>(msg.targetVel[i])]->setChild(msg.currentNum - 1, 1,\
                                                                  new QStandardItem(QString::number(msg.targetVel[i])));
        axisItemMap[i][static_cast<int>(msg.targetVel[i])]->setChild(msg.currentNum - 1, 2,\
                                                                  new QStandardItem(QString::number(msg.actVel[i])));
    }
    vtrMsgSet.push_back(msg);
#if 1
    if((++totalVtrResultCount) == GV::VEL_TEST_NUM * GV::VEL_TEST_SPEC)
    {
        qDebug() << "setSize:" << vtrMsgSet.size();
        for(int i = 0;i < GV::AXIS_NUM;i++)
        {
            for(int j = 0;j < vtrMsgSet.size();j+=GV::VEL_TEST_NUM)
            {
                float aver = 0.0;
                for(int k = 0;k < GV::VEL_TEST_NUM;k++)
                    aver += vtrMsgSet[j + k].actVel[i];
                aver /= GV::VEL_TEST_NUM;
                averageVel[j / GV::VEL_TEST_NUM][i] = aver;
                for(int k = 0;k < GV::VEL_TEST_NUM;k++)
                    square[j / GV::VEL_TEST_NUM][i] += pow(static_cast<double>(vtrMsgSet[j + k].actVel[i] - aver), 2);
                precision[j][i] = fabs(vel[j][i] - averageVel[j][i]) / vel[j][i];
                smoothness[j][i] = sqrt(square[j][i] / (GV::VEL_TEST_NUM - 1)) / averageVel[j][i];
            }
        }
        for(int i = 0;i < GV::AXIS_NUM;i++)
        {
            for(int j = 0;j < vtrMsgSet.size();j++)
            {

            }
        }
#if 1
        for(int i = 0; i < GV::AXIS_NUM; i++)
        {
            for(int j = 0;j < GV::VEL_TEST_SPEC; j++)
            {
                qDebug() << "aver:" << averageVel[j][i] << vel[j][i] << square[j][i] << precision[j][i] << smoothness[j][i];
            }
        }
#endif
        totalVtrResultCount = 0;
        vtrMsgSet.clear();
    }
    qDebug() << totalVtrResultCount;
#endif
}


