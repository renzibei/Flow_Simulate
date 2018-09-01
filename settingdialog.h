#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr, int mode = 0, int input1 = 0, int input2 = 1, int output1 = 0,
                           int output2 = 1, int output3 = 2, int size = 8);
    ~SettingDialog();

private:
    Ui::SettingDialog *ui;
    void fillComboBox(int input1, int input2, int output1,
                      int output2, int output3, int size);
    int dialogMode;
protected slots:
    void cancelSlot();
    void acceptSlot();
    void sizeNumChanged(int index);
};

#endif // SETTINGDIALOG_H
