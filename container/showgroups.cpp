#include "showgroups.h"

ShowGroups::ShowGroups(QObject *parent) :
    QObject(parent)
{
}

void ShowGroups::addGroup(QString name, QModelIndex parent){
    //Parent muss gruppe sein
    if(gruppenModel.getItem(parent)->getElementType() == AbstractElement::GRUPPE){
        //Hole Parent
        Gruppe *pg = (Gruppe*)gruppenModel.getItem(parent);
        Gruppe *g = new Gruppe(name, "", QString(), pg);
        pg->appendChild(g);
    }
}

QString ShowGroups::loadFromXML(QString projectPath){
    QFile groupsFile(projectPath + "/groups.xml");
    if(groupsFile.exists()){
        //Datei öffnen
        if (groupsFile.open(QIODevice::ReadOnly)){
            QXmlStreamReader xmlReader(&groupsFile);
            //Gruppen laden
            while(!xmlReader.atEnd() && !xmlReader.hasError()) {
                if(xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "groupsList"){
                    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "groupsList")) {
                        if(xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "group"){
                            //Einzelne Gruppeneinträge laden
                            if(!loadGroupElement(&xmlReader)) return QString(tr("Laden der Gruppe fehlgeschlagen."));
//                            GruppenTyp *g = new GruppenTyp(name);
//                            gruppenTypen.append(g);
                        }
//                        // *** Pfade zu den letzten Projekten
//                      if(xmlReader.name() == "project"){
//                            lastUsedProjectFiles.append(QDir(xmlReader.readElementText()));
//                        }
                        xmlReader.readNext();
                    }
                }
                xmlReader.readNext();
            }
        }
        return QString();
    }
    return QString(tr("Datei groups.xml nicht gefunden."));
}


bool ShowGroups::loadGroupElement(QXmlStreamReader *xmlReader, AbstractElement *parentElement){
    if(!parentElement){
        parentElement = gruppenModel.getItem(QModelIndex());
    }
    QString name;
    QColor color;
    while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "group")) {
//        qDebug() << "Gruppe";
        if(xmlReader->name() == "name"){
            name = xmlReader->readElementText();
//            qDebug() << "Name: " << name;
        }
        if(xmlReader->name() == "color"){
            color = QColor(xmlReader->readElementText());
//            qDebug() << "Color: " << color;
        }
        xmlReader->readNext();
    }
    Gruppe *g = new Gruppe(name, "", "", parentElement);
    parentElement->appendChild(g);
    return true;
//    addGroup(name, QModelIndex());

}
