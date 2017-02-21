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

signals:

public slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *move);

private:

};

#endif // EVENTHANDLINGVIEW_H