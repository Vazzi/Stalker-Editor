#ifndef MAPINFO_H
#define MAPINFO_H

#include <QtGui>

class MapInfo
{
public:
    MapInfo();

    void setItems(QList <QGraphicsPixmapItem *> items);
    void setBackground(QGraphicsPixmapItem* newBackground, bool repeat);
    QString itemsToString();
    QString backgroundToString();
    void setMap(QString name, int width, QString info );
    QString mapToString();



private:
    QList <QGraphicsPixmapItem *> m_items;
    QGraphicsPixmapItem *m_background;
    QString m_mapName, m_info;
    int m_sceneWidth;
    bool m_bRepeat;

};

#endif // MAPINFO_H
