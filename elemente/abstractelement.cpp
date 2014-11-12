#include "abstractelement.h"

AbstractElement::AbstractElement(AbstractElement *parent)
{
    parentItem = parent;
    uuid = QUuid::createUuid().toString().mid(1,36).toUpper();
    setName("Neues Element");
    setDescription("Neues Element");
}

AbstractElement::~AbstractElement(){
}

QIcon AbstractElement::getThumbnailIcon() const {
    if(thumbnail.isNull()) return  QIcon();
    //ToDo:: StandardIcon
    else return QIcon(thumbnail);
}

int AbstractElement::row() const{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<AbstractElement*>(this));
    return 0;
}

AbstractElement *AbstractElement::child(int row) const{
    if (row < childItems.count()){
        return childItems.at(row);
    }
    return 0;
}

int AbstractElement::childCount() const{
    return childItems.count();
}

void AbstractElement::appendChild(AbstractElement *item)
{
    childItems.append(item);
}


bool AbstractElement::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row){
        delete childItems.takeAt(position);
    }
    return true;
}

//bool AbstractElement::removeColumns(int position, int columns)
//{
//    if (position < 0 || position + columns > itemData.size())
//        return false;

//    for (int column = 0; column < columns; ++column)
//        itemData.remove(position);

//    foreach (AbstractElement *child, childItems)
//        child->removeColumns(position, columns);

//    return true;
//}
