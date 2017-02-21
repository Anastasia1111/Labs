#include "eventhandlingview.h"
#include <QPointF>
#include <QDebug>

EventHandlingView::EventHandlingView(QWidget *parent) : QGraphicsView(parent),
    drawing(false)
{
    currentPen = new QPen(QColor("black"));
}

EventHandlingView::~EventHandlingView()
{
    delete currentPen;
}

void EventHandlingView::mousePressEvent(QMouseEvent *e)
{
    if (!this->scene())
    {
        QMessageBox::warning(this,"Warning!","Create a new file first!");
        return;
    }
    if (e->button() == Qt::LeftButton){
        drawing = true;
        QPointF pt = mapToScene(e->pos());
        oldLocation = pt;
        currentPath = new QPainterPath(oldLocation);
    }
}

void EventHandlingView::mouseReleaseEvent(QMouseEvent *e)
{
    drawing = false;
    try {
        delete currentPath;
    }
    catch (...) {};
}

void EventHandlingView::mouseMoveEvent(QMouseEvent *e)
{
    QPointF pt = mapToScene(e->pos());
    currentPath->lineTo(pt);
    this->scene()->addPath(*currentPath, *currentPen);
    oldLocation = pt;
    this->update();
}