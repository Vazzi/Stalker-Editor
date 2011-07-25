#include "myscene.h"
#include <QtGui>

MyScene::MyScene()
{
    chessboard();
    m_rectangle = this->addRect(0,0,40,40);
    m_rectangle->setFlag(QGraphicsItem::ItemIsMovable);
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
    this->addPixmap(m_texturePath)->setPos(m_cursor);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    m_cursor.setX(event->scenePos().x());
    m_cursor.setY(event->scenePos().y());
    if((int(m_cursor.x()) % 5) != 0)
        m_cursor.setX(int(m_cursor.x()) - (int(m_cursor.x()) % 5));
    if((int(m_cursor.y()) % 5) != 0)
        m_cursor.setY(int(m_cursor.y()) - (int(m_cursor.y()) % 5));
    m_rectangle->setPos(m_cursor);
}
