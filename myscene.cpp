#include "myscene.h"
#include <QtGui>

MyScene::MyScene(int newPixle)
{
    m_pixle = newPixle;
    makeGrid();
}

void MyScene::makeGrid()
{
    //Make a grid
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

void MyScene::setImage(QString path)
{
    //set path to Image in resources and set the crusorImage
    m_imagePath = path;
    m_cursorImage = this->addPixmap(m_imagePath);

}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //active at mouse button press
    //if left button then add picture if rigth butten remove picture
    if(event->button() == Qt::LeftButton)
    {
        m_images.append(this->addPixmap(m_imagePath));
        m_images.last()->setPos(m_cursor);
    }
    if(event->button() == Qt::RightButton)
    {
        //pixmap remove
            int index;
            for(index = 0; index < m_images.length(); index++)
            {
                if(m_images[index]->pos() == m_cursor)
                {
                    this->removeItem(m_images[index]);
                    m_images.removeAt(index);
                    break;
                }
            }
    }

}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //active when mouse move
    //it change position of cursorImage where is cursor
    m_cursor.setX(event->scenePos().x());
    m_cursor.setY(event->scenePos().y());
    if((int(m_cursor.x()) % m_pixle) != 0)
        m_cursor.setX(int(m_cursor.x()) - (int(m_cursor.x()) % m_pixle));
    if((int(m_cursor.y()) % m_pixle) != 0)
        m_cursor.setY(int(m_cursor.y()) - (int(m_cursor.y()) % m_pixle));
    //cursor in the midle of picture
    m_cursor.operator -=(QPointF(m_cursorImage->pixmap().width() / 2,m_cursorImage->pixmap().height() / 2));
    //picture cant get out of screen
    if(m_cursor.x()<0)
        m_cursor.setX(0);
    if(m_cursor.y()<0)
        m_cursor.setY(0);
    if((m_cursor.x())+m_cursorImage->pixmap().width()>800)
        m_cursor.setX(800-m_cursorImage->pixmap().width());
    if((m_cursor.y())+m_cursorImage->pixmap().height()>600)
        m_cursor.setY(600-m_cursorImage->pixmap().height());
    m_cursorImage->setPos(m_cursor);

}
