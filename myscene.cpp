#include "myscene.h"
#include <QtGui>

MyScene::MyScene()
{
    chessboard();
}

void MyScene::chessboard()
{
    QPen gPen(Qt::lightGray);
    for(int i = 5; i < 800; i = i +5)
    {
        this->addLine(i,0,i,600, gPen);
    }
    for(int i = 5; i < 600; i = i +5)
    {
        this->addLine(0,i,800,i,gPen);
    }


}

void MyScene::AddTexture(QString path)
{
    m_texturePath = path;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->addPixmap(m_texturePath)->setPos(event->scenePos());

}
