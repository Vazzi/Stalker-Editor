#include "mapinfo.h"
#include <QtGui>


MapInfo::MapInfo()
{

}

void MapInfo::setItems(QList<QGraphicsPixmapItem *> items,QString imageFolder){
    //set items
    m_items = items;

    //remove absolute image path if image has any (has been imported)
    QString itemPath;
    for(int index = 0; index < m_items.count(); index++){
        itemPath = m_items[index]->data(0).toString();
        if(!itemPath.contains(":/images/",Qt::CaseSensitive)){
            itemPath = "/" + imageFolder + "/" + itemPath.split("/").last();
            m_items[index]->setData(0,itemPath) ;
        }
    }
}

void MapInfo::setBackground(QGraphicsPixmapItem* newBackground, bool repeat,QString imageFolder){
    //set background and bgRepeat
    //if background repeat true else false
    m_bgRepeat = repeat;

    QString itemPath = newBackground->data(0).toString();
    if(!itemPath.contains(":/images/",Qt::CaseSensitive)){
        itemPath = "/" + imageFolder + "/" + itemPath.split("/").last();
        newBackground->setData(0,itemPath);
    }
    m_background = newBackground;


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
    //save file
    QFile saveMap(filePath);
    //control if can save
    if(!saveMap.open(QFile::WriteOnly | QFile::Text))
        return false;
    //save text
    QTextStream out(&saveMap);
    out << mapToString();
    out << backgroundToString();
    out << itemsToString();
    saveMap.close();
    //return true if everything is OK
    return true;

}

bool MapInfo::loadFile(QString filePath){

    //load file
    //file structure:
        // name;info;width;backround;item_1;item_2;...item_n;
    QFile loadMap(filePath);
    int i;
    QList <QString> itemsInStr, members, bgInStr,membersInItems;
    QString data;

    //control if can work with file
    if(!loadMap.open(QFile::ReadOnly | QFile::Text))
        return false;

    data = loadMap.readAll();
    members = data.split(";");

    //control basics
    if(members[0] == "")
        return false;
    m_mapName = members[0];
    m_info = members[1];

    //width
    bool ok;
    m_sceneWidth = members[2].toInt(&ok , 10);
    if(!ok)
        return false;

    //background
    bgInStr = members[3].split(",");
    m_bgPath = bgInStr[0];
    m_bgRepeat = bgInStr[1].toInt(&ok, 10);

    //get all items
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

    QString imageFolderPath = filePath.remove(".map",Qt::CaseSensitive);
    imageFolderPath.append("_images/");
    QDir imageFolder;
    filePath.remove(filePath.split("/").last());
    filePath = filePath.left(filePath.count()-1);
    if(imageFolder.cd(imageFolderPath)){
        if(!m_bgPath.startsWith(":/images/",Qt::CaseSensitive)){
            m_bgPath = filePath + m_bgPath;
        }
        for(i = 0; i < m_itemsPath.count(); i++ ){
            if(!m_itemsPath[i].startsWith(":/images/",Qt::CaseSensitive)){
                m_itemsPath[i] = filePath + m_itemsPath[i];
            }
        }
    }

    return true;

}
