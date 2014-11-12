#ifndef CONTPUNKTGRUPPEN_H_
#define CONTPUNKTGRUPPEN_H_

#include <QList>
#include <QDebug>
#include <QGLWidget>
#include "elemente/punktgruppe.h"

class ContPunktgruppen {
    private:
        bool highlight;
        QList<Punktgruppe*> punktgruppen;
    public:
        ContPunktgruppen();
        virtual ~ContPunktgruppen();
        void clear();

        void addPunktgruppe(Punktgruppe* pg) { punktgruppen.append(pg); };
        void removePunktgruppe(int index) { punktgruppen.removeAt(index); };
        Punktgruppe* getPunktgruppeAt(int index) { return punktgruppen.at(index); };

        void GLdraw(QGLWidget *glw);
        void setHighlight(bool hl) { highlight = hl; };
};

#endif /* CONTPUNKTGRUPPEN_H_ */
