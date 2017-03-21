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
    QRectF* zone_View;
    QRectF* zone_Form;
    QRectF* zone_Info;
    QPointF sStart;
    QPointF cStart;
    QPointF rStart;
    QPointF prevPos;
    QGraphicsItem* Square;
    QGraphicsItem* Circle;
    QGraphicsItem* Rectangle;
    QGraphicsItem* draggedItem;
    QGraphicsTextItem* txtView;
    QGraphicsTextItem* txtForm;
    QGraphicsTextItem* txtInfo;
    QGraphicsItemGroup* group;
};

#endif // DRAGSCENE_H