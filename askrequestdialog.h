#ifndef ASKREQUESTDIALOG_H
#define ASKREQUESTDIALOG_H

#include <QDialog>

namespace Ui {
class askRequestDialog;
}

class askRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit askRequestDialog(QWidget *parent = nullptr);
    ~askRequestDialog();

private:
    Ui::askRequestDialog *ui;

private slots:
    void getTargetNet();
};

#endif // ASKREQUESTDIALOG_H
