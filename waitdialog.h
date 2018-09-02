#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QDialog>
#include <vector>

using std::vector;

namespace Ui {
class WaitDialog;
}

class WaitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitDialog(vector<double> target, QWidget *parent = nullptr);
    ~WaitDialog();

private:
    Ui::WaitDialog *ui;
    int finishCount = 0;
    void computeFlow();
    vector<double> targetVector;
    const int threadNum = 1;
protected slots:
    void completeOne();
};

#endif // WAITDIALOG_H
