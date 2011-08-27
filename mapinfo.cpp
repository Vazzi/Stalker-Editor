#include "mapinfo.h"

MapInfo::MapInfo()
{

}

void MapInfo::setItems(QList<QGraphicsPixmapItem *> items){
    m_items = items;
}

void MapInfo::setBackground(QGraphicsPixmapItem newBackground, bool repeat){
    m_background = &newBackground;
    m_bRepeat = repeat;
}


QString MapInfo::itemsToString(){
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
    QString background;
    background.append(m_background->data(0).toString());
    background += ",";
    background.append(QString::number(m_bRepeat));

}
