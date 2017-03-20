#include "dragscene.h"
#include <QDebug>
#include <QLabel>

DragScene::DragScene(QObject *parent) : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::white);
    Rectangle = new QRectF(10,10,200,100);
    Circle = new QRectF(220,10,150,150);
    Square = new QRectF(380,10,150,150);
    this->addEllipse(*Circle,QPen(Qt::red),QBrush(Qt::red));
    this->addRect(*Square,QPen(Qt::blue),QBrush(Qt::blue));
    this->addRect(*Rectangle,QPen(Qt::yellow),QBrush(Qt::yellow));

    group = new QGraphicsItemGroup(this->addRect(0,400,800,200));
    group->addToGroup(this->addRect(0,400,266,200));
    group->addToGroup(this->addRect(266,400,268,200));
    group->addToGroup(this->addRect(534,400,266,200));
    QGraphicsTextItem *io1 = new QGraphicsTextItem;
    QGraphicsTextItem *io2 = new QGraphicsTextItem;
    QGraphicsTextItem *io3 = new QGraphicsTextItem;
    io1->setPos(120,475);
    io1->setPlainText("Вид");
    this->addItem(io1);
    group->addToGroup(io1);
    io2->setPos(385,475);
    io2->setPlainText("Форма");
    this->addItem(io2);
    group->addToGroup(io2);
    io3->setPos(640,475);
    this->addItem(io3);
    io3->setPlainText("Информация");
    group->addToGroup(io3);
}

DragScene::~DragScene()
{
    delete Rectangle;
    delete Circle;
    delete Square;
}

void DragScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() == Qt::LeftButton){
        draggedItem = this->itemAt(e->scenePos(),QTransform());
        if (draggedItem!=0 && draggedItem->group()==0){
            qDebug() << e->scenePos().y();
            prevPos = e->scenePos() - draggedItem->pos();
        }
    }
}

void DragScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    //
}

void DragScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton){
        if (draggedItem!=0 && draggedItem->group()==0){
            draggedItem->setPos(e->scenePos()-prevPos);
        }
    }
}