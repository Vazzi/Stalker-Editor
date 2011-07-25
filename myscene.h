#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui>

class MyScene: public QGraphicsScene
{
public:
    MyScene();
    void AddTexture(QString path);

private:
    void chessboard();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QPointF m_cursor;
    QGraphicsPixmapItem *m_texture;
    QString m_texturePath;
    QGraphicsRectItem *m_rectangle;
};

#endif // MYSCENE_H
