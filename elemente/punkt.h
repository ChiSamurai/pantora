#ifndef Punkt_H_
#define Punkt_H_

#include <QColor>
#include <QString>
#include <QList>
#include <QDebug>
#include <QGLWidget>
#include <QVector3D>

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <iostream>
#include <math.h>

#define PI 3.14159

//using namespace std;

class Punkt : QVector3D {
    public:
//        Punkt(double x, double y, double z);
        Punkt(qreal x, qreal y, qreal z);
        ~Punkt();

        void setColor(QColor c) {color = c; };
        QColor getColor() {return color;};

        void setName(QString n) {name = n; };
        QString getName() { return name; };

        void GLdraw(QGLWidget *glw);
        void GLvertex(QGLWidget *glw);


//        static float *vWinkel(Punkt*, Punkt*, Punkt*, Punkt*);
//        static float winkel2Vektoren(QVector3D*, QVector3D*);
//
//        static double abstand(Punkt*, Punkt*);
//        static double abstand(QVector3D*, QVector3D*);

//        static void pointLabel(viewWindow *vw, QVector3D *punkt);

    private:
        QVector3D *vektor_gemessen;
        QString name;
        QColor color;
};

#endif /* Punkt_H_ */
