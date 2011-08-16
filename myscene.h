#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui>


class MyScene: public QGraphicsScene
{
public:
    MyScene(int newPixle, QString nonePath, QString background, int sceneWidth);
    void setImage(QString path);
    void paintImagesRect(QPointF leftCorner, QPointF rightCorner);
    void removeImagesRect(QPointF leftCorner, QPointF rightCorner);
    void showHideGrid(bool show);
    void removeNone();
    void showHideBackgroudImage(bool show);
    void setBackground(QString backgroundPath);
    void setItemZValue(int zValue);

    QString getImages() { return m_images.last()->data(0).toString(); }

    bool readMap();
    bool writeMap();

    QPointF xyposition;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void makeGrid();
    void shiftRectangle(bool shift);

    int m_pixle,m_sceneWidth, m_zValue;
    bool m_shift, m_eraser;
    QPointF m_cursor, m_shiftLeftCorner;
    QString m_imagePath, m_none;
    QList<QGraphicsPixmapItem *> m_images;
    QList<QGraphicsLineItem *> m_grid;
    QGraphicsRectItem *m_cursorImage, *m_shiftRect;
    QGraphicsPixmapItem *m_background;

};

#endif // MYSCENE_H
