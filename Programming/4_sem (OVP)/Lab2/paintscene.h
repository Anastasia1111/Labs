#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();
    void setPenColor(QColor color);
    void setPenStyle(Qt::PenStyle style);
    QColor getPenColor();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void setPenWidth(int width);
    void undo();
    void redo();
    void clear();

private:
    QPointF oldLocation; // Координаты предыдущей точки
    QPen* currentPen;
    QColor penColor;
    int penWidth;
    QList<QPixmap>* History;
    int historyCounter;
};

#endif // PAINTSCENE_H