#ifndef MAPINFO_H
#define MAPINFO_H

#include <QtGui>

class MapInfo
{
public:
    MapInfo();

private:
    QList <QString> m_items;
    QString m_background, m_mapName,m_sceneWidth,m_info;
};

#endif // MAPINFO_H
