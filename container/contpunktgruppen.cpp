#include "container/contpunktgruppen.h"

ContPunktgruppen::ContPunktgruppen() {
    highlight = false;
    // TODO Auto-generated constructor stub
}

ContPunktgruppen::~ContPunktgruppen() {
    // TODO Auto-generated destructor stub
}

void ContPunktgruppen::GLdraw(QGLWidget *glw){
    foreach(Punktgruppe *pg, punktgruppen) pg->GLdraw(glw);
}

void ContPunktgruppen::clear(){
    foreach(Punktgruppe *pg, punktgruppen){
        delete pg;
    }
    punktgruppen.clear();
}
