#ifndef EVENTHANDLINGVIEW_H
#define EVENTHANDLINGVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMessageBox>

class EventHandlingView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit EventHandlingView(QWidget *parent = 0);
    ~EventHandlingView();

signals:

public slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    bool drawing;
    QPointF oldLocation;
    QPainterPath* currentPath;
    QPen* currentPen;

};

#endif // EVENTHANDLINGVIEW_H