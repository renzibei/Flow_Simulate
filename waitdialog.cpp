#include "waitdialog.h"
#include "ui_waitdialog.h"
#include "computethread.h"
#include "mainwindow.h"

WaitDialog::WaitDialog(vector<double> target, QWidget *parent) :
    QDialog(parent),ui(new Ui::WaitDialog),threadNum(QThread::idealThreadCount())
{
    ui->setupUi(this);
    ui->waitLabel->setText("<h1>请稍等</h1>");
    this->targetVector = target;
    this->computeFlow();
}

void WaitDialog::computeFlow()
{

    ComputeThread *threads[128];
    for(int i = 0; i < threadNum; ++i) {
        threads[i] = new ComputeThread(this->targetVector, MainWindow::getInstance()->intoPipePos[0], MainWindow::getInstance()->intoPipePos[1],
                                    MainWindow::getInstance()->outPipePos[0], MainWindow::getInstance()->outPipePos[1], MainWindow::getInstance()->outPipePos[2], MainWindow::getInstance()->sizeNum);
    }
    for(int i = 0; i < threadNum; ++i) {
        connect(threads[i], SIGNAL(finished()), this, SLOT(completeOne()));
    }
}

void WaitDialog::completeOne()
{
    this->finishCount++;
    if(this->finishCount == threadNum) {
        this->close();
       // MainWindow::getInstance()->finishCompute();
    }
}

WaitDialog::~WaitDialog()
{
    delete ui;
}
