#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingdialog.h"
#include "calculate.h"
#include "pipeitem.h"
#include "askrequestdialog.h"



#include <cstdlib>
#include <time.h>

MainWindow* MainWindow::instance = nullptr;

void MainWindow::setAlignment()
{
    ui->numGridLayout->setAlignment(Qt::AlignCenter);
    ui->buttonVLayout->setAlignment(Qt::AlignCenter);
    ui->buttonBox->setAlignment(Qt::AlignCenter);
    ui->displayBox->setAlignment(Qt::AlignCenter);

}

void MainWindow::prepareCompute()
{
    askRequestDialog *askDialog = new askRequestDialog();
    askDialog->show();
    this->hide();

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sizeNum(0), totalNum(0)
{
    ui->setupUi(this);
    ui->nameLabel->setText("<h1 align=\"center\">Microfluidic Chip Simulation</h1>");
    this->setWindowTitle(tr("Microfluidic Chip Simulation"));
    this->setAlignment();
    this->pipesScene = new QGraphicsScene();
    ui->pipesView->setScene(this->pipesScene);
    this->makeMenu();
    memset(this->pipeLength, 0, sizeof(this->pipeLength));
    memset(this->intoPipePos, 0, sizeof(this->intoPipePos));
    memset(this->outPipePos, 0, sizeof(this->outPipePos));

    connect(ui->resetAllButton, SIGNAL(clicked()), this, SLOT(resetAll()));
    connect(ui->randomButton, SIGNAL(clicked()), this, SLOT(initPipeScene()));
    connect(ui->resetInputButton, SIGNAL(clicked()), this, SLOT(resetInputOutput()));
    connect((ui->generateRequestButton), SIGNAL(clicked()), this, SLOT(prepareCompute()));
    srand((unsigned)time(NULL));
    /*
    ui->lcdNum1->setSmallDecimalPoint(true);
    ui->lcdNum2->setSmallDecimalPoint(true);
    ui->lcdNum3->setSmallDecimalPoint(true);
    ui->lcdNum1->setDigitCount(3);
    ui->lcdNum2->setDigitCount(3);
    ui->lcdNum3->setDigitCount(3);
    */
   // SettingDialog *setDialog = new SettingDialog(this);
    //setDialog->show();

    //this->initPipeScene();
}

MainWindow* MainWindow::getInstance()
{
    if(MainWindow::instance == nullptr)
        MainWindow::instance = new MainWindow();
    return MainWindow::instance;
}

void MainWindow::finishCompute(vector<double> resultVector)
{
    ui->lcdNum1->setText(QString::number(resultVector[0], 'g', 3));
    ui->lcdNum2->setText(QString::number(resultVector[1], 'g', 3));
    ui->lcdNum3->setText(QString::number(resultVector[2], 'g', 3));
    this->repaint();
}

void MainWindow::initSettings(int size, int intoPipe1, int intoPipe2, int outPipe1, int outPipe2, int outPipe3)
{
    this->sizeNum = size;
    this->intoPipePos[0] = intoPipe1; this->intoPipePos[1] = intoPipe2;
    this->outPipePos[0] = outPipe1; this->outPipePos[1] = outPipe2; this->outPipePos[2] = outPipe3;
    this->totalNum = 2 * size * (size - 1);
    try {
        this->initPipeScene();
    } catch (const char* msg) {
        qDebug("%s", msg);
    }
}



int MainWindow::addPipeItem(int index)
{
    PipeItem *newPipeItem = new PipeItem(getPipeRect(index), index);
    QPen rectPen = this->getCommonPen();
    newPipeItem->setPen(rectPen);
    if(this->pipeLength[index] == 0)
        newPipeItem->setOpacity(0.01);
    this->pipeItems[index] = newPipeItem;
    this->pipesScene->addItem(newPipeItem);
    return 0;
}

int MainWindow::judgePipeWidth(int index, int width)
{
    int pipeType = this->getPipeType(index);
    const int widthSumLimit = 2800;
    if(width < 20)
        return -2;
    if(pipeType == 0) {
        if(index - 1 >= 0)
            if(pipeItems[index - 1]->width + width > widthSumLimit)
                return -1;
        if(index + 1 < this->totalNum)
            if(pipeItems[index + 1]->width + width > widthSumLimit)
                return -1;
    }
    if(pipeType == 1) {
        if(index - this->sizeNum + 1 >=0)
            if(pipeItems[index - this->sizeNum]->width + width > widthSumLimit)
                return -1;
        if(index + this->sizeNum -1 < this->totalNum)
            if(pipeItems[index + this->sizeNum -1]->width + width > widthSumLimit)
                return -1;
    }
    return 0;
}

void MainWindow::resetAll()
{
    SettingDialog *settingDialog = new SettingDialog(this, 1, intoPipePos[0], intoPipePos[1], outPipePos[0], outPipePos[1], outPipePos[2], this->sizeNum);
    this->hide();
    settingDialog->show();


}

void MainWindow::changeOnePipeStatus(int index)
{
    if(this->pipeLength[index] == 0)
        this->pipeLength[index] = 1600;
    else if(this->pipeLength[index] == 1600)
        this->pipeLength[index] = 0;
    this->calculateFlow();
}


QPen MainWindow::getCommonPen(int visable)
{
    QPen rectPen = QPen();
    if(visable == 1) {
        rectPen.setWidth(1);
        rectPen.setColor(Qt::black);
    }
    else {
        rectPen.setWidth(-1);
        rectPen.setColor((Qt::white));
    }
    return rectPen;
}

int MainWindow::getPipeType(int index)
{
    int limit1 = sizeNum * (sizeNum - 1); int limit2 = 2 * limit1;
    if(0 <= index && index < limit1)
        return 1;
    else if(limit1 <= index && index < limit2)
        return 0;
    else if(limit2 <= index && index < limit2 + 2)
        return 2;
    else if(limit2 + 2 <= index && index < limit2 + 5)
        return 3;
    else return -1;
}

void MainWindow::changePipeWidth(PipeItem* pipeItem, int width)
{
    this->pipesScene->removeItem(pipeItem);
    QRectF rect = pipeItem->rect();
    double w = width, oldW = pipeItem->width;
    pipeItem->width = width;
    int pipeType = this->getPipeType(pipeItem->index);
    if(pipeType == 0) {
        //rect.setHeight(w/100);
        //rect.setY(rect.y() + (w - oldW) / 100);
        rect.setRect(rect.x(), rect.y() + (oldW - w) / 200 * pixUnit, rect.width(), w/100 * pixUnit);
    }
    else if(pipeType == 1) {
        //rect.setWidth(w/100);
        //rect.setX(rect.x() + (w - oldW) / 100);
        rect.setRect(rect.x() + (oldW - w)/200 * pixUnit, rect.y(), w/100 * pixUnit, rect.height());
    }
    pipeItem->setRect(rect);
    this->pipesScene->addItem(pipeItem);
}

QRectF MainWindow::getPipeRect(int index)
{
    int pipeType = getPipeType(index);
    if(pipeType == -1)
        throw "Index is not legal ! Can't get pipeType!";
    double width = 0, height = 0, xpos = 0, ypos = 0;
    if(this->pipeLength[index] > 0) {

    }
        if(pipeType == 0) {
            width = 16 * pixUnit; height = 2 * pixUnit;
            xpos = (index - sizeNum * sizeNum + sizeNum) / sizeNum * 18 * pixUnit + 2 * pixUnit + leftPointx;
            ypos = ((index - sizeNum * sizeNum + sizeNum) % sizeNum ) * 18 * pixUnit  + leftPointy;
        }
        else if(pipeType == 1) {
            width = 2 * pixUnit; height = 16 * pixUnit;
            xpos = (index / (this->sizeNum - 1)) * 18 * pixUnit + leftPointx;
            ypos = (index % (this->sizeNum - 1)) * 18 * pixUnit + 2 * pixUnit + leftPointy;
        }
        else if(pipeType == 2) {
             width = 2 * pixUnit; height = 16 * pixUnit;
             xpos = (intoPipePos[index - this->totalNum]) * 18 * pixUnit + leftPointx;
             ypos = -16 * pixUnit + leftPointy;
        }
        else if(pipeType == 3) {
            width = 2 * pixUnit; height = 16 * pixUnit;
            xpos = (outPipePos[index - this->totalNum - 2]) * 18 * pixUnit + leftPointx;
            ypos = (this->sizeNum - 1) * 18 * pixUnit + 2 * pixUnit + leftPointy;

        }

    QRectF tempRect =  QRectF(xpos, ypos, width, height);
    return tempRect;
}

int MainWindow::initPipeScene()
{

    for(int i = 0; i < totalNum; ++i) {
        this->pipeLength[i] = [] () -> int { int x = rand()%10; if(x < 9) return 1600; return 0; } (); //随机管道
    }
    for(int i = totalNum; i < totalNum + 5; ++i)
        this->pipeLength[i] = 1600;
    this->calculateFlow();
    this->pipesScene->clear();
    for(int i = 0; i < totalNum + 5; ++i)
        this->addPipeItem(i);
    this->drawPorts();
    //ui->pipesView->viewport()->update();
    //ui->pipesView->update();
   // qDebug("刷新按钮按动");

    return 0;
}

void MainWindow::redrawInputOutput(int intoPipe1, int intoPipe2, int outPipe1, int outPipe2, int outPipe3)
{

    this->intoPipePos[0] = intoPipe1; this->intoPipePos[1] = intoPipe2;
    this->outPipePos[0] = outPipe1; this->outPipePos[1] = outPipe2; this->outPipePos[2] = outPipe3;
    this->calculateFlow();
    for(int i = totalNum; i < totalNum + 5; ++i) {
        this->pipesScene->removeItem(this->pipeItems[i]);
        this->addPipeItem(i);
    }

}

void MainWindow::drawPorts()
{
    QPen squarePen = this->getCommonPen();
    double xpos = 0, ypos = 0;

    for(int i = 0; i < sizeNum; ++i)
        for(int j = 0; j < sizeNum; ++j) {
            xpos = i * 18 * pixUnit  + leftPointx;
            ypos = j * 18 * pixUnit  + leftPointy;
            QGraphicsRectItem *tempSquareItem = new QGraphicsRectItem(xpos, ypos, 2 * pixUnit, 2 * pixUnit);
            tempSquareItem->setPen(squarePen);
            this->pipesScene->addItem(tempSquareItem);
        }
}

void MainWindow::resetInputOutput()
{
    SettingDialog *settingDialog = new SettingDialog(this, 2, intoPipePos[0], intoPipePos[1], outPipePos[0], outPipePos[1], outPipePos[2], this->sizeNum);
    this->hide();
    settingDialog->show();
}

int MainWindow::calculateFlow()
{
    vector<double> pipesLength(this->totalNum + 5);
    BackCompute bc;
    for(int i = 0; i < this->totalNum + 5; ++i)
        pipesLength[i] = this->pipeLength[i];
    vector<double> results = bc.caluconspeed(this->sizeNum, pipesLength, intoPipePos[0] , intoPipePos[1], outPipePos[0], outPipePos[1], outPipePos[2]);
    //qDebug("results %lf %lf %lf", results[0], results[1], results[2]);
    ui->lcdNum1->setText(QString::number(results[0], 'g', 3));
    ui->lcdNum2->setText(QString::number(results[1], 'g', 3));
    ui->lcdNum3->setText(QString::number(results[2], 'g', 3));
    //ui->lcdNum1->display(QString::number(results[0], 'g', 3));
    //ui->lcdNum2->display(QString::number(results[1], 'g', 3));
    //ui->lcdNum3->display(QString::number(results[2], 'g', 3));
    this->repaint();
    //this->update();
    /*
    ui->lcdNum1->display(results[0]);
    ui->lcdNum2->display(results[1]);
    ui->lcdNum3->display(results[2]);
    ui->lcdNum1->update();
    ui->lcdNum2->update();
    ui->lcdNum3->update();
    */
    return 0;
}

void MainWindow::makeMenu()
{
    QAction *exitAction = new QAction(tr("退出"), this);
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
   // QMenuBar *mainMenuBar = new QMenuBar();
    //mainMenuBar->clear();
    QMenu *fileMenu = new QMenu(tr("文件"));
    //ßmainMenuBar->addMenu(tr("文件"));
    //this->setMenuBar(mainMenuBar);

    fileMenu->addAction(exitAction);
    //mainMenuBar->addMenu(fileMenu);
    //mainMenuBar->addAction(fileMenu->menuAction());
    //mainMenuBar->show();
    menuBar()->addMenu(fileMenu);
    fileMenu->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}


