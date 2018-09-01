#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>


SettingDialog::SettingDialog(QWidget *parent, int mode, int input1, int input2, int output1,
                             int output2, int output3, int size) :
    QDialog(parent),
    ui(new Ui::SettingDialog),
    dialogMode(mode)
{
    ui->setupUi(this);
    ui->dialogNameLabel->setText("<h3>请设置参数</h3>");
    if(mode == 2) {
        ui->verticalLayout->removeItem(ui->sizeHLayout);
        ui->sizeComboBox->setVisible(false);
        ui->sizeNumLabel->setVisible(false);
    }
    this->fillComboBox(input1, input2, output1, output2, output3, size);
    ui->buttonBox->addButton(tr("确认"),QDialogButtonBox::AcceptRole);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptSlot()));
    if(mode != 0) {
        ui->buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
        connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(cancelSlot()));
    }

   // MainWindow *mainwindow = new MainWindow();
   // this->setParent(mainwindow);
}

void SettingDialog::cancelSlot()
{
    this->close();
    MainWindow::getInstance()->show();
}

void SettingDialog::acceptSlot()
{
    if(ui->input1Combo->currentIndex() == ui->input2Combo->currentIndex())
        QMessageBox::information(this, tr("输入管道不能位于同一列"), tr("输入管道不能位于同一列"));
    else {
        int num1 = ui->output1Combo->currentIndex(), num2 = ui->output2Combo->currentIndex(), num3 = ui->output3Combo->currentIndex();
        if(num1 == num2 || num2 == num3 || num1 == num3)
            QMessageBox::information(this, tr("输出管道不能位于同一列"), tr("输出管道不能位于同一列"));
        else {
            if(this->dialogMode == 0 || this->dialogMode == 1)
                MainWindow::getInstance()->initSettings(ui->sizeComboBox->currentIndex() + 5, ui->input1Combo->currentIndex() ,
                                                       ui->input2Combo->currentIndex(), ui->output1Combo->currentIndex(),
                                                        ui->output2Combo->currentIndex(), ui->output3Combo->currentIndex());
            else if(this->dialogMode == 2) {
                MainWindow::getInstance()->redrawInputOutput(ui->input1Combo->currentIndex() ,
                                                             ui->input2Combo->currentIndex(), ui->output1Combo->currentIndex(),
                                                              ui->output2Combo->currentIndex(), ui->output3Combo->currentIndex());
            }
            this->close();
            MainWindow::getInstance()->show();
        }
    }
}

void SettingDialog::fillComboBox(int input1, int input2, int output1,
                                 int output2, int output3, int size)
{
    QStringList sizeTexts = {"5", "6", "7", "8"};
    ui->sizeComboBox->addItems(sizeTexts);
    ui->sizeComboBox->setCurrentIndex(size - 5);
    QStringList colTexts = {"1", "2", "3", "4", "5", "6", "7", "8"};
    this->sizeNumChanged(size - 5);
    //ui->input1Combo->addItems(colTexts);
    ui->input1Combo->setCurrentIndex(input1);
   // ui->input2Combo->addItems(colTexts);
    ui->input2Combo->setCurrentIndex(input2);
   // ui->output1Combo->addItems(colTexts);
   // ui->output2Combo->addItems(colTexts);
    ui->output1Combo->setCurrentIndex(output1);
    ui->output2Combo->setCurrentIndex(output2);
  //  ui->output3Combo->addItems(colTexts);
    ui->output3Combo->setCurrentIndex(output3);
    connect(ui->sizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sizeNumChanged(int)));
}

void SettingDialog::sizeNumChanged(int index)
{
    QStringList colTexts = {"1", "2", "3", "4", "5", "6", "7", "8"};
    ui->input1Combo->clear();
    ui->input2Combo->clear();
    ui->output1Combo->clear();
    ui->output2Combo->clear();
    ui->output3Combo->clear();
    for(int i = 0; i < 5 + index; ++i) {
        ui->input1Combo->addItem(colTexts[i]);
        ui->input2Combo->addItem(colTexts[i]);
        ui->output1Combo->addItem(colTexts[i]);
        ui->output2Combo->addItem(colTexts[i]);
        ui->output3Combo->addItem(colTexts[i]);
    }
    ui->input2Combo->setCurrentIndex(1);
    ui->output2Combo->setCurrentIndex(1);
    ui->output3Combo->setCurrentIndex(2);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}
