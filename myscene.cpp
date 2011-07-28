#include "myscene.h"
#include <QtGui>


MyScene::MyScene(int newPixle, QString background, QString nonePath)
{
    m_pixle = newPixle;
    m_none = nonePath;
    m_shift = false;
    m_shiftLeftCorner = QPointF(-1,-1);
    m_background = this->addPixmap(background);
    makeGrid();

}


void MyScene::makeGrid()
{
    //Make a grid with a little opacity
    QPen gPen(Qt::lightGray);
    ;
    for(int i = m_pixle ; i < 800; i = i +m_pixle)
    {
        m_grid.append(this->addLine(i,0,i,600, gPen));
        m_grid.last()->setOpacity(0.2f);
    }
    for(int i = m_pixle; i < 600; i = i +m_pixle)
    {
        m_grid.append(this->addLine(0,i,800,i,gPen));
        m_grid.last()->setOpacity(0.2f);
    }

}
void MyScene::showGrid()
{
    for(int index = 0; index < m_grid.length();index++)
        m_grid[index]->show();
}
void MyScene::hideGrid()
{
    for(int index = 0; index < m_grid.length();index++)
        m_grid[index]->hide();
}
void MyScene::removeNone(){
    for(int index = 0; index < m_images.length();index++){
        if(m_images[index]->data(0).toString() == m_none){
            this->removeItem(m_images[index]);
            m_images.removeAt(index);
            --index;
        }
    }
}


void MyScene::paintImagesRect(QPointF leftCorner, QPointF rightCorner){
    for(int y = leftCorner.y();y < rightCorner.y() + m_cursorImage->rect().height();y = y + m_cursorImage->rect().height()){
    for(int x = leftCorner.x();x < rightCorner.x() + m_cursorImage->rect().width();x = x + m_cursorImage->rect().width()){
    int index;
        bool canPut = true;
        for(index = 0; index < m_images.length();index++){
            if(m_images[index]->pos().x() > x &&
                    m_images[index]->pos().x() < x + m_cursorImage->rect().width()
                    || (m_images[index]->pos().x() + m_images[index]->pixmap().width() > x
                        && m_images[index]->pos().x() < x
                        )
                    || m_images[index]->pos().x() == x){
                if(m_images[index]->pos().y() > y &&
                        m_images[index]->pos().y() < y + m_cursorImage->rect().height()
                        || (m_images[index]->pos().y() + m_images[index]->pixmap().height() > y
                            && m_images[index]->pos().y() < y
                            )
                        || m_images[index]->pos().y() == y){
                canPut = false;
                break;
                }
            }
        }
        if(canPut){
            m_images.append(this->addPixmap(m_imagePath));
            m_images.last()->setData(0, m_imagePath);
            m_images.last()->setPos(QPoint(x,y));
        }
    }
    }
}

void MyScene::removeImagesRect(QPointF leftCorner, QPointF rightCorner){
    for(int y = leftCorner.y();y < rightCorner.y() + m_cursorImage->rect().height();y = y + m_cursorImage->rect().height()){
    for(int x = leftCorner.x();x < rightCorner.x() + m_cursorImage->rect().width();x = x + m_cursorImage->rect().width()){
        for(int index = 0; index < m_images.length(); index++){
            if(m_images[index]->pos() == QPointF(x,y)){
                this->removeItem(m_images[index]);
                m_images.removeAt(index);
                break;
            }
        }
        }
    }
}

void MyScene::setImage(QString path){
    //set path to Image in resources and set the crusorImage
    m_imagePath = path;
    QPen *myPen = new QPen();
    myPen->setColor(Qt::green);
    myPen->setWidth(2);
    QPixmap newImage;
    newImage.load(m_imagePath);
    if(m_cursorImage)
    {
        delete m_cursorImage;
    }
    m_cursorImage = this->addRect(0,0,newImage.width(),newImage.height(),*myPen,Qt::white);
    m_cursorImage->setOpacity(0.4f);
    m_cursorImage->setZValue(1);
}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //active at mouse button press
    //if left button then add picture if rigth butten remove picture
    if(event->button() == Qt::LeftButton)
         {
             if(m_shift){
                 if(m_shiftLeftCorner != QPointF(-1,-1)){
                     paintImagesRect(m_shiftLeftCorner,m_cursor);
                     m_shiftLeftCorner = QPointF(-1,-1);
                 }
                 else{
                     m_shiftLeftCorner = m_cursor;
                 }
             }
             else{
                 int index;
                     bool canPut = true;
                     for(index = 0; index < m_images.length();index++){
                         if(m_images[index]->pos().x() > m_cursorImage->pos().x() &&
                                 m_images[index]->pos().x() < m_cursorImage->pos().x() + m_cursorImage->rect().width()
                                 || (m_images[index]->pos().x() + m_images[index]->pixmap().width() > m_cursorImage->pos().x()
                                     && m_images[index]->pos().x() < m_cursorImage->pos().x()
                                     )
                                 || m_images[index]->pos().x() == m_cursorImage->pos().x()){
                             if(m_images[index]->pos().y() > m_cursorImage->pos().y() &&
                                     m_images[index]->pos().y() < m_cursorImage->pos().y() + m_cursorImage->rect().height()
                                     || (m_images[index]->pos().y() + m_images[index]->pixmap().height() > m_cursorImage->pos().y()
                                         && m_images[index]->pos().y() < m_cursorImage->pos().y()
                                         )
                                     || m_images[index]->pos().y() == m_cursorImage->pos().y()){
                             canPut = false;
                             break;
                             }
                         }
                     }
                     if(canPut){
                         m_images.append(this->addPixmap(m_imagePath));
                         m_images.last()->setData(0, m_imagePath);
                         m_images.last()->setPos(m_cursor);
                     }
             }

         }

         if(event->button() == Qt::RightButton){
             //pixmap remove
             if(m_shift){
                 if(m_shiftLeftCorner != QPointF(-1,-1)){
                     removeImagesRect(m_shiftLeftCorner,m_cursor);
                     m_shiftLeftCorner = QPointF(-1,-1);
                 }
                 else{
                     m_shiftLeftCorner = m_cursor;
                 }
             }
             else{
                 for(int index = 0; index < m_images.length(); index++){
                     if(m_images[index]->pos() == m_cursor){
                         this->removeItem(m_images[index]);
                         m_images.removeAt(index);
                         break;
                     }
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
    m_cursor.operator -=(QPointF(m_cursorImage->rect().width(),m_cursorImage->rect().height()));
    //picture cant get out of screen
    if(m_cursor.x()<0)
        m_cursor.setX(0);
    if(m_cursor.y()<0)
        m_cursor.setY(0);
    if((m_cursor.x())+m_cursorImage->rect().width()>800)
        m_cursor.setX(800-m_cursorImage->rect().width());
    if((m_cursor.y())+m_cursorImage->rect().height()>600)
        m_cursor.setY(600-m_cursorImage->rect().height());
    m_cursorImage->setPos(m_cursor);

}


void MyScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
        m_shift = true;
}


void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
        m_shift = false;
}

