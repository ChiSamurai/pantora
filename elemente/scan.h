#ifndef SCAN_H
#define SCAN_H

#include <QtXml>
#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QDebug>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QUuid>
#include <QIcon>
#include <QMessageBox>
#include <QGLWidget>

#include "textur.h"
#include "elemente/gruppe.h"
#include "elemente/abstractelement.h"

class Scan : public AbstractElement
{
    Q_DECLARE_TR_FUNCTIONS(Scan)
    public:
        Scan(QString scansDir, QString uuid = QString(), AbstractElement *parent = 0);
        Scan(QString scansDir, QImage image, AbstractElement *parent = 0);

//        Scan(QString scansDir, , AbstractElement *parent = 0);
        ~Scan();
//        Scan(const Scan& s); // Kopierkonstruktor

        void reset();

        void setFilename(QString fn);

        QList <Textur*> getTextures();
        void appendTexture(Textur *);
        Textur *getTextureAt(int index);

        void removeTextureAt(int index);

        void setRects(QList<QRect> rects);
        QList <QRect> getRects();

        QRect *getRectAt(int index);

        QList< QString > getTextureNameList();

        bool saveScan(QPixmap pic, Scan *s);

        void addRect(QRect r);

        void saveToXMLStream(QXmlStreamWriter *xmlWriter);
        QString loadFromXMLStream(QXmlStreamReader *xmlReader);

        void loadThumbnails();
        void loadScanThumbnail();
        void makeThumbnail();

        QPixmap loadScanImage();
        bool saveScanImage(QPixmap);

        bool saveScanImage(QImage);

        void setScanPath(QString uuid);
        QString getScanPath(){ return scanPath.absolutePath(); }

        void setScansPath(QString path) { scansPath  = path; }
        QString getScansPath() { return scansPath; }

        void GLinit(QGLWidget *glw);
        void GLdraw(QGLWidget *glw);

        void setImage(QImage i) { image = i; }
        QImage getImage();

        // *** Item-spezifische Funktionen
//        AbstractElement *child(int row) const;
//        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        bool setData(int column, const QVariant &value);
        int row() const;

        type getElementType() const { return SCAN; }
//        Scan* copy();
        void clearTextures();

private:
        QImage image;

        QPersistentModelIndex textureIndex;

        QList< QRect > _rects;
        QList< Textur* > _texturen;

        QString filename;

        QDir scanPath;
        QString scansPath;

        void writeThumbnail();

        bool checkScanPath();

        bool removeDir(QString );

        bool cleanupScanDir(QList<QString> textureUuids); //Aufräumen des Scan-Directory (Temporäre Texturen entfernen)

};

#endif // SCAN_H
