#ifndef PIPEITEM_H
#define PIPEITEM_H

#include <QObject>
#include <QGraphicsItem>

class PipeItem : public QGraphicsRectItem
{

public:
    explicit PipeItem(const QRectF &rect, int index, QGraphicsItem *parent = nullptr);
    explicit PipeItem(qreal x, qreal y, qreal width, qreal height, int index = -1, QGraphicsItem *parent = nullptr);

    ~PipeItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int index;
};

#endif // PIPEITEM_H
