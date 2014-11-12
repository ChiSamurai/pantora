#include "project.h"

Project::Project(QString path, QWidget *parent) : QObject(parent){
        drawKoordinatenkreuz = false;
        model = new ElementModel(this);
        anzeigeModel = new ElementModel(this);
        projectsDir = path;
        invertXAxis = false;

//        nullPoint = QVector3D(0.0, 0.0, 0.0);
        camPos = QVector3D(nullPoint.x() - 1.0f, nullPoint.y() + 2.0f, nullPoint.z() - 4.0f);

        //Verzeichnisse erstellen, wenn nicht bereits vorhanden
        QDir dir(projectsDir);
        dir.mkdir("scans");
//        elementeModel->itemFromIndex(elementeModel->index(0,0))->setGruppe(scanRootGruppe);

        //Scan-Gruppe erstellen
        AbstractElement *i = model->getItem();
        Gruppe *scanGruppe = new Gruppe(tr("Scans"), "", "");
        model->insertChild(scanGruppe); //an Model-Root anhängen
        scansGruppe = model->index(0,0);

        //TexturenGruppe zur Anzeigegruppe hinzufügen
        am_texturenGruppe = new Gruppe(tr("Zeichnungen"), "", "");
        anzeigeModel->insertChild(am_texturenGruppe);
        am_texturenIndex = anzeigeModel->index(0, 0);
}

Project::~Project(){

}

void Project::close(){
    //GL texturen unloaden
    for(int i = 0; i < model->rowCount(scansGruppe); i++){
        Scan* s = (Scan*)model->getItem(model->index(i, 0, scansGruppe));
        QPersistentModelIndex scanIndex = model->index(i, 0, scansGruppe);
        if(model->rowCount(scanIndex) > 0){
            QPersistentModelIndex texturenIndex = model->index(0, 0, scanIndex);
            //Alle Texturen zeichnen
            for(int j = 0; j < model->rowCount(texturenIndex); j++){
                QPersistentModelIndex thisTexIndex = model->index(j, 0, texturenIndex);
                Textur *t = (Textur*)model->getItem(thisTexIndex);
                delete t;
            }
        }
    }

    punktgruppen.clear();
    scans.clear();
}

//bool Project::connectInterface(qThreadInterface* interface){
//	this->interface = interface;
//        return true;
//}

void Project::GLdraw(QGLWidget *glw){
    for(int i = 0; i < model->rowCount(scansGruppe); i++){
        Scan* s = (Scan*)model->getItem(model->index(i, 0, scansGruppe));
        QPersistentModelIndex scanIndex = model->index(i, 0, scansGruppe);
        if(model->rowCount(scanIndex) > 0){
            QPersistentModelIndex texturenIndex = model->index(0, 0, scanIndex);
            //Alle Texturen zeichnen
            for(int j = 0; j < model->rowCount(texturenIndex); j++){
                QPersistentModelIndex thisTexIndex = model->index(j, 0, texturenIndex);
                Textur *t = (Textur*)model->getItem(thisTexIndex);
                t->GLdraw(glw, invertXAxis);
            }
//            qDebug() << model->getItem(texturenIndex)->getName();
        }
//        qDebug() << s->getName();
//        s->GLdraw(glw);
    }
//    scans.GLdraw(glw);
//        if(drawKoordinatenkreuze) koordKreuz->draw();
}

void Project::GLinit(QGLWidget *glw){
    scans.GLinit(glw);
}

//bool Project::clear(){
//    punktecontainer = new contPoints();
//    punktgruppencontainer = new ContPunktGruppen();
//}

//void Project::addScan(Scan *s){
//    _scans.append(s);
//}

//ContScans *Project::getScansContainer(){
//    return scans;
//}

QString Project::load(QString dir){
    QString error;
    //Scans laden
    error = scans.loadFromXML(dir + "/scans");
    if(!error.isNull()) {
        return error;
    }

    projectsDir = dir;

    //Projekteinstellungen laden
    loadProjectSettings(dir);

    //Gruppentypen laden
//    loadGroupTypes();

    foreach(Scan *s, scans.getScans()){
        //Scan an Scangruppe anhängen
        Gruppe *scanGruppe = (Gruppe*)model->getItem(scansGruppe);
        s->setParent(scanGruppe);
        scanGruppe->appendChild(s);
        //ToDo: in scan-Klasse verschieben Texturgruppe an Scan anhängen
        Gruppe *texturGruppe = new Gruppe(tr("Texturen"), "", "", s);
        s->appendChild(texturGruppe);
        foreach(Textur* t, s->getTextures()){
            //Textur an Texturgruppe anhängen
            t->setParent(texturGruppe);
            texturGruppe->appendChild(t);
        }
    }

//    //Texturen zu Anzeigemodel hinzufügen
//    for(int i = 0; i < model->rowCount(scansGruppe); i++){
//        Scan* s = (Scan*)model->getItem(model->index(i, 0, scansGruppe));
//        QPersistentModelIndex scanIndex = model->index(i, 0, scansGruppe);
//        if(model->rowCount(scanIndex) > 0){
//            QPersistentModelIndex texturenIndex = model->index(0, 0, scanIndex);
//            //Alle Texturen zu Texturmodel hinzufügen
//            for(int j = 0; j < model->rowCount(texturenIndex); j++){
//                QPersistentModelIndex thisTexIndex = model->index(j, 0, texturenIndex);
//                am_texturenGruppe
//            }
//        }
//    }


    //ShowGruppen laden
//    error = anzeigegruppen.loadFromXML(projectsDir);
//    if(!error.isNull()) {
//        return error;
//    }
//    anzeigeModel = anzeigegruppen.getModel();
    return error;
}

QString Project::save(){
    try{
        QString error;
        //Bilder speichern
        error.append(scans.saveToXML(model));
        //Projekteinstellungen speichern
        error.append(saveProjectSettings(projectsDir));

//        QString error = saveScans(this->);
        if(!error.isNull()) throw error;
    }
    catch (QString error){
        return error;
    }
    return NULL;
}

bool Project::loadGroupTypes(){
//    qDebug() << projectsDir;
    QFile types(projectsDir + "/groupTypes.xml");
    if(types.exists()){
//        //letzte Projekte lesen
        if (types.open(QIODevice::ReadOnly)){
            QXmlStreamReader xmlReader(&types);
            while(!xmlReader.atEnd() && !xmlReader.hasError()) {
                if(xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "groupTypes"){
                    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "groupTypes")) {
                        if(xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "group"){
                            QString name;
                            QColor color;
                            while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "group")) {
                                if(xmlReader.name() == "name"){
                                    //qDebug() << "Name: " << xmlReader.readElementText();
                                    name = xmlReader.readElementText();
                                }
                                if(xmlReader.name() == "color"){
//                                    qDebug() << "Color: " << xmlReader.readElementText();
                                    color = QColor(xmlReader.readElementText());
                                }

                                xmlReader.readNext();
                            }
                            GruppenTyp *g = new GruppenTyp(name);
                            gruppenTypen.append(g);
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
    }
}


//Projekteinstellungen laden
QString Project::loadProjectSettings(QString path){
    QDir dir(path);
    QFile projectSettings(dir.absolutePath() + "/project.xml");
    if(projectSettings.exists()){
        if (projectSettings.open(QIODevice::ReadOnly)){
            QXmlStreamReader xmlReader(&projectSettings);
            while(!xmlReader.atEnd() && !xmlReader.hasError()) {
//                if(xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "project"){
//                    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "project")) {
                if(xmlReader.name() == "project") {
                    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "project")) {
                        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
                            if(xmlReader.name() == "name") name = xmlReader.readElementText();
                            else if(xmlReader.name() == "invertx"){
                                if(xmlReader.readElementText() == "true") invertXAxis = true;
                                else invertXAxis = false;
                            }
                            else if(xmlReader.name() == "null"){
                                QXmlStreamAttributes attr = xmlReader.attributes();
                                nullPoint.setX(attr.value("x").toString().toDouble());
                                nullPoint.setY(attr.value("y").toString().toDouble());
                                nullPoint.setZ(attr.value("z").toString().toDouble());
                            }
                            else if(xmlReader.name() == "camPos"){
                                QXmlStreamAttributes attr = xmlReader.attributes();
                                camPos.setX(attr.value("x").toString().toDouble());
                                camPos.setY(attr.value("y").toString().toDouble());
                                camPos.setZ(attr.value("z").toString().toDouble());
                            }
                        }
                        xmlReader.readNextStartElement();
                    }
                }
                xmlReader.readNext();
            }
        }
    }
    return QString();
}

QString Project::saveProjectSettings(QString path){
    QString error;
    QDir dir(path);
    QFile file(dir.absolutePath() + "/project.xml");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) error = tr("Fehler beim Öffnen der Datei");
    else{
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

        xmlWriter.writeStartElement("project");
        // *** Name
        xmlWriter.writeTextElement("name", name);

        // *** camPos
        xmlWriter.writeStartElement("camPos");
        xmlWriter.writeAttribute("x", QString::number(camPos.x()));
        xmlWriter.writeAttribute("y", QString::number(camPos.y()));
        xmlWriter.writeAttribute("z", QString::number(camPos.z()));
        xmlWriter.writeEndElement();

        // *** null
        xmlWriter.writeStartElement("null");
        xmlWriter.writeAttribute("x", QString::number(nullPoint.x()));
        xmlWriter.writeAttribute("y", QString::number(nullPoint.y()));
        xmlWriter.writeAttribute("z", QString::number(nullPoint.z()));
        xmlWriter.writeEndElement();

        // *** invertx
        xmlWriter.writeTextElement("invertx", (invertXAxis?"true":"false"));

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        if(xmlWriter.hasError()) error = tr("Fehler beim Schreiben der Projekteinstellungen");
    }
    return error;
}

//QString Project::saveScans(QString path){
//    QDir dir(path);
//    if(dir.exists()) removeDir();

//    dir.mkpath("scans");
//    dir.setPath(scans);

//    QFile file(dir.absolutePath() + ("/scans.xml"));
//    //Scan-XML schreiben
//    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) return "Fehler beim Öffnen der Datei";

//    QXmlStreamWriter xmlWriter(&file);
//    xmlWriter.setAutoFormatting(true);
//    xmlWriter.writeStartDocument();

//    xmlWriter.writeStartElement("scanList");

////    foreach(Scan *s, scans){
////        s->saveToXMLStream(&xmlWriter);
////    }

//    xmlWriter.writeEndElement();

//    xmlWriter.writeEndDocument();
//    file.close();

//    return NULL;
//}
