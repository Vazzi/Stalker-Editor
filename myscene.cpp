#include "myscene.h"
#include <QtGui>

MyScene::MyScene(int newPixle)
{
    m_pixle = newPixle;
    makeGrid();
    m_rectangle = this->addRect(0,0,40,40);

}

void MyScene::makeGrid()
{
    QPen gPen(Qt::lightGray);
    for(int i = m_pixle ; i < 800; i = i +m_pixle)
    {
        this->addLine(i,0,i,600, gPen);
    }
    for(int i = m_pixle; i < 600; i = i +m_pixle)
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
    if(event->button() == Qt::LeftButton)
        this->addPixmap(m_texturePath)->setPos(m_cursor);
    //if(event->button() == Qt::RightButton)
        //pixmap remove
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_cursor.setX(event->scenePos().x());
    m_cursor.setY(event->scenePos().y());
    if((int(m_cursor.x()) % m_pixle) != 0)
        m_cursor.setX(int(m_cursor.x()) - (int(m_cursor.x()) % m_pixle));
    if((int(m_cursor.y()) % m_pixle) != 0)
        m_cursor.setY(int(m_cursor.y()) - (int(m_cursor.y()) % m_pixle));
    m_cursor.operator -=(QPointF(20,20));
    if(m_cursor.x()<0)
        m_cursor.setX(0);
    if(m_cursor.y()<0)
        m_cursor.setY(0);
    if((m_cursor.x())+40>800)
        m_cursor.setX(800-40);
    if((m_cursor.y())+40>600)
        m_cursor.setY(600-40);
    m_rectangle->setPos(m_cursor);



}
