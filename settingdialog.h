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
    /**
     * @brief SettingDialog
     * @param parent
     * @param mode 构造模式, 0代表初始化模式，1代表全部重新调整模式,2代表只调整出入口模式
     * @param input1
     * @param input2
     * @param output1
     * @param output2
     * @param output3
     * @param size
     */
    explicit SettingDialog(QWidget *parent = nullptr, int mode = 0, int input1 = 0, int input2 = 1, int output1 = 0,
                           int output2 = 1, int output3 = 2, int size = 8);
    ~SettingDialog();

private:
    Ui::SettingDialog *ui;
    void fillComboBox(int input1, int input2, int output1,
                      int output2, int output3, int size);
    void makeMenu();
    int dialogMode;
protected slots:
    void cancelSlot();
    void acceptSlot();
    void sizeNumChanged(int index);
};

#endif // SETTINGDIALOG_H
