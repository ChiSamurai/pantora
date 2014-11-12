#include "linie.h"

//Linie::Linie(AbstractElement *parent, QString uuid) : AbstractElement(parent), QPolygon(){
//    setUuid(QUuid::createUuid().toString().mid(1,36).toUpper());
//    closed = false;
//    drawPoints = false;
//    setName(tr("neue Befundgrenze"));

//    setParent(parent);
//}

Linie::Linie(QString uuid, AbstractElement *parent) :AbstractElement(parent), QPolygon(){
    if (uuid.isNull()) setUuid(QUuid::createUuid().toString().mid(1,36).toUpper());
    closed = false;
    drawPoints = false;
    setName(tr("neue Befundgrenze"));
    setParent(parent);
    color = QColor(Qt::blue);
    display = true;

}

void Linie::copyFrom(Linie *l){
    setName(l->getName());
    closed = l->closed;
    color = l->getColor();
    this->clear();
    foreach(QPoint p, *l) this->append(p);
}

void Linie::saveToXMLStream(QXmlStreamWriter *xmlWriter){
    if(uuid.isNull()) uuid = QUuid::createUuid().toString().mid(1,36).toUpper();
    if(size() > 0){
        xmlWriter->writeStartElement("line");
        xmlWriter->writeAttribute("uuid", uuid);
        xmlWriter->writeAttribute("closed", closed?"true":"false");
        xmlWriter->writeTextElement("name", getName());
        xmlWriter->writeTextElement("color", getColor().name());

        xmlWriter->writeStartElement("pointList");
        for(int i = 0; i < size(); i++){
            QPoint p = at(i);
            xmlWriter->writeStartElement("point");
            xmlWriter->writeAttribute("x", QString::number(p.x()));
            xmlWriter->writeAttribute("y", QString::number(p.y()));
            xmlWriter->writeEndElement();
        }
        xmlWriter->writeEndElement();

        xmlWriter->writeEndElement();
    }
}

QString Linie::loadFromXMLStream(QXmlStreamReader *xmlReader){
    QXmlStreamAttributes attr = xmlReader->attributes();
    uuid = QUuid(attr.value("uuid").toString());
    closed = attr.value("closed").toString() == "true"?true:false;

    while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "line")) {
        if(xmlReader->tokenType() == QXmlStreamReader::StartElement) {
            //Name lesen
            if(xmlReader->name() == "name"){
                xmlReader->readNext();
                setName(xmlReader->text().toString());
            }
            if(xmlReader->name() == "color"){
                xmlReader->readNext();
                QColor m;
                m.setNamedColor(xmlReader->text().toString());
                setColor(m);
            }

            //Punktliste lesen
            // <point x="200" y="200"/>
            if(xmlReader->name() == "pointList") {
                while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "pointList")) {
                    xmlReader->readNext();
                    if(xmlReader->tokenType() == QXmlStreamReader::StartElement) {
                        if(xmlReader->name() == "point"){
                            QXmlStreamAttributes pattr = xmlReader->attributes();
                            append(QPoint(pattr.value("x").toString().toInt(), pattr.value("y").toString().toInt()));
                        }
                    }
                }
            }
        }
        xmlReader->readNext();
    }
    return NULL;
}

void Linie::GLdraw(QGLWidget *glw){
    if(display){
        GLfloat *lw = new GLfloat(1.0);
        glGetFloatv(GL_LINE_WIDTH, lw);

        glw->qglColor(color);
        glLineWidth(2);
        if(closed) glBegin(GL_LINE_LOOP);
        else glBegin(GL_LINE_STRIP);
        for(int i = 0; i < size(); i++){
            QPoint q = at(i);
            glVertex3f(q.x(), q.y(), 0);
        }
        glEnd();
    //    glLineWidth(lw);
        glLineWidth(*lw);

        if(drawPoints){
            glPointSize(4);
            //Punkte nachzeichnen
            glBegin(GL_POINTS);
            for(int i = 0; i < size(); i++){
                QPoint q = at(i);
                glVertex3f(q.x(), q.y(), 4);
            }
            glEnd();
        }
    }
}
int Linie::columnCount() const{
    return 1;
}

QVariant Linie::data(int column) const{
    switch(column){
    case 0:
        return getName();
        break;
    }

    return 0;
}

bool Linie::setData(int column, const QVariant &value){
    switch(column){
        case 0:
            this->setName(value.toString());
    }
    return true;
}
