#include "mapinfo.h"

MapInfo::MapInfo()
{

}

void MapInfo::setItems(QList<QGraphicsPixmapItem *> items){
    //set items
    m_items = items;
}

void MapInfo::setBackground(QGraphicsPixmapItem* newBackground, bool repeat){
    //set background and bRepeat
    //if background repeat true else false
    m_background = newBackground;
    m_bRepeat = repeat;
}

void MapInfo::setMap(QString name, int width,QString info = ""){
    //set information about map
    m_mapName = name;
    m_info = info;
    m_sceneWidth = width;
}


QString MapInfo::itemsToString(){

    //convert items to string
    //image,x,y,z;
    QString itemsInString;

    for(int i = 0; i < m_items.count(); i++){
        itemsInString += m_items[i]->data(0).toString() + ',';
        itemsInString +=QString::number(m_items[i]->pos().x()) + ",";
        itemsInString += QString::number(m_items[i]->pos().y()) + ",";
        itemsInString += QString::number(m_items[i]->zValue()) +";";
    }

    return itemsInString;
}

QString MapInfo::backgroundToString(){
    //convert backround info to string
    //image,repeat;
    QString backgroundString;
    backgroundString.append(m_background->data(0).toString());
    backgroundString += ",";
    backgroundString.append(QString::number(m_bRepeat) + ";");
    return backgroundString;

}

QString MapInfo::mapToString(){
    //map information to string
    //mapname;some_information;scene_width;
    QString infoString;
    infoString.append(m_mapName + ";" + m_info + ";" + QString::number(m_sceneWidth)+ ";");
    return infoString;
}
