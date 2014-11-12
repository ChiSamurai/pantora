#include "contscans.h"

ContScans::ContScans(){
}

ContScans::~ContScans(){
    clear();
}

void ContScans::clear(){
    foreach(Scan *s, scans){
        delete s;
    }
    scans.clear();

}

int ContScans::saveScan(Scan *s){
    //Ist scan bereits in Liste?
    int index = scans.indexOf(s);
    //wenn nicht, dann hinzufügen
    if(index == -1) scans.append(s);
//    //Ansonsten Bilder updaten
//    else{
//
//    }
    return index;
}

QList<Scan*> ContScans::getScans(){
    return scans;
}


Scan *ContScans::getScanAt(int i){
    return scans[i];
}

QString ContScans::loadFromXML(QString dir){
    scansDir = dir;
    QString filename = scansDir + "/scans.xml";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return QString(QObject::tr("Fehler beim Laden der Datei: ") + filename);
    //ScanXML laden
    QXmlStreamReader xmlReader(&file);
    if(!xmlReader.hasError()){
        scans.clear();  //Scanliste zurücksetzen
        while(!xmlReader.atEnd() &&
                    !xmlReader.hasError()) {
            //Scan laden
//            while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "scanList")) {
                if(xmlReader.name() == "scan") {
                    Scan *s = new Scan(scansDir);
                    QString error = s->loadFromXMLStream(&xmlReader);
                    if (!error.isNull()) return error;
                    //Thumbnails laden
                    s->loadThumbnails();
                    saveScan(s);
//                }
            }
            xmlReader.readNextStartElement();
        }
        return NULL;
    }else{
        return xmlReader.errorString();
    }
}

QString ContScans::saveToXML(ElementModel *em){
    model = em;
    return saveToXMLFile(scansDir);
}

//QString ContScans::saveToXMLFile(QString path){
//    QDir dir(path);
//    if(dir.exists()) removeDir();

//    dir.mkpath(scansDir);
//    dir.setPath(scansDir);

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

//    saveImages();
//    return NULL;
//}

QString ContScans::saveToXMLFile(QString path){
    QDir dir(path);

    dir.mkpath(scansDir);
    dir.setPath(scansDir);

    QFile file(dir.absolutePath() + ("/scans.xml"));
    //Scan-XML schreiben
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) return "Fehler beim Öffnen der Datei";

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("scanList");

    //ToDo: Dirty Hack über ContScans entfenen
    QPersistentModelIndex scansIndex = model->index(0, 0);

    for(int i = 0; i < model->rowCount(scansIndex); i++){
        QPersistentModelIndex thisScanIndex = model->index(i, 0, scansIndex);
        Scan *s = (Scan*)model->getItem(thisScanIndex);
        s->saveToXMLStream(&xmlWriter);
    }

//    foreach(Scan *s, scans){
//        s->saveToXMLStream(&xmlWriter);
//    }

    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();
    file.close();

    return NULL;
}


void ContScans::saveImages(){
    foreach(Scan* s, scans){
//        s->saveImages();
    }
}

bool ContScans::removeDir(){
    bool result = true;
    QDir dir(scansDir);
//    qDebug() << dir.absolutePath();
//    if (dir.exists(dirName)) {
//        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
//            if (info.isDir()) {
//                result = removeDir(info.absoluteFilePath());
//            } else {
//                result = QFile::remove(info.absoluteFilePath());
//            }
//            if (!result) return result;
//        }
//        result = dir.rmdir(dirName);
//    }
    return result;
}

QString ContScans::getScansDir(){
    return scansDir;
}

void ContScans::setScansDir(QString s){
    scansDir = s;
}

QString ContScans::getXmlFile(){
    return xmlFile;
}

void ContScans::setXmlFile(QString s){
    xmlFile = s;
    QFileInfo finfo(xmlFile);
    scansDir = finfo.absolutePath() + "/";
}

void ContScans::GLinit(QGLWidget *glw){
    foreach(Scan *s, scans){
        s->GLinit(glw);
    }
}

void ContScans::GLdraw(QGLWidget *glw){
    foreach(Scan *s, scans){
        s->GLdraw(glw);
    }
}
