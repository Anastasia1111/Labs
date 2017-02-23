#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();
    void setPenColor(QColor color);
    QColor getPenColor();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void setPenWidth(int width);

private:
    QPointF oldLocation; // Координаты предыдущей точки
    QPen* currentPen;
    QColor penColor;
    int penWidth;
};

#endif // PAINTSCENE_H