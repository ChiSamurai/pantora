#ifndef CONTPUNKTE_H
#define CONTPUNKTE_H

#include <QDebug>
#include <QList>
#include <QGLWidget>
//#include <QVariant>
//#include <GL/gl.h>

#include "elemente/punkt.h"

class ContPunkte {
private:
    QList<Punkt*> punkte;

public:
    ContPunkte();
    int addPoint(Punkt *p);

    void deletePoint(int index) { punkte.removeAt(index); }
    QList<Punkt*> *getPoints() { return &punkte; };
    Punkt *getPointAt(int index) {return punkte.at(index); };

    void GLdraw(QGLWidget *glw);

    int size();

};

#endif // CONTPUNKTE_H
