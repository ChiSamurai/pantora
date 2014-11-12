#ifndef CONTSCANS_H
#define CONTSCANS_H

#include <QObject>
#include <QList>
#include <QGLWidget>
#include <models/elementmodel.h>

#include "elemente/scan.h"

class ContScans{

public:
    ContScans();
    ~ContScans();

    void clear();

    int saveScan(Scan *);
    Scan *getScanAt(int);
    QList<Scan*> getScans();


    QString loadFromXML(QString dir);
    QString saveToXML(ElementModel* em);
    QString saveToXMLFile(QString dir);

    QString getScansDir();
    void setScansDir(QString s);

    QString getXmlFile();
    void setXmlFile(QString s);

    void GLinit(QGLWidget *glw);
    void GLdraw(QGLWidget *glw);

private:
    QList< Scan*> scans;
    QString scansDir;
    QString xmlFile;

    ElementModel *model;


    void saveImages();
    bool removeDir();
};

#endif // CONTSCANS_H
