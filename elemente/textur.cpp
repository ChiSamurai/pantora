#include "textur.h"

Textur::Textur(QString scanPath, AbstractElement *parent) : AbstractElement(parent){
    this->scanPath = scanPath;

    setTexturePath(getUuid());
    setName(tr("neue Zeichnung"));

//    einA = NULL;
//    einB = NULL;
    display = true;
    drawRotationAxis = false;
    drawClipPoints = false;
    drawLabel = true;
    typ = Planum;

    //Standardtransparez: 0
    alpha = 100;

    //Befundgrenzengruppe an Textur anhängen
    befundgrenzen = new Gruppe(tr("Befundgrenzen"), "", "", this);
    appendChild(befundgrenzen);
    setParent(parent);
}

Textur::Textur(QString scanPath, QRect r, AbstractElement *parent) : AbstractElement(parent){
    setUuid(QUuid::createUuid().toString().mid(1,36).toUpper());
    this->scanPath = scanPath;
    setTexturePath(getUuid());

    setName("neue Textur");
    rect = r;

//    einA = NULL;
//    einB = NULL;
    display = true;
    drawRotationAxis = false;
    drawClipPoints = false;
    drawLabel = true;
    typ = Planum;

    //ToDo: Transparenzen
    //Standardtransparez: 0
    alpha = 100;

    //Befundgrenzengruppe an Textur anhängen
    befundgrenzen = new Gruppe(tr("Befundgrenzen"), "", "", this);
    appendChild(befundgrenzen);
    setParent(parent);
}

Textur::~Textur(){
    glDeleteTextures(1, &tex);
//    delete einA;
//    delete einB;
}

void Textur::setTexturePath(QString uuid){
    texturePath = scanPath + "/" + uuid + "/";
}

void Textur::saveTexture(Textur *t){
//    //ToDo: filename != name
//    name = QString(filename);
    einA = t->einA;
    einB = t->einB;

    punktgruppen = t->punktgruppen;
    transPunktgruppen = t->transPunktgruppen;
    rahmen = t->rahmen;

    rect = t->rect;
}

void Textur::makeTextureImage(){
    QPixmap pix = imageTexture;
    //Zeichnen des edited_image
    QImage image_edit = pix.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
    QPainter edit(&image_edit);

    //Transparente Bereiche zeichnen
    edit.setCompositionMode(QPainter::CompositionMode_DestinationAtop);

    edit.setPen(QPen(Qt::transparent, 1));
    edit.setBrush(QBrush(Qt::transparent, Qt::SolidPattern));

    foreach(QPolygon p, transPunktgruppen){
        edit.drawPolygon(p);
    }

    if(rahmen.count() > 2){
        QPainterPath path;
        path.addRect(0, 0, image_edit.width(), image_edit.height());
        path.addPolygon(rahmen);
        path.closeSubpath();
        edit.drawPath(path);
    }
//    imageTexture = QPixmap::fromImage(image_edit);
    GLTexture = QImage(image_edit);
    //SVG speichern
    saveSVG(texturePath + "/befundgrenzen.svg");

//    imageTexture = QPixmap::fromImage(image_edit);
//    qDebug() << GLTexture.format();
}

QPixmap Textur::loadImageOrig(){
    return QPixmap(texturePath + "/original.jpg");
}

void Textur::makeThumbnail(){
    if(!checkTexturePath() || imageTexture.isNull()) return;
    setThumbnail(imageTexture.scaledToHeight(200, Qt::SmoothTransformation));
    getThumbnail().save(texturePath + "/thumbnail.jpg", "JPG");
}

//bool Textur::saveImageThumbnail(QPixmap pix){
//    if(!pix.save(texturePath + "/thumbnail.jpg", "JPG")) return false;
//    setThumbnail(pix);
//    return true;
//}

void Textur::loadTextureThumbnail(){
    setThumbnail(QPixmap(texturePath + "/thumbnail.jpg"));
}

void Textur::saveToXMLStream(QXmlStreamWriter *xmlWriter){

    //Wenn keine UUID, dann erstellen
    xmlWriter->writeAttribute("uuid", getUuid());

    // *** Anzeigen?
    xmlWriter->writeAttribute("display", display?"true":"false");

    // *** Name (Beschreibung der Textur)
    xmlWriter->writeTextElement("name", getName());

    // *** Typ (Planum oder Profil)
    QString ztyp;
    switch(typ){
    case 0:
        ztyp = QString("planum");
        break;
    case 1:
        ztyp = QString("profil");
        break;
    }

    xmlWriter->writeTextElement("type", ztyp);

    // *** Grabungskante
    xmlWriter->writeStartElement("border");
    rahmen.saveToXMLStream(xmlWriter);
    xmlWriter->writeEndElement();

    // *** Transparente Bereiche
    xmlWriter->writeStartElement("transparentAreas");
    foreach(Linie l, transPunktgruppen){
        l.saveToXMLStream(xmlWriter);
    }
    xmlWriter->writeEndElement();

    // *** Befundgrenzen
    //ToDo: Dirty Workaround: Zugriff via Kinder (eigentlich über Model)
    Gruppe *befundgrenzenGruppe = (Gruppe*)child(0);

    xmlWriter->writeStartElement("pointgroups");
    for(int i = 0; i < befundgrenzenGruppe->childCount(); i++){
        ((Linie*)befundgrenzenGruppe->child(i))->saveToXMLStream(xmlWriter);
    }
//    foreach(Linie l, punktgruppen){
//        l.saveToXMLStream(xmlWriter);
//    }
    xmlWriter->writeEndElement();

    // *** Ausschneidebereich
    QRect r = rect;
    xmlWriter->writeStartElement("areaRect");

    xmlWriter->writeStartElement("tl");
    xmlWriter->writeAttribute("x", QString::number(r.topLeft().x()));
    xmlWriter->writeAttribute("y", QString::number(r.topLeft().y()));
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("br");
    xmlWriter->writeAttribute("x", QString::number(r.bottomRight().x()));
    xmlWriter->writeAttribute("y", QString::number(r.bottomRight().y()));
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();

    // *** Einhängepunkte
    xmlWriter->writeStartElement("clipPoints");
    xmlWriter->writeStartElement("pointA");

    xmlWriter->writeStartElement("pointPixel");
    xmlWriter->writeAttribute("x", QString::number(einA.koords_pixel.x()));
    xmlWriter->writeAttribute("y", QString::number(einA.koords_pixel.y()));
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("pointGlobal");
    xmlWriter->writeAttribute("x", QString::number(einA.x()));
    xmlWriter->writeAttribute("y", QString::number(einA.y()));
    xmlWriter->writeAttribute("z", QString::number(einA.z()));
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();


    xmlWriter->writeStartElement("pointB");

    xmlWriter->writeStartElement("pointPixel");
    xmlWriter->writeAttribute("x", QString::number(einB.koords_pixel.x()));
    xmlWriter->writeAttribute("y", QString::number(einB.koords_pixel.y()));
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("pointGlobal");
    xmlWriter->writeAttribute("x", QString::number(einB.x()));
    xmlWriter->writeAttribute("y", QString::number(einB.y()));
    xmlWriter->writeAttribute("z", QString::number(einB.z()));
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();


    xmlWriter->writeEndElement();
}

QString Textur::loadFromXMLStream(QXmlStreamReader *xmlReader){
    QXmlStreamAttributes attr = xmlReader->attributes();
    // *** uuid
    setUuid(attr.value("uuid").toString());
    setTexturePath(getUuid());

    // *** display
    display = attr.value("display").toString() == "true"?true:false;

    //Sub-Elemente
    while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "texture")) {
        // *** Name
        if(xmlReader->name() == "name"){
            setName(xmlReader->readElementText());
        }
        // *** Typ
        if(xmlReader->name() == "type"){
            typ =  xmlReader->readElementText() == "planum"?Planum:Profil;
        }
        // *** Rahmen
        if(xmlReader->name() == "border"){
            while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "border")) {
                if(xmlReader->tokenType() == QXmlStreamReader::StartElement) {
                    if(xmlReader->name() == "line"){
                        QString error = rahmen.loadFromXMLStream(xmlReader);
                        if (!error.isNull()) return error;
                    }
                }
                xmlReader->readNext();
            }
        }
        // *** Transparente Bereiche
        if(xmlReader->name() == "transparentAreas"){
            while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "transparentAreas")) {
                if(xmlReader->tokenType() == QXmlStreamReader::StartElement) {
                    if(xmlReader->name() == "line"){
                        Linie l;
                        QString error = l.loadFromXMLStream(xmlReader);
                        if (!error.isNull()) return error;
                        transPunktgruppen.append(l);
                    }
                }
                xmlReader->readNext();
            }
        }
        // *** Linien
        if(xmlReader->name() == "pointgroups"){
            while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "pointgroups")) {
                if(xmlReader->tokenType() == QXmlStreamReader::StartElement) {
                    if(xmlReader->name() == "line"){
                        Linie *l = new Linie("", befundgrenzen);
                        befundgrenzen->appendChild(l);
                        QString error = l->loadFromXMLStream(xmlReader);
                        if (!error.isNull()) return error;
                        punktgruppen.append(*l);
                    }
                }
                xmlReader->readNext();
            }
        }
        // *** Ausschneidebereich
        if(xmlReader->name() == "areaRect"){
            while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "areaRect")) {
                QXmlStreamAttributes attr = xmlReader->attributes();
                xmlReader->readNext();
                if(xmlReader->name() == "tl"){
                    rect.setTopLeft(QPoint(attr.value("x").toString().toInt(), attr.value("y").toString().toInt()));
                }
                if(xmlReader->name() == "br") {
                    rect.setBottomRight(QPoint(attr.value("x").toString().toInt(), attr.value("y").toString().toInt()));
                }
                xmlReader->readNextStartElement();
            }
        }
        // *** Einhängepunkte
        if(xmlReader->name() == "clipPoints"){
            while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "clipPoints")) {
                if(xmlReader->tokenType() == QXmlStreamReader::StartElement){
                    if(xmlReader->name() == "pointA") {
                        while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "pointA")) {
                            if(xmlReader->tokenType() == QXmlStreamReader::StartElement){
                                if(xmlReader->name() == "pointPixel"){
                                    QXmlStreamAttributes attr = xmlReader->attributes();
                                    einA.koords_pixel.setX(attr.value("x").toString().toInt());
                                    einA.koords_pixel.setY(attr.value("y").toString().toInt());
                                }
                                if(xmlReader->name() == "pointGlobal"){
                                    QXmlStreamAttributes attr = xmlReader->attributes();
                                    einA.setX(attr.value("x").toString().toDouble());
                                    einA.setY(attr.value("y").toString().toDouble());
                                    einA.setZ(attr.value("z").toString().toDouble());
                                }
                            }
                            xmlReader->readNext();
                        }
                    }
                    if(xmlReader->name() == "pointB") {
                        while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "pointB")) {
                            if(xmlReader->tokenType() == QXmlStreamReader::StartElement){
                                if(xmlReader->name() == "pointPixel"){
                                    QXmlStreamAttributes attr = xmlReader->attributes();
                                    einB.koords_pixel.setX(attr.value("x").toString().toInt());
                                    einB.koords_pixel.setY(attr.value("y").toString().toInt());
                                }
                                if(xmlReader->name() == "pointGlobal"){
                                    QXmlStreamAttributes attr = xmlReader->attributes();
                                    einB.setX(attr.value("x").toString().toDouble());
                                    einB.setY(attr.value("y").toString().toDouble());
                                    einB.setZ(attr.value("z").toString().toDouble());
                                }
                            }
                            xmlReader->readNext();
                        }
                    }
                }
                xmlReader->readNext();
            }
        }
        xmlReader->readNext();
    }
    loadTextureThumbnail();
    imageTexture = getImageTexture();
    makeTextureImage();
//    loadImageOrig();
    calculateFactors();
    return NULL;
}

bool Textur::saveImageOrig(QPixmap pix){
    if(!checkTexturePath()) return false;
    if(!pix.save(texturePath + "/original.jpg", "JPG")) return false;
//    if(!saveImageTexture(pix)) return false;
    return true;
}

bool Textur::texImageFromScan(QImage scan){
    if(!checkTexturePath()) return false;

    QImage teximage = scan.copy(rect.x(), rect.y(), rect.width(), rect.height());
    imageTexture = QPixmap::fromImage(teximage);

    saveImageOrig(QPixmap::fromImage(teximage));
    saveImageTexture(QPixmap::fromImage(teximage));
    return true;
}

bool Textur::saveImageTexture(QPixmap pix){
    if(pix.isNull()){
        pix = loadImageOrig();
    }
    makeTextureImage();
    if(!checkTexturePath()) return false;
    if(!imageTexture.save(texturePath + "/texture.jpg", "JPG")) return false;
    makeThumbnail();

    return true;
}

bool Textur::checkTexturePath(){
    QDir dir(texturePath);
    if(!dir.exists()){
        if(!dir.mkpath(dir.absolutePath())) return false;
    }
    return true;
}

//Textur für GL vorbereiten etc.
void Textur::GLinit(QGLWidget *glw){

    check_gl_error();
    textureSize = GLTexture.size();

    calculateFactors();

//    img = img.mirrored(0, 1);

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_TEXTURE);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

//    glGenTextures( 1, &tex);
 //   glBindTexture( GL_TEXTURE_2D, tex);
//    glColor4f(1.0f,1.0f,1.0f, 1.0f);

//    check_gl_error();
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    check_gl_error();
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);

    check_gl_error();

    tex = glw->bindTexture(GLTexture, GL_TEXTURE_2D, GL_RGBA,
                            QGLContext::MipmapBindOption);

//    glTexImage2D( GL_TEXTURE_2D, 0, 3, GLTexture.width(), GLTexture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GLTexture.bits() );
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_TEXTURE_2D);
}

void Textur::GLdraw(QGLWidget *glw, bool xflip){

    //Einhängepunkte
    if(drawClipPoints){
        glPushMatrix();
         glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
         glPointSize(4);
         glBegin(GL_POINTS);
             glVertex3f(einA.x(), einA.y(), einA.z());
         glEnd();

        //Einhängegeraden
         glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
         glPointSize(2);
         glBegin(GL_LINES);
             glVertex3f(einA.x(), einA.y(), einA.z());
             glVertex3f(einB.x(), einB.y(), einB.z());
         glEnd();
         glw->renderText(einA.x() , einA.y() + 0.1f, einA.z(), "EinA (" + QString().number(einA.x()) + "|" + QString().number(einA.y()) + "|" + QString().number(einA.z()) + ")");
         glw->renderText(einB.x() , einB.y() + 0.1f, einB.z(), "EinB (" + QString().number(einB.x()) + "|" + QString().number(einB.y()) + "|" + QString().number(einB.z()) + ")");
        glPopMatrix();
    }

    // *** Zeichnen der Texturen
    glPushMatrix();
//        glDisable(GL_LIGHTING);

    glTranslatef(einA.x(), // zum Einhängepunkt bewegen
                  einA.y(),
                  einA.z());

    //Rotationsachsen zeichnen?
    if(drawRotationAxis){
        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
            glVertex3f(0, -1 , 0);
            glVertex3f(0, 1, 0);
        glEnd();
    }

    glRotatef(angleToY, 0, 1, 0);

    //Wenn Planum: 90° um x-Achse drehen
    if(typ == Planum){
        if(xflip) glRotatef(90, 1, 0, 0);
        else glRotatef(-90, 1, 0, 0);
    }
//
    glScalef(scaleFactor, scaleFactor, scaleFactor);
//

//        //Scanwinkel ausgleichen (Drehung um z-Achse)
//        if(typ == Planum) glRotatef(-scanAngle, 0, 0, 1);
//        else glRotatef(-scanAngle, 0, 1, 0);
    glRotatef(-scanAngle, 0, 0, 1);

    glTranslatef(-pixelOffset.x(), -pixelOffset.y(), 0.0f);

    //Textur nur Zeichnen, wenn Einhängepunkte definiert
    if(display && (einA != einB)){
        glDisable(GL_LIGHTING);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.1);
        glEnable(GL_TEXTURE_2D);

//        QColor c = QColor(255, 255, 255, alpha);
//        glw->qglColor(c);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        check_gl_error();

//        glw->renderText(0.0f, 0.0f, 0.0f, "(0|0)");
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, true);
//        glGenerateMipmap(GL_TEXTURE_2D);  //Generate mipmaps now!!!

        glw->drawTexture(QPoint(0.0, 0.0), tex, GL_TEXTURE_2D);
        check_gl_error();

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_ALPHA_TEST);
    }

    glDisable(GL_LIGHTING);
    // *** Linien zeichnen
    glTranslatef(0.0, textureSize.height(), 0.0);
    glRotatef(180, 1.0, 0.0, 0.0);
    for(int i = 0; i < befundgrenzen->childCount(); i++){
        Linie * l = (Linie*) befundgrenzen->child(i);
        l->GLdraw(glw);
    }
//        foreach(Linie l, punktgruppen){
//            l.GLdraw(glw);
//        }

    // *** Label zeichnen
    if(display && (einA != einB)){
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    //        glw->renderText(textureSize.width() + (0.1f / scaleFactor), textureSize.height(), 0.0f, name);
        glw->renderText(0.2f / scaleFactor, 0.2f / scaleFactor, 0.01, getName());
    }
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void Textur::GLupdate(QGLWidget *glw){
    //Textur löschen
//    glDeleteTextures(1, &tex);
    glw->deleteTexture(tex);
    GLinit(glw);
}

void Textur::calculateFactors(){
    //Vektoren zwischen beiden Punkten (pixel und global)
    QVector2D kv = QVector2D(einB.koords_pixel) - QVector2D(einA.koords_pixel);
//        einV = einB.koords_global - einA.koords_global;
    einV = einB - einA;


    // *** Faktoren für Skalierung berechnen
    qreal abstand_global = einV.length();
    qreal abstand_pixel = kv.length();
    scaleFactor = abstand_global / abstand_pixel;

    // *** Nullpunkt der Textur = EinA  - Pixel-Offset
    pixelOffset.setX(einA.koords_pixel.x());
    pixelOffset.setY(textureSize.height() - einA.koords_pixel.y());

    // *** Berechnung der Drehwinkel
    // ** Pixelkoordinaten
    // Ausgleich des schrägen Scans: z = 0, Drehung um Z-Achse
    // Nullpunkt auf ein-A verschieben (Vektor kv von einA nach einB)
    QLineF l1(QPointF(0, 0), QPointF(1, 0));
    QLineF l2(QPointF(0, 0), kv.toPointF());
    scanAngle = l1.angleTo(l2);

    //Winkel um y-Achse berechnen
    QLineF l(QPointF(0, 0), QPointF(einV.x(), einV.z()));
    angleToY = QLineF(QPointF(0, 0), QPointF(1, 0)).angleTo(l);
}

int Textur::columnCount() const{
    return 1;
}

QVariant Textur::data(int column) const{
    switch(column){
    case 0:
        return getName();
        break;
    }

    return 0;
}

bool Textur::setData(int column, const QVariant &value){
    switch(column){
        case 0:
            this->setName(value.toString());
    }
    return true;
}

Textur *Textur::copy(){
    Textur *t = new Textur(*this);
    //ToDo:: Einhängepunkt
//    t->setEinA(new Einhaengepunkt(*einA));
//    t->setEinB(new Einhaengepunkt(*einB));
    return t;
}

void Textur::setRect(QRect r){
     rect = r;
     //Setze mappingRect permanent
     if (mappingRect.isNull()){
         mappingRect = r;
     }
}

QImage Textur::getImage() {
    if(image.isNull()){
        image.load(texturePath + "/original.jpg");
    }
    return image;
}

void Textur::saveSVG(QString path){
    //Textur-Vollbild laden
    QPixmap pm = loadImageOrig();

    QSvgGenerator generator;
    generator.setFileName(path);
//    generator.setSize(pm.size());
    generator.setViewBox(QRect(0, 0, pm.size().width(), pm.size().height()));
    generator.setTitle(tr("Pantora - Befundgrenzen"));
    generator.setDescription(tr("Mit Pantora (www.pantora.de) generiertes Befundgrenzen-SVG"));

    QPainter painter;
    painter.begin(&generator);
    //Befundgrenzen zeichnen
    for(int i = 0; i < befundgrenzen->childCount(); i++){
        Linie *l = (Linie*)befundgrenzen->child(i);
        painter.setPen(QPen(l->getColor()));
        QPainterPath path;
        path.addPolygon(*l);
        if(l->closed) path.closeSubpath();
        painter.drawPath(path);
        //        qDebug() << l->getName();
    }
//    QWidget::paint(painter);
    painter.end();

}

void Textur::setAlpha(int a){
    alpha = a;
}
