#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "pipeitem.h"
#include <vector>

using std::vector;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* getInstance();
    void initSettings(int size, int intoPipe1, int intoPipe2, int outPipe1, int outPipe2, int outPipe3);
    void redrawInputOutput(int intoPipe1, int intoPipe2, int outPipe1, int outPipe2, int outPipe3);
    void changeOnePipeStatus(int index);

    int intoPipePos[2];
    int outPipePos[3];
    int sizeNum = 8;
    void finishCompute(vector<double> resultVector);

public slots:
    int calculateFlow();
    /**
     * @brief judgePipeWidth 判断序号为index的Pipe能否将宽度调整为width
     * @param index
     * @param width
     * @return 若宽度过大，返回-1，过小则返回-2， 可以则返回0
     */
    int judgePipeWidth(int index, int width);
    void changePipeWidth(PipeItem* pipeItem, int width);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *pipesScene;
    static MainWindow* instance;
    const int leftPointx = 0, leftPointy = 15;
    const double pixUnit = 1.5;

    int totalNum = 112; //管道总数(不加5根)

    int pipeLength[200];
    PipeItem *pipeItems[200];



    void setAlignment();

    /**
     * @brief addPipeItem 向场景中加入管道
     * @param index 管道编号
     * @return 成功返回0，错误返回-1
     */
    int addPipeItem(int index);

    /**
     * @brief getPipeType
     * 获取管道类型（横竖）
     * @param index 管道编号
     * @return 横为0，竖为1，入口管道为2，出口管道为3，错误返回-1
     */
    int getPipeType(int index);

    /**
     * @brief initPipeScene
     * @return 如果成功画完scene则返回0， 否则返回-1
     */

    void drawPorts();
    /**
     * @brief getCommonPen
     * @param visable 是否可见，1为可见， 0不可见
     * @return
     */
    QPen getCommonPen(int visable = 1);
    QRectF getPipeRect(int index);

    void makeMenu();


private slots:
    void resetAll();
    int initPipeScene();
    void resetInputOutput();
    void prepareCompute();

};

#endif // MAINWINDOW_H
