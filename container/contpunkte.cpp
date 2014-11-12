#include "contpunkte.h"

//Konstruktor
ContPunkte::ContPunkte(){
}

//Neuen Punkt zur Punktesammlung hinzufügen und id zurückgeben
int ContPunkte::addPoint(Punkt *p){
    punkte.append(p);
    return (punkte.count() - 1);
}

//Punkte zeichnen
void ContPunkte::GLdraw(QGLWidget *glw){
    foreach(Punkt *p, punkte) p->GLdraw(glw);
}
