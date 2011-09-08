#ifndef MAPINFO_H
#define MAPINFO_H

#include <QtGui>

class MapInfo
{
public:
    MapInfo();

    void setItems(QList <QGraphicsPixmapItem *> items,QString imageFolder);
    void setBackground(QGraphicsPixmapItem* newBackground, bool repeat,QString imageFolder );
    QString itemsToString();
    QString backgroundToString();
    void setMap(QString name, int width, QString info );
    QString mapToString();
    bool saveFile(QString filePath);
    bool loadFile(QString filePath);
    QString getBgPath() {return m_bgPath;};
    QString getName() {return m_mapName;};
    QString getInfo() {return m_info;};
    int getWidth () {return m_sceneWidth; };
    bool getBgRepeat() {return m_bgRepeat ;};
    QString getItemPath(int index) { return m_itemsPath[index]; };
    int getItemX(int index) { return m_itemsX[index]; };
    int getItemY(int index) { return m_itemsY[index]; };
    int getItemZ(int index) { return m_itemsZ[index]; };
    int getItemsCount() {return m_itemsPath.count();};



private:
    QList <QGraphicsPixmapItem *> m_items;
    QGraphicsPixmapItem *m_background;
    QString m_mapName, m_info, m_bgPath;
    QList <QString> m_itemsPath;
    QList <int> m_itemsX, m_itemsY, m_itemsZ;
    int m_sceneWidth;
    bool m_bgRepeat;


};

#endif // MAPINFO_H
