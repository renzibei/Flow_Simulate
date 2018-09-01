#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>


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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *pipesScene;
    static MainWindow* instance;
    const int leftPointx = 0, leftPointy = 15;
    const double pixUnit = 1.5;
    int sizeNum = 8;
    int totalNum = 112; //管道总数(不加5根)
    int intoPipePos[2];
    int outPipePos[3];
    int pipeLength[200];
    QGraphicsRectItem *pipeItems[200];



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
    QPen getCommonPen();
    QRectF getPipeRect(int index);



private slots:
    void resetAll();
    int initPipeScene();
    void resetInputOutput();
};

#endif // MAINWINDOW_H
