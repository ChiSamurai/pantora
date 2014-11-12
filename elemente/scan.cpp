#include "scan.h"

Scan::Scan(QString scansDir, QString uuid, AbstractElement *parent) : AbstractElement(parent) {
    setName("Neuer Scan");
    setThumbnail(NULL);

    if(uuid.isNull()) setUuid(QUuid::createUuid().toString().mid(1,36).toUpper());
    else setUuid(uuid);

    scansPath = scansDir;
    setScanPath(getUuid());
}

Scan::Scan(QString scansDir, QImage image, AbstractElement *parent) : AbstractElement(parent) {
    setName("Neuer Scan");
    setUuid(QUuid::createUuid().toString().mid(1,36).toUpper());
    scansPath = scansDir;
    setScanPath(getUuid());
}

Scan::~Scan(){
//    foreach (Textur *t, _texturen){
//        delete t;
//    }
//    _texturen.clear();
}

//Scan::Scan(const Scan &s){
//    qDebug() << "Kopierkonstruktor";
//    setName(s.getName());
//    setUuid(s.getUuid());
//    setScansPath(s.getS);
//    setScanPath(getUuid());
//}

void Scan::setScanPath(QString uuid){
    scanPath = QDir(scansPath + "/" + uuid);
}

void Scan::reset(){
    _rects.clear();
    _texturen.clear();
    setThumbnail(NULL);
}

void Scan::setFilename(QString fn){
    filename = fn;
}

void Scan::addRect(QRect r){
    _rects.append(r);
    //Textur zum Rect erzeugen
    Textur *t = new Textur(scanPath.absolutePath(), r);
    _texturen.append(t);
}

QRect *Scan::getRectAt(int index){
    QRect *r = &_rects[index];
    return r;
}

QList <QRect> Scan::getRects(){
    return _rects;
}

void Scan::setRects(QList<QRect> rects){
    _rects = rects;
}

QList<Textur*> Scan::getTextures(){
    //Checken, ob für alle Texturen Thumbnails vorhanden sind
    QList<QString> uuids;
    foreach(Textur *t, _texturen){
        uuids.append(t->getUuid());
        if (t->getThumbnail().isNull()){
//            QPixmap pix  = loadScanImage();
            t->makeThumbnail();
//            t->saveImageOrig(pix.copy(t->getRect()));
        }
    }

    cleanupScanDir(uuids);
    return _texturen;
}

void Scan::appendTexture(Textur *t){
    _texturen.append(t);
}

Textur *Scan::getTextureAt(int index){
    return _texturen[index];
}

QPixmap Scan::loadScanImage(){
    //Wenn Bild im Speicher, dieses zurückgeben
    if(!image.isNull()){
        QPixmap p = QPixmap::fromImage(image);
        return p;
    }else{
        //sonst laden;
        QPixmap pix;
        if(pix.load(scanPath.absolutePath() + "/original.jpg")) return pix;
        else return NULL;
    }
}

void Scan::makeThumbnail(){
    //zuerst Bild laden
    QPixmap pix(scanPath.absolutePath() + "/original.jpg");

    QImage textureImage = QImage(pix.toImage());
    textureImage = textureImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    QPainter textureAreas(&textureImage);

    //Transparente Bereiche zeichnen
    QColor fillColor(Qt::red);
    fillColor.setAlpha(50);

    textureAreas.setPen(QPen(Qt::red, 2));
    textureAreas.setBrush(QBrush(fillColor, Qt::SolidPattern));
    textureAreas.drawRects(getRects().toVector());

    //Thumbnail ertellen
    QPixmap thumb = QPixmap::fromImage(textureImage).scaledToWidth(300);
    //Thumbnail speichern
    if(!thumb.save(scanPath.absolutePath() + "/thumbnail.jpg")) QMessageBox::critical(NULL, "FEHLER", "FEEEEHLER!!", QMessageBox::Ok);
    setThumbnail(thumb);
}

QList< QString > Scan::getTextureNameList(){
    QList< QString > l;
    foreach(Textur *t, _texturen){
        l.append(t->getName());
    }
    return l;
}

bool Scan::saveScanImage(QPixmap pix){
    if(!checkScanPath()) return false;
    if(!pix.save(scanPath.absolutePath() + "/original.jpg", "JPG")) return false;
    return true;
}

bool Scan::saveScanImage(QImage image){
    if(!checkScanPath()) return false;
    if(!image.save(scanPath.absolutePath() + "/original.jpg", "JPG")) return false;
    return true;
}

bool Scan::saveScan(QPixmap pix, Scan *s){
    //Scan-Verzeichnis leeren (löschen und neu erstellen)
    if (!removeDir(scanPath.absolutePath())) return false;
    if (!checkScanPath()) return false;
    if (!saveScanImage(pix)) return false;


    _rects = s->getRects();
    _texturen = s->getTextures();

    //Texturen generieren
    for(int i = 0; i < _texturen.size(); i++){
        _texturen[i]->setRect(_rects.at(i));
        QRect rect = _texturen[i]->getRect();
        _texturen[i]->saveImageOrig(pix.copy(rect));
    }


    //Scan Thumbnail generieren
    makeThumbnail();
    return true;
}

void Scan::clearTextures(){
    _texturen.clear();
}

//Speichern
void Scan::saveToXMLStream(QXmlStreamWriter *xmlWriter){
    if(getUuid().isNull()) setUuid(QUuid::createUuid().toString().mid(1,36).toUpper());
    xmlWriter->writeStartElement("scan");
    // *** UUID
    xmlWriter->writeAttribute("uuid", getUuid());

    // *** Name (Beschreibung des Scans)
    xmlWriter->writeTextElement("name", getName());

    // *** Die Texturen schreiben
    xmlWriter->writeStartElement("textureList");

    //ToDo: Dirty Workaround: Zugriff via Kinder (eigentlich über Model)
    Gruppe *texturenGruppe = (Gruppe*)child(0);

    for(int i = 0; i < texturenGruppe->childCount(); i++){
        xmlWriter->writeStartElement("texture");
//        qDebug() << texturenGruppe->child(i)->getName();
//        texturenGruppe->child(i)->getName();
        ((Textur*)texturenGruppe->child(i))->saveToXMLStream(xmlWriter);
        xmlWriter->writeEndElement();

    }

    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();
}

//Laden
QString Scan::loadFromXMLStream(QXmlStreamReader *xmlReader){
    //Attribute des Scans holen
    QXmlStreamAttributes attr = xmlReader->attributes();
    setUuid(attr.value("uuid").toString());
    setScanPath(getUuid());

    //Gruppen leeren?

    while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "scan")) {
        // *** Name
        if(xmlReader->name() == "name") setName(xmlReader->readElementText());

        if(xmlReader->tokenType() == QXmlStreamReader::StartElement) {
            if(xmlReader->tokenType() == QXmlStreamReader::StartElement) {
                if(xmlReader->name() == "textureList"){
                    while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "textureList")) {
                        xmlReader->readNext();
                        if(xmlReader->tokenType() == QXmlStreamReader::StartElement) {
                            if(xmlReader->name() == "texture"){
                                Textur *t = new Textur(scanPath.absolutePath());
                                QString error = t->loadFromXMLStream(xmlReader);
                                if (!error.isNull()) return error;
//                                _rects.append(new QRect(*(t->getRect())));
                                t->makeThumbnail();
                                _texturen.append(t);

                            }
                        }
                    }
                }

                xmlReader->readNext();
            }
        }
        xmlReader->readNext();
    }
    makeThumbnail();
//    qDebug() << "thumbnail: " << getThumbnail().size();
    return NULL;
}

void Scan::loadScanThumbnail(){
    setThumbnail(QPixmap(scanPath.absolutePath() + "/thumbnail.jpg"));
}

void Scan::loadThumbnails(){
    loadScanThumbnail();
}

bool Scan::checkScanPath(){
    QDir dir(scanPath);
    if(!dir.exists()){
        if(!dir.mkpath(dir.absolutePath())) return false;
    }
    return true;
}

bool Scan::removeDir(QString dirName){
    bool result = true;
    QDir dir(dirName);
    if (dir.exists()) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result) return result;
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

void Scan::removeTextureAt(int index){
    _texturen.removeAt(index);
    _rects.removeAt(index);
}

bool Scan::cleanupScanDir(QList<QString> textureUuids){
    QDir dir(scanPath);
    if (dir.exists()) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs)){
            if(textureUuids.indexOf(info.fileName()) == -1) removeDir(info.absoluteFilePath());
        }
    }
}

void Scan::GLinit(QGLWidget *glw){
    foreach(Textur *t, _texturen){
        t->GLinit(glw);
    }
}

void Scan::GLdraw(QGLWidget *glw){
    if (childCount() > 0){
//        textureIndex = (ElementModel*)this-
    }

//    foreach(Textur *t, _texturen){
//        qDebug() << t->getName();
//        t->GLdraw(glw);
//    }
}

//AbstractElement *Scan::child(int row) const{
//    return static_cast<AbstractElement*>(_texturen.at(row));
//}

//int Scan::childCount() const {
//    return _texturen.count();
//}

int Scan::columnCount() const{
    return 1;
}

QVariant Scan::data(int column) const{
    switch(column){
        case 0:
            return getName();
    }
    return 0;
}

bool Scan::setData(int column, const QVariant &value){
    switch(column){
        case 0:
            setName(value.toString());
    }
    return true;
}

QImage Scan::getImage() {
    if(image.isNull()){
        image.load(scanPath.absolutePath() + "/original.jpg");
    }
    return image;

}
//Scan *Scan::copy(){
////    Scan *s = new Scan(*this);
//    Scan *s = new Scan("");
//    foreach(Textur *t, _texturen){
////        Textur *nt = new Textur(s->getScanPath(), QRect(200, 200, 300, 300), s);
////        s->appendChild(nt);
//                                    //        Textur *t_copy = t->copy();
////        t_copy->setParent(s);
////        s->appendTexture(t_copy);
//    }
//    return s;
//}
