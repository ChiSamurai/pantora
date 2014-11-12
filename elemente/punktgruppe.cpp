#include "punktgruppe.h"

QColor Punktgruppe::defaultColor = QColor(255, 0, 0, 255);

Punktgruppe::Punktgruppe() {
    drawPoints = false;
    highlight = false;
    typ = CLOUD;
    color = defaultColor;
}

Punktgruppe::~Punktgruppe() {
	// TODO Auto-generated destructor stub
}

void Punktgruppe::GLdraw(QGLWidget *glw){
    glPushMatrix();
    glw->qglColor(color);
    //Welcher Typ?
    if(typ == LINE){
        if(highlight) glLineWidth(2.0);
        else glLineWidth(1.0);
        glBegin(GL_LINE_STRIP);
    }
    else if (typ == LINE_C){
        if(highlight) glLineWidth(2.0);
        else glLineWidth(1.0);
        glBegin(GL_LINE_LOOP);
    }
    else if (typ == CLOUD){
        glPointSize(2.0);
        glBegin(GL_POINTS);
    }
    //Vertex Out der Punkte
    foreach(Punkt *p, *punkte.getPoints()) p->GLvertex(glw);
    glEnd();

    //Punkte nachzeichnen?
    if (this->drawPoints){
        glPointSize(2.0);
        glDisable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
        glDisable(GL_POINT_SMOOTH);

        glw->qglColor(color);
        foreach(Punkt* p, *punkte.getPoints()) p->GLvertex(glw);
        glEnd();

        glEnable(GL_POINT_SMOOTH);
    }
    glPopMatrix();
}
