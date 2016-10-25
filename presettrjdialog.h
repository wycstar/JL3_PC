#ifndef PRESETTRJDIALOG_H
#define PRESETTRJDIALOG_H

#include <QDialog>
#include <global.h>
#include <QRadioButton>
#include <QGroupBox>

namespace Ui {
class presetTrjDialog;
}

class presetTrjDialog : public QDialog
{
    Q_OBJECT

public:
    explicit presetTrjDialog(QWidget *parent = 0);
    ~presetTrjDialog();

private slots:
    void sendTrj();
    void sendCancel();

private:
    Ui::presetTrjDialog *ui;
    std::map<int, QRadioButton *> radioMap;
    std::map<int, QRadioButton *> chMap;
    QGroupBox *gb;
};

#endif // PRESETTRJDIALOG_H
