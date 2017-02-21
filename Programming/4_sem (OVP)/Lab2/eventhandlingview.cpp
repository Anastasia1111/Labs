#include "eventhandlingview.h"
#include <QPointF>
#include <QDebug>

EventHandlingView::EventHandlingView(QWidget *parent) : QGraphicsView(parent)
{

}

void EventHandlingView::mousePressEvent(QMouseEvent *e)
{
    if (!this->scene())
    {
        QMessageBox::warning(this,"Warning!","Create a new file first!");
        return;
    }
}

void EventHandlingView::mouseMoveEvent(QMouseEvent *move)
{

}