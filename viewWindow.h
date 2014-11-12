#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QGLWidget>
#include <QtGui>
#include <QtOpenGL>
#include <vector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QGLViewer/qglviewer.h>

#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>

#include "container/project.h"

using namespace qglviewer;

class viewWindow : public QGLViewer
{
Q_OBJECT
public:
    viewWindow(QWidget *parent = 0);

    void drawMainAxis(QVector3D);
    void drawInfoQuad();
    void drawRotationCross(QVector3D);
    void fiatLux();
    void setProject(Project *p);

public slots:
    void setCamPos(QVector3D);
    void setLookAtPoint(QVector3D);

signals:
    void lookAtPointChanged(QVector3D);
    void camPosChanged(QVector3D);

protected:
    void init();
    void draw();

private:
    Project *project;
    int Rot[3];

    QVector3D eyeCoords, axisCoords, lookAtPoint, cameraPos;

    GLenum errCode;
    const GLubyte *errString;

//    void draw();

    QColor qtGreen, qtPurple, qtBackgroundColor;

    float radius;
    GLfloat LightPosition[4];

    int windowWidth, windowHeight;

    void drawRaster(QVector3D start, float lengthx, float lengthy, float pace);

    bool isDragging();

signals:
};

#endif // VIEWWINDOW_H
