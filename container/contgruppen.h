#ifndef CONTGRUPPEN_H
#define CONTGRUPPEN_H

#include <QList>
#include "elemente/gruppe.h"

class ContGruppen
{
public:
    ContGruppen();
    Gruppe* at(int i){ return gruppen.at(i); }
    QList<Gruppe*> *getGruppen() { return &gruppen; }
    void addGruppe(Gruppe *g) { gruppen.append(g); }

private:
    QList<Gruppe*> gruppen;
};

#endif // CONTGRUPPEN_H
