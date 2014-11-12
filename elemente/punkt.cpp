/*
 * Punkt.cpp
 *
 *  Created on: 17.12.2009
 *      Author: samurai
 */

#include "punkt.h"

Punkt::Punkt(qreal x, qreal y, qreal z) :QVector3D(x, y, z){
    name = QString("Punkt");
    color = Qt::blue;
}

Punkt::~Punkt() {
    // TODO Auto-generated destructor stub
}

void Punkt::GLdraw(QGLWidget *glw){
    glPointSize(2.0);
    glBegin(GL_POINTS);
        glw->qglColor(color);
        GLvertex(glw);
    glEnd();
}

void Punkt::GLvertex(QGLWidget *glw){
    glVertex3d(x(), y(), z());
}

//float Punkt::winkel2Vektoren(QVector3D* v1, QVector3D* v2){
//	double zaehler =  QVector3D::dotProduct(*v1, *v2);
//	double nenner = v1->length() * v2->length();
////	double nenner = sqrt(VektorA[0]*VektorA[0] + VektorA[2] * VektorA[2]) * sqrt(VektorB[0]*VektorB[0] + VektorB[2] * VektorB[2]);
//	return acos(zaehler/nenner) * 180 / PI; //im Uhrzeigersinn
//}
//
//float *Punkt::vWinkel(Punkt* o1, Punkt* o2, Punkt* p1, Punkt* p2){
//	float winkel[2];
//	//Koordinaten Origin und Richung des Ausgangspunkts
//	//(Nullpunkt des lokalen Koordinatensystems und ein Punkt auf der z-Achse
//	double *origin1 = o1->getCoord(); //Nullpunkt des alten Koordinatensystems
//	double *origin2 = o2->getCoord(); //Punkt auf alter Y-Achse
//
//	double *punkt1 = p1->getCoord(); // Nullpunkt des neuen Koordsystems
//	double *punkt2 = p2->getCoord(); // Punkt auf neuer Y-Achse
//	double VektorA[3], VektorB[3];
//
//	// Vektor v (A->B) = A1-B1, A2-B2, A3-B3
//	VektorA[0] = origin1[0] - origin2[0];
//	VektorA[1] = origin1[1] - origin2[1]; //y wird eigentlich nicht gebraucht
//	VektorA[0] = origin1[2] - origin2[2];
//
//	VektorB[0] = punkt1[0] - punkt2[0];
//	VektorB[1] = punkt1[1] - punkt2[1]; //y wird eigentlich nicht gebraucht
//	VektorB[2] = punkt1[2] - punkt2[2];
//
//	//
//	double zaehler =  VektorA[0] * VektorB[0] + VektorA[2] * VektorB[2];
//	double nenner = sqrt(VektorA[0]*VektorA[0] + VektorA[2] * VektorA[2]) * sqrt(VektorB[0]*VektorB[0] + VektorB[2] * VektorB[2]);
////	qDebug() << "Zähler: " << zaehler;
////	qDebug() << "Nenner: " << nenner;
////	qDebug() << "cos Alpha: " << (zaehler/nenner);
////	qDebug() << "Alpha: " << acos(zaehler/nenner) * 180 / PI ;
//	winkel[0] =  acos(zaehler/nenner) * 180 / PI; //im Uhrzeigersinn
//	winkel[1] = 360 - winkel[0];
//	return winkel;
//}
//
//double Punkt::abstand(Punkt* p1, Punkt* p2){
//	QVector3D v1 = *p1->vektor3D;
//	QVector3D v2 = *p2->vektor3D;
//	QVector3D distVect = v1 - v2;
//	return (double)distVect.length();
//}
//
//double Punkt::abstand(QVector3D *p1, QVector3D *p2){
//	QVector3D distVect = *p1 - *p2;
//	return (double)distVect.length();
//}

//void Punkt::pointLabel(viewWindow *vw, QVector3D *punkt){
//	vw->renderText(punkt->x() + 0.05, punkt->y(), punkt->z(), "(" + QString::number(punkt->x()) + " | " + QString::number(punkt->y()) + " | " + QString::number(punkt->z()) + ")");
//}
