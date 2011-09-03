#include "mapinfo.h"
#include <QtGui>


MapInfo::MapInfo()
{

}

void MapInfo::setItems(QList<QGraphicsPixmapItem *> items){
    //set items
    m_items = items;
}

void MapInfo::setBackground(QGraphicsPixmapItem* newBackground, bool repeat){
    //set background and bgRepeat
    //if background repeat true else false
    m_background = newBackground;
    m_bgRepeat = repeat;
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
    backgroundString.append(QString::number(m_bgRepeat) + ";");
    return backgroundString;

}

QString MapInfo::mapToString(){
    //map information to string
    //mapname;some_information;scene_width;
    QString infoString;
    infoString.append(m_mapName + ";" + m_info + ";" + QString::number(m_sceneWidth)+ ";");
    return infoString;
}

bool MapInfo::saveFile(QString filePath){
    QFile saveMap(filePath);
    if(!saveMap.open(QFile::WriteOnly | QFile::Text))
        return false;
    QTextStream out(&saveMap);
    out << mapToString();
    out << backgroundToString();
    out << itemsToString();
    saveMap.close();
    return true;

}

bool MapInfo::loadFile(QString filePath){
    QFile loadMap(filePath);
    int i;
    QList <QString> itemsInStr, members, bgInStr,membersInItems;
    QString data;


    if(!loadMap.open(QFile::ReadOnly | QFile::Text))
        return false;
    data = loadMap.readAll();
    members = data.split(";");
    if(members[0] == "")
        return false;
    m_mapName = members[0];
    m_info = members[1];
    bool ok;
    m_sceneWidth = members[2].toInt(&ok , 10);
    if(!ok)
        return false;

    bgInStr = members[3].split(",");
    m_bgPath = bgInStr[0];
    m_bgRepeat = bgInStr[1].toInt(&ok, 10);
    i = 4;
    while(members[i] != ""){
        itemsInStr.append(members[i++]);
    }
    m_itemsPath.clear();

    for(i = 0 ; i < itemsInStr.count() ; i++){
        membersInItems = itemsInStr[i].split(",");
        m_itemsPath.append(membersInItems[0]);

        m_itemsX.append(membersInItems[1].toInt(&ok, 10));
        m_itemsY.append(membersInItems[2].toInt(&ok, 10));
        m_itemsZ.append(membersInItems[3].toInt(&ok, 10));
    }

    return true;

}
