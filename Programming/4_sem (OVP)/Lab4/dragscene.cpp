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
    QFont wowfont("Times", 10, QFont::Bold);
    txtView = new QGraphicsTextItem;
    txtForm = new QGraphicsTextItem;
    txtInfo = new QGraphicsTextItem;
    txtView->setFont(wowfont);
    txtView->setPos(120,475);
    txtView->setPlainText("Вид");
    this->addItem(txtView);
    group->addToGroup(txtView);
    txtForm->setFont(wowfont);
    txtForm->setPos(385,475);
    txtForm->setPlainText("Форма");
    this->addItem(txtForm);
    group->addToGroup(txtForm);
    txtInfo->setFont(wowfont);
    txtInfo->setPos(610,475);
    this->addItem(txtInfo);
    txtInfo->setPlainText("     Информация     ");
    group->addToGroup(txtInfo);

    QPainterPath rect;
    rect.addRect(QRectF(0,0,150,50));
    Circle = this->addEllipse(QRectF(0,0,100,100),QPen(Qt::red),QBrush(Qt::red));
    Circle->setPos(220,10);
    Square = this->addRect(QRectF(0,0,100,100),QPen(Qt::blue),QBrush(Qt::blue));
    Square->setPos(380,10);
    Rectangle = this->addPath(rect,QPen(Qt::yellow),QBrush(Qt::yellow));
    Rectangle->setPos(10,10);
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
    draggedItem = NULL;

    if(zone_Form->contains(Square->scenePos())){
        Square->setPos(Circle->scenePos());
        Circle->setPos(e->scenePos()-prevPos);
    } else {
        if(zone_Form->contains(Circle->scenePos())){
            Circle->setPos(Square->scenePos());
            Square->setPos(e->scenePos()-prevPos);
        }
    }
}

void DragScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton){
        if (draggedItem!=NULL && draggedItem->group()==NULL){
            draggedItem->setPos(e->scenePos()-prevPos);
        }
    }
    if(zone_View->contains(Square->scenePos())){
        txtInfo->setPlainText("   Синий квадрат    ");
    } else {
        if(zone_View->contains(Circle->scenePos())){
            txtInfo->setPlainText("    Красный круг    ");
        } else {
            if(zone_View->contains(Rectangle->scenePos())){
                txtInfo->setPlainText("Желтый прямоугольник");
            } else {
                txtInfo->setPlainText("     Информация     ");
            }
        }
    }
}
