#include "pipeitem.h"
#include "mainwindow.h"

PipeItem::PipeItem(const QRectF &rect, int index, QGraphicsItem *parent):
    QGraphicsRectItem (rect, parent), index(index)
{

}

PipeItem::PipeItem(qreal x, qreal y, qreal width, qreal height, int index, QGraphicsItem *parent):
    QGraphicsRectItem (x, y, width, height, parent), index(index)
{

}

void PipeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->opacity() < 0.5)
        this->setOpacity(1);
    else this->setOpacity(0.01);
    MainWindow::getInstance()->changeOnePipeStatus(this->index);
}

PipeItem::~PipeItem()
{

}
