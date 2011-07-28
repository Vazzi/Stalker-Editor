#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui>


class MyScene: public QGraphicsScene
{
public:
    MyScene(int newPixle, QString background);
    void setImage(QString path);
    void showGrid();
    void hideGrid();

    QString getImages() { return m_images.last()->data(0).toString(); }

    bool readMap();
    bool writeMap();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


    void makeGrid();

    int m_pixle;
    QPointF m_cursor;
    QString m_imagePath;
    QList<QGraphicsPixmapItem *> m_images;
    QList<QGraphicsLineItem *> m_grid;
    QGraphicsRectItem *m_cursorImage;
    QGraphicsPixmapItem *m_background;

};

#endif // MYSCENE_H
