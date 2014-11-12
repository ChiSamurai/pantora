#include "gruppe.h"

Gruppe::Gruppe(AbstractElement *parent) : AbstractElement(parent)
{
    setUuid(QUuid::createUuid().toString().mid(1,36).toUpper());
    setName(tr("neue Gruppe"));
    setDescription(tr("neue Gruppe"));
    setParent(parent);
}

Gruppe::Gruppe(QString name, QString description, QString uuid, AbstractElement* parent) : AbstractElement (parent){
    if (uuid.isNull()) setUuid(QUuid::createUuid().toString().mid(1,36).toUpper());
    setUuid(uuid);
    setName(name);
    setDescription(description);
    setParent(parent);
}

Gruppe::~Gruppe(){
}

int Gruppe::columnCount() const{
    return 1;
}

QVariant Gruppe::data(int column) const{
    if(column > columnCount()) return 0;
    switch(column){
    case 0:
        return getName();
        break;
//    case 1:
//        return getDescription();
//        break;
    }
}

bool Gruppe::setData(int column, const QVariant &value){
    switch(column){
        case 0:
            setName(value.toString());
            break;
    }
    return true;
}
