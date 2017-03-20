#ifndef DRAGSCENE_H
#define DRAGSCENE_H

#include <QGraphicsScene>
#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsItem>

class DragScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DragScene(QObject *parent = 0);
    ~DragScene();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);

private:
    QRectF* Rectangle;
    QRectF* Circle;
    QRectF* Square;
    QPointF prevPos;
    QGraphicsItem* draggedItem;
    QGraphicsItemGroup* group;
};

#endif // DRAGSCENE_H