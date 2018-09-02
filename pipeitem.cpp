#include "pipeitem.h"
#include "mainwindow.h"
#include "setwidthdialog.h"
#include <QMenu>
#include <QString>
#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

PipeItem::PipeItem(const QRectF &rect, int index, int width, QGraphicsItem *parent):
    QGraphicsRectItem (rect, parent), index(index), width(width)
{

}

PipeItem::PipeItem(qreal x, qreal y, qreal width, qreal height, int index, QGraphicsItem *parent):
    QGraphicsRectItem (x, y, width, height, parent), index(index)
{

}

void PipeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if(this->opacity() < 0.5)
            this->setOpacity(1);
        else this->setOpacity(0.01);
        MainWindow::getInstance()->changeOnePipeStatus(this->index);
    }
    else if(event->button() == Qt::RightButton) {
        this->modifyWidth();
    }
}

/**
void PipeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu rightMenu;
    QAction *setWidthAction = rightMenu.addAction(tr("调整宽度"));
    connect(setWidthAction, SIGNAL(triggered()), this, SLOT(modifyWidth()));
    rightMenu.show();


}
*/
void PipeItem::modifyWidth()
{

    SetWidthDialog *setWidthDialog = new SetWidthDialog(this);
    setWidthDialog->show();
}

PipeItem::~PipeItem()
{

}
