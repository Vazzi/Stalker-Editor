#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui>


class MyScene: public QGraphicsScene
{
public:
    MyScene(int newPixle);
    void setImage(QString path);
    int getImages() { return m_images.length(); };
private:
    void makeGrid();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QPointF m_cursor;
    QList<QGraphicsPixmapItem *> m_images;
    QString m_imagePath;
    QGraphicsPixmapItem *m_cursorImage;
    int m_pixle;
};

#endif // MYSCENE_H
