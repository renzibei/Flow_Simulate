#ifndef PIPEITEM_H
#define PIPEITEM_H

#include <QObject>
#include <QGraphicsItem>

class PipeItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit PipeItem(const QRectF &rect, int index, int width = 200,QGraphicsItem *parent = nullptr);
    explicit PipeItem(qreal x, qreal y, qreal width, qreal height, int index = -1, QGraphicsItem *parent = nullptr);
    int index;
    int width;
    ~PipeItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
   // void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

protected slots:
    void modifyWidth();
};

#endif // PIPEITEM_H
