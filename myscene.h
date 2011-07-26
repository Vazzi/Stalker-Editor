#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui>

class MyScene: public QGraphicsScene
{
public:
    MyScene(int newPixle);
    void AddTexture(QString path);
private:
    void makeGrid();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QPointF m_cursor;
    QGraphicsPixmapItem *m_texture;
    QString m_texturePath;
    QGraphicsRectItem *m_rectangle;
    int m_pixle;
};

#endif // MYSCENE_H
