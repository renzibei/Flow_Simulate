#include "setwidthdialog.h"
#include "ui_setwidthdialog.h"
#include "mainwindow.h"
#include <QMessageBox>

SetWidthDialog::SetWidthDialog(PipeItem * pipeItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetWidthDialog),
    pipe(pipeItem)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(pipeItem->width));
    ui->lineEdit->setValidator(new QIntValidator(20, 4000, this));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(okButtonPressed()));
}

void SetWidthDialog::okButtonPressed()
{
    int width = ui->lineEdit->text().toInt();
    int judgeStatus = MainWindow::getInstance()->judgePipeWidth(this->pipe->index, width);
    if(judgeStatus == -1)
        QMessageBox::information(this, tr("宽度超出范围"), tr("相邻管道之间间距不能小于200um"));
    else if (judgeStatus == -2)
        QMessageBox::information(this, tr("宽度过小"), tr("管道宽度不能小于20um"));
    else if(judgeStatus == 0) {
        MainWindow::getInstance()->changePipeWidth(this->pipe, width);
        this->close();
    }
}

SetWidthDialog::~SetWidthDialog()
{
    delete ui;
}
