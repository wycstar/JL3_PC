#ifndef AUTOTESTOPDIALOG_H
#define AUTOTESTOPDIALOG_H

#include <QDialog>

namespace Ui {
class autoTestOpDialog;
}

class autoTestOpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit autoTestOpDialog(QWidget *parent = 0);
    ~autoTestOpDialog();
    void paintEvent(QPaintEvent *event);

private:
    Ui::autoTestOpDialog *ui;
};

#endif // AUTOTESTOPDIALOG_H
