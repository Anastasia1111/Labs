#ifndef SPACESCENE_H
#define SPACESCENE_H

#include <QGraphicsScene>
#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "star.h"
#include "planet.h"

class SpaceScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit SpaceScene(QObject *parent = 0);
    ~SpaceScene();

public slots:
    void advance();

private:

};

#endif // SPACESCENE_H