#ifndef TEXTUR_H
#define TEXTUR_H

#include <QtCore>
#include <QGLWidget>
#include <QObject>
#include <QImage>
#include <QList>
#include <QPixmap>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QUuid>
#include <QDir>
#include <QIcon>
#include <QVector2D>
#include <QSvgGenerator>

#include "glerror.h"

#include "linie.h"
#include "einhaengepunkt.h"
#include "elemente/abstractelement.h"
#include "elemente/gruppe.h"

class Gruppe;

class Textur : public AbstractElement{
    Q_DECLARE_TR_FUNCTIONS(Scan)

    public:
        enum Typ {Planum, Profil};

        Textur(QString scanPath, AbstractElement *parent = 0);
        Textur(QString scanPath, QRect r, AbstractElement *parent = 0);
        ~Textur();

        void setTexturePath(QString );

//        void c(Textur *t);

        void setDisplay(bool b){ display = b; }
        bool getDisplay() { return display; }

        QList<GLuint> textureIDs;
        QImage GL_formatted_image;

        void updateTextures();

        bool texImageFromScan(QImage scan);

        QPixmap loadImageOrig();
        bool saveImageOrig(QPixmap p);

        bool saveImageTexture(QPixmap pix = NULL);
        QPixmap getImageTexture() { return QPixmap(texturePath + "/texture.jpg"); }

        void makeThumbnail();
//        bool saveImageThumbnail(QPixmap pix);
        void loadTextureThumbnail();

        void removePunktgruppe(int index) { punktgruppen.removeAt(index); }
        QList<Linie> *getPunktgruppen() { return &punktgruppen; }

        void removeTransPunktgruppe(int index) { transPunktgruppen.removeAt(index); }
        QList<Linie> *getTransPunktgruppen() { return &transPunktgruppen; }
        void setTransPuktgruppen(QList<Linie> l) { transPunktgruppen = l; }


        void setEinA(Einhaengepunkt e) { einA = e;}
        Einhaengepunkt getEinA() { return einA; }

        void setEinB(Einhaengepunkt e) { einB = e;}
        Einhaengepunkt getEinB() { return einB; }

        void setRahmen(Linie l) { rahmen = l; }
        Linie getRahmen() { return rahmen; }

        void makeTextureImage();

        void saveTexture(Textur *t);

//        void setFilename(QString);
//        QString *getFilename();

        void setRect(QRect r);
        QRect getRect() { return rect; }

        void saveToXMLStream(QXmlStreamWriter *xmlWriter);
        QString loadFromXMLStream(QXmlStreamReader *xmlReader);

        void saveSVG(QString path);

//        void saveImages(QString projectDir);

        int getTyp() { return (int)typ; }
        void setTyp(int t) { typ = (Typ)t; }

        //GL Funktionen
        void calculateFactors();

        void GLinit(QGLWidget *glw);
        void GLupdate(QGLWidget *glw);
        void GLdraw(QGLWidget *glw, bool xflip = false);

        Textur *copy();

        QImage getImage();

        // *** Item-spezifische Funktionen
//        AbstractElement *child(int row) const;
        int columnCount() const;
        QVariant data(int column) const;
        bool setData(int column, const QVariant &value);
//        int row() const;
        type getElementType() const { return TEXTUR; }

        int getAlpha() { return alpha; }
        void setAlpha(int a);

    private:
        bool checkTexturePath();

        Typ typ;
        bool display;
        int alpha;

        QString texturePath;
        QString scanPath;

        QPixmap imageTexture;

        QImage GLTexture, image;
        GLuint tex;

        QList< Linie > punktgruppen;
        QList< Linie > transPunktgruppen;

        QRect rect;
        QRect mappingRect;

        Linie rahmen;
        Einhaengepunkt einA;
        Einhaengepunkt einB;

        QVector3D einV;
//        QVector3D nullNew;
        QVector2D pixelOffset;
        QSize textureSize;

        qreal angleToX, angleToY, angleToZ, scanAngle; //scanAngle = Ausgleich eines schiefen Scans

        qreal scaleFactor;

        bool drawRotationAxis, drawClipPoints, drawLabel;

        //Gruppen für sichtbare Subelemente
        Gruppe *befundgrenzen;

};

#endif // TEXTUR_H
