#ifndef Punktgruppe_H_
#define Punktgruppe_H_

#include <QList>
#include <QDebug>
#include <QGLWidget>

#include "punkt.h"
#include "container/contpunkte.h"

class Punktgruppe {
    public:
        enum type {CLOUD, LINE, LINE_C};

        Punktgruppe();
        virtual ~Punktgruppe();

    private:
        static QColor defaultColor;
        ContPunkte punkte;

        bool drawPoints;
        bool highlight;

        type typ;
        QColor color;
        QString label;

    public:
        void addPoint(Punkt *p) { punkte.addPoint(p); }
        Punkt *getPointAt(int index) { return punkte.getPointAt(index); }
        void removePointAt(int index) { punkte.deletePoint(index); }

        void GLdraw(QGLWidget *glw);

        void setType(int t) { typ = (type) t; }
        unsigned int getTyp() { return (int)typ; }

        void setColor(QColor c) { color = c; }
        QColor getColor(){ return color; }

        void setLabel(QString l) { label = l;}
        QString getLabel() { return label; }
        void setHighlight(bool h) { highlight = h;}


};

#endif /* Punktgruppe_H_ */
