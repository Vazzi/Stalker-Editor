#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui>

class MyScene: public QGraphicsScene
{
public:
    MyScene();
private:
    void chessboard();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QPoint m_cursor;
};

#endif // MYSCENE_H
