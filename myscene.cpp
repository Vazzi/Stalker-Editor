#include "myscene.h"
#include <QtGui>



MyScene::MyScene(int newPixle, QString nonePath, int sceneWidth)
{
    m_pixle = newPixle;
    m_none = nonePath;
    m_sceneWidth = sceneWidth;
    m_shift = false;
    m_shiftLeftCorner = QPointF(-1,-1);
    m_background = this->addPixmap(NULL);
    QPen *myPen = new QPen();
    myPen->setColor(Qt::green);
    myPen->setWidth(2);
    m_shiftRect = this->addRect(0,0,1,1,*myPen,Qt::lightGray);
    m_shiftRect->setZValue(11);
    m_shiftRect->setOpacity(0.4f);
    m_shiftRect->setVisible(false);
    makeGrid();

}



void MyScene::makeGrid()
{
    //Make a grid with a little opacity
    QPen gPen(Qt::lightGray);
    ;
    for(int i = m_pixle ; i < m_sceneWidth; i = i +m_pixle)
    {
        m_grid.append(this->addLine(i,0,i,600, gPen));
        m_grid.last()->setOpacity(0.2f);
    }
    for(int i = m_pixle; i < 600; i = i +m_pixle)
    {
        m_grid.append(this->addLine(0,i,m_sceneWidth,i,gPen));
        m_grid.last()->setOpacity(0.2f);
    }

}
void MyScene::showHideGrid(bool show)
{
    if(show){
    for(int index = 0; index < m_grid.length();index++)
        m_grid[index]->show();
    }
    else{
    for(int index = 0; index < m_grid.length();index++)
        m_grid[index]->hide();
    }

}

void MyScene::removeNone(){
    //remove none images from list
    for(int index = 0; index < m_images.length();index++){
        if(m_images[index]->data(0).toString() == m_none){
            this->removeItem(m_images[index]);
            m_images.removeAt(index);
            --index;

        }
    }
}



void MyScene::paintImagesRect(QPointF leftCorner, QPointF rightCorner){
    //put pictures into the scene into the rectangle (leftCorner x rightCorner)
    int helper;

    if(leftCorner.x() > rightCorner.x()){
            helper = rightCorner.x();
            rightCorner.setX(leftCorner.x());
            leftCorner.setX(helper);
    }
    if(leftCorner.y() > rightCorner.y()){
            helper = rightCorner.y();
            rightCorner.setY(leftCorner.y());
            leftCorner.setY(helper);
    }
    for(int y = leftCorner.y();y < rightCorner.y();y = y + m_cursorImage->rect().height()){
    for(int x = leftCorner.x();x < rightCorner.x();x = x + m_cursorImage->rect().width()){
    int index;
        bool canPut = true;
        //if there is no picture in the way it add picture else none
        for(index = 0; index < m_images.length();index++){
            if(m_images[index]->data(1)!=m_zValue)
                continue;
            if(m_images[index]->pos().x() > x &&
                    m_images[index]->pos().x() < x + m_cursorImage->rect().width()
                    || (m_images[index]->pos().x() + m_images[index]->pixmap().width() > x
                        && m_images[index]->pos().x() < x)
                    || m_images[index]->pos().x() == x){
                if(m_images[index]->pos().y() > y &&
                        m_images[index]->pos().y() < y + m_cursorImage->rect().height()
                        || (m_images[index]->pos().y() + m_images[index]->pixmap().height() > y
                            && m_images[index]->pos().y() < y)
                        || m_images[index]->pos().y() == y){
                canPut = false;
                break;
                }
            }
        }
        //can i put a picture put else none
        if(canPut){
            m_images.append(this->addPixmap(m_imagePath));
            m_images.last()->setZValue(m_zValue);
            m_images.last()->setData(0, m_imagePath);
            m_images.last()->setPos(QPoint(x,y));
            m_images.last()->setData(1,m_zValue);
            if(m_visibleLayer!=m_zValue && m_visibleLayer!=0)
                m_images.last()->setVisible(false);

        }
    }
    }

}

void MyScene::removeImagesRect(QPointF leftCorner, QPointF rightCorner){
    //remove all pictures in the rectangle(leftCorner x rightCorner)
    int helper;

    if(leftCorner.x() > rightCorner.x()){
            helper = rightCorner.x();
            rightCorner.setX(leftCorner.x());
            leftCorner.setX(helper);
    }
    if(leftCorner.y() > rightCorner.y()){
            helper = rightCorner.y();
            rightCorner.setY(leftCorner.y());
            leftCorner.setY(helper);
    }
    for(int y = leftCorner.y();y < rightCorner.y();y += m_pixle){
    for(int x = leftCorner.x();x < rightCorner.x();x += m_pixle){
                for(int index = 0; index < m_images.length(); index++){
                    if(m_images[index]->data(1)!=m_zValue)
                        continue;
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
    //set path to Image in resources and set the crusorRectangel
    m_imagePath = path;
    QPen *myPen = new QPen();
    myPen->setWidth(2);
    QPixmap newImage;
    this->removeItem(m_cursorImage);
    if(m_imagePath==":/images/rubber"){
        myPen->setColor(Qt::red);
        newImage.load(m_none);
        m_shiftRect->setPen(*myPen);
        m_eraser = true;
    }
    else{
        myPen->setColor(Qt::green);
        newImage.load(m_imagePath);
        m_shiftRect->setPen(*myPen);
        m_eraser = false;
    }

    /*if(m_cursorImage)
    {
        delete m_cursorImage;
    }*/
    m_cursorImage = this->addRect(0,0,newImage.width(),newImage.height(),*myPen,Qt::white);
    m_cursorImage->setOpacity(0.4f);
    m_cursorImage->setZValue(11);
    shiftRectangle(false);

}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //active at mouse button press
    //if eraser is active erase images else add images
    if(event->button() == Qt::LeftButton){
        if(m_eraser){
            //erase image
            if(m_shift){
                    removeImagesRect(m_shiftLeftCorner,m_cursor);
            }
            else{
                removeImagesRect(m_cursor,m_cursor);
            }
         }
        else{
             if(m_shift){
                     paintImagesRect(m_shiftLeftCorner,m_cursor);
             }
             else{
                 int index;
                     bool canPut = true;

                     for(index = 0; index < m_images.length();index++){
                         if(m_images[index]->data(1)!=m_zValue)
                             continue;
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
                     /*
                     m_cursorImage->setVisible(false);
                     if(this->itemAt(m_cursorImage->pos().x(),m_cursorImage->pos().y())->zValue()!=0){
                        canPut=false;
                        QMessageBox::information(0,"prd", QString::number(this->itemAt(m_cursorImage->pos().x(),m_cursorImage->pos().y())->zValue()));
                     }
                     m_cursorImage->setVisible(true);
                     */
                     if(canPut){
                         m_images.append(this->addPixmap(m_imagePath));
                         m_images.last()->setZValue(m_zValue);
                         m_images.last()->setData(1,m_zValue);
                         m_images.last()->setData(0, m_imagePath);
                         m_images.last()->setPos(m_cursor);
                         if(m_visibleLayer!=m_zValue && m_visibleLayer!=0)
                             m_images.last()->setVisible(false);

                     }
                 }
             }

  }
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //active when mouse move
    //it changes position of cursorImage where cursor is
    xyposition = event->scenePos();

    m_cursor.setX(event->scenePos().x());
    m_cursor.setY(event->scenePos().y());

    if(m_shiftRect->isVisible()){
        int intRemainder = ((int(m_cursor.x()) - int(m_shiftLeftCorner.x())) % int(m_cursorImage->rect().width()));
        if(m_cursor.x()>m_shiftLeftCorner.x())
            m_cursor.setX((int(m_cursor.x()) - intRemainder)+m_cursorImage->rect().width());
        else
            m_cursor.setX((int(m_cursor.x()) - intRemainder)-m_cursorImage->rect().width());

        intRemainder =(int(int(m_cursor.y()) - int(m_shiftLeftCorner.y())) % int(m_cursorImage->rect().height()));
        if(m_cursor.y()>m_shiftLeftCorner.y())
            m_cursor.setY((int(m_cursor.y()) - intRemainder)+m_cursorImage->rect().height());
        else
            m_cursor.setY((int(m_cursor.y()) - intRemainder)-m_cursorImage->rect().height());


        if(m_cursor.x()>m_sceneWidth)
            m_cursor.setX(m_cursor.x()-m_cursorImage->rect().width());
        else if(m_cursor.x()<0)
            m_cursor.setX(m_cursor.x()+m_cursorImage->rect().width());
        if(m_cursor.y()>600)
            m_cursor.setY(m_cursor.y()-m_cursorImage->rect().height());
        else if(m_cursor.y()<0)
            m_cursor.setY(m_cursor.y()+m_cursorImage->rect().height());

        QRect rectangle;
          if(m_shiftLeftCorner.x() < m_cursor.x()){
              if(m_shiftLeftCorner.y() < m_cursor.y())
                  rectangle.setCoords(m_shiftLeftCorner.x(),m_shiftLeftCorner.y(),m_cursor.x(), m_cursor.y());
              else
                  rectangle.setCoords(m_shiftLeftCorner.x(),m_cursor.y(),m_cursor.x(), m_shiftLeftCorner.y());
          }
          else{
              if(m_shiftLeftCorner.y() < m_cursor.y())
                  rectangle.setCoords(m_cursor.x(),m_shiftLeftCorner.y(),m_shiftLeftCorner.x(), m_cursor.y());
              else
                  rectangle.setCoords(m_cursor.x(),m_cursor.y(),m_shiftLeftCorner.x(), m_shiftLeftCorner.y());
          }

          m_shiftRect->setRect(rectangle);


    }
    else{
        if((int(m_cursor.x()) % m_pixle) != 0)
            m_cursor.setX(int(m_cursor.x()) - (int(m_cursor.x()) % m_pixle));
        if((int(m_cursor.y()) % m_pixle) != 0)
            m_cursor.setY(int(m_cursor.y()) - (int(m_cursor.y()) % m_pixle));
        //picture cant get out of screen
            if(m_cursor.x()<0)
                m_cursor.setX(0);
            if(m_cursor.y()<0)
                m_cursor.setY(0);
            if((m_cursor.x())+m_cursorImage->rect().width()>m_sceneWidth)
                m_cursor.setX(m_sceneWidth-m_cursorImage->rect().width());
            if((m_cursor.y())+m_cursorImage->rect().height()>600)
                m_cursor.setY(600-m_cursorImage->rect().height());
        m_cursorImage->setPos(m_cursor);

    }


}


void MyScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
        shiftRectangle(true);

}


void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
        shiftRectangle(false);
}

void MyScene::showHideBackgroudImage(bool show){
    if(show)
        m_background->show();
    else
        m_background->setVisible(false);

}

void MyScene::setBackground(QString backgroundPath){
    QPixmap newBackground;
    newBackground.load(backgroundPath);
    m_background->setPixmap(newBackground);
}

void MyScene::shiftRectangle(bool shift){
    if(shift){
        m_shiftLeftCorner = m_cursor;
        m_shiftRect->setVisible(true);
        m_cursorImage->setVisible(false);
        m_shiftRect->setRect(m_cursor.x(), m_cursor.y(),m_cursorImage->rect().width(),m_cursorImage->rect().height());
        m_shift = true;
    }
    else{
        m_shiftRect->setVisible(false);
        m_cursorImage->setVisible(true);
        m_shift = false;
        m_shiftLeftCorner = QPointF(-1,-1);


    }
}
void MyScene::setItemZValue(int zValue){
    m_zValue = zValue;

}

void MyScene::showLayer(int layer){
    if(layer==0){
        for(int i = 0; i<m_images.length();i++)
            m_images[i]->setVisible(true);
    }
    else{
        for(int i = 0; i<m_images.length();i++){
            if(m_images[i]->data(1).toInt()==layer)
                m_images[i]->setVisible(true);
            else
                m_images[i]->setVisible(false);
        }
    }
    m_visibleLayer=layer;
}

void MyScene::clearlyNewScene(int sceneWidth){
    for(int i = 0; i<m_images.length();i++)
       this->removeItem(m_images[i]);
    m_images.clear();

    m_sceneWidth = sceneWidth;
    for(int i = 0; i<m_grid.length();i++)
       this->removeItem(m_grid[i]);
    makeGrid();

}

void MyScene::fill(){
    if(m_imagePath==":/images/rubber")
        removeImagesRect(QPoint(0,0),QPoint(m_sceneWidth,600));
    else
        paintImagesRect(QPoint(0,0),QPoint(m_sceneWidth,600));
}


















