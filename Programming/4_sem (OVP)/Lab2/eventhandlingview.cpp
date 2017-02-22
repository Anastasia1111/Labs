#include "eventhandlingview.h"
#include <QPointF>
#include <QDebug>

EventHandlingView::EventHandlingView(QWidget *parent) : QGraphicsView(parent)
{
    currentPen = new QPen(QColor("black"));
}

EventHandlingView::~EventHandlingView()
{
    delete currentPen;
}

/*void EventHandlingView::mousePressEvent(QMouseEvent *e)
{
    if (!this->scene())
    {
        QMessageBox::warning(this,"Warning!","Create a new file first!");
        return;
    }
    if (e->button() == Qt::LeftButton){
        QPoint localPoint = this->mapFromGlobal(QCursor::pos());
        oldLocation = localPoint;
    }
}

void EventHandlingView::mouseReleaseEvent(QMouseEvent *e)
{

}

void EventHandlingView::mouseMoveEvent(QMouseEvent *e)
{
    QPainterPath currPath(oldLocation);
    QPoint localPoint = this->mapFromGlobal(QCursor::pos());
    currPath.lineTo(localPoint);
    this->scene()->addPath(currPath, *currentPen);
    oldLocation = localPoint;
    this->update();
}*/

