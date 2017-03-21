#include "dragscene.h"
#include <QDebug>
#include <QLabel>

DragScene::DragScene(QObject *parent) : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::white);

    zone_View = new QRectF(0,400,266,200);
    zone_Form = new QRectF(266,400,268,200);
    zone_Info = new QRectF(534,400,266,200);
    group = new QGraphicsItemGroup(this->addRect(0,400,800,200));
    group->addToGroup(this->addRect(*zone_View));
    group->addToGroup(this->addRect(*zone_Form));
    group->addToGroup(this->addRect(*zone_Info));
    txtView = new QGraphicsTextItem;
    txtForm = new QGraphicsTextItem;
    txtInfo = new QGraphicsTextItem;
    txtView->setPos(120,475);
    txtView->setPlainText("Вид");
    this->addItem(txtView);
    group->addToGroup(txtView);
    txtForm->setPos(385,475);
    txtForm->setPlainText("Форма");
    this->addItem(txtForm);
    group->addToGroup(txtForm);
    txtInfo->setPos(610,475);
    this->addItem(txtInfo);
    txtInfo->setPlainText("     Информация     ");
    group->addToGroup(txtInfo);

    QPainterPath rect;
    rect.addRect(QRectF(10,10,200,100));
    Circle = this->addEllipse(QRectF(220,10,150,150),QPen(Qt::red),QBrush(Qt::red));
    cStart = QPointF(220,10);
    Square = this->addRect(QRectF(380,10,150,150),QPen(Qt::blue),QBrush(Qt::blue));
    sStart = QPointF(380,10);
    Rectangle = this->addPath(rect,QPen(Qt::yellow),QBrush(Qt::yellow));
    rStart = QPointF(10,10);
}

DragScene::~DragScene()
{
    delete zone_View;
    delete zone_Form;
    delete zone_Info;
    delete Square;
    delete Circle;
    delete Rectangle;
    delete group;
}

void DragScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() == Qt::LeftButton){
        draggedItem = this->itemAt(e->scenePos(),QTransform());
        if (draggedItem!=NULL && draggedItem->group()==NULL){
            prevPos = e->scenePos() - draggedItem->scenePos();
        }
    }
}

void DragScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if (draggedItem!=NULL){
        if(zone_Form->contains(e->scenePos())){
            if(draggedItem==Square){
                Square->setPos(Circle->scenePos()+cStart-sStart);
                Circle->setPos(e->scenePos()-cStart-prevPos+sStart);
            } else {
                if(draggedItem==Circle){
                    Circle->setPos(Square->scenePos()+sStart-cStart);
                    Square->setPos(e->scenePos()-sStart-prevPos+cStart);
                }
            }
        }
        draggedItem = NULL;
    }
}

void DragScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton){
        if (draggedItem!=NULL && draggedItem->group()==NULL){
            draggedItem->setPos(e->scenePos()-prevPos);
        }
    }
    if(zone_View->contains(Square->scenePos()+sStart)){
        txtInfo->setPlainText("   Синий квадрат    ");
    } else {
        if(zone_View->contains(Circle->scenePos()+cStart)){
            txtInfo->setPlainText("    Красный круг    ");
        } else {
            if(zone_View->contains(Rectangle->scenePos()+rStart)){
                txtInfo->setPlainText("Желтый прямоугольник");
            } else {
                txtInfo->setPlainText("     Информация     ");
            }
        }
    }
}