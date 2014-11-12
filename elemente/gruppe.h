#ifndef GRUPPE_H
#define GRUPPE_H

#include <QUuid>
#include <QObject>

#include "elemente/punktgruppe.h"
#include "elemente/abstractelement.h"
#include "textur.h"

class Gruppe : public AbstractElement
{
//    Q_OBJECT
    Q_DECLARE_TR_FUNCTIONS(Gruppe)

public:

    Gruppe(AbstractElement *parent = 0);
    Gruppe(QString name, QString description, QString uuid = "", AbstractElement *parent = 0);
    ~Gruppe();

    int columnCount() const;
    QVariant data(int column) const;
    bool setData(int column, const QVariant &value);

    type getElementType() const{ return GRUPPE; }

private:

};

#endif // GRUPPE_H
