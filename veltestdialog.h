#ifndef VELTESTDIALOG_H
#define VELTESTDIALOG_H

#include "global.h"

namespace Ui {
class velTestDialog;
}

class velTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit velTestDialog(QWidget *parent = 0);
    ~velTestDialog();

private:
    Ui::velTestDialog *ui;
    int addWidgetNum;

public:
    QPropertyAnimation *openAnimation;

private slots:
    void addVelTestItem();
    void cancelOp();
    void okOp();
};

#endif // VELTESTDIALOG_H
