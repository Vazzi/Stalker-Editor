#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui>


class MyScene: public QGraphicsScene
{
public:
    MyScene(int newPixle, QString background);
    void setImage(QString path);
    QString getImages() { return m_images.last()->data(0).toString(); }
    bool readMap();
    bool writeMap();
private:
    void makeGrid();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    int m_pixle;
    QPointF m_cursor;
    QString m_imagePath;
    QList<QGraphicsPixmapItem *> m_images;
    QGraphicsPixmapItem *m_cursorImage;
    QGraphicsPixmapItem *m_background;
};

#endif // MYSCENE_H
