#ifndef LINIE_H
#define LINIE_H

#include <QtCore>
#include <QPolygon>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QGLWidget>
#include <QUuid>
#include <QDebug>
#include <QColor>

#include "abstractelement.h"

class Linie : public AbstractElement, public QPolygon {
    Q_DECLARE_TR_FUNCTIONS(Linie)

public:
//    explicit Linie(AbstractElement *parent = 0);
    Linie(QString uuid = "", AbstractElement *parent = 0);
//    QString name;
    void saveToXMLStream(QXmlStreamWriter *xmlWriter);
    QString loadFromXMLStream(QXmlStreamReader *xmlReader);
    bool closed;
    void copyFrom(Linie *l);

    void GLdraw(QGLWidget *glw);

    int columnCount() const;
    QVariant data(int column) const;
    bool setData(int column, const QVariant &value);
    type getElementType() const { return BEFUNDGRENZE; }

    QColor getColor(){ return color; }
    void setColor(QColor c){ color = c; }

    bool getDisplay() { return display; }
    void setDisplay(bool d) { display = d; }


private:
    bool display;
    QColor color;
    QString uuid;
    bool drawPoints;
};

#endif // LINIE_H
