#include "elementmodel.h"

ElementModel::ElementModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    Gruppe *g = new Gruppe("RootGruppe", "", "");
    rootItem = g;
}

ElementModel::~ElementModel()
{
    delete rootItem;
}

int ElementModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<AbstractElement*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant ElementModel::data(const QModelIndex &index, int role) const
{
//    qDebug() << role << " ==? " << Qt::DisplayRole;
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::DecorationRole && role != Qt::EditRole)
        return QVariant();

    AbstractElement *item = static_cast<AbstractElement*>(index.internalPointer());

    if (role == Qt::DecorationRole){
        return item->getThumbnailIcon();
    }
    else if(role == Qt::DisplayRole ){
        return item->data(index.column());
    }
    else if(role == Qt::EditRole ){
        return item->data(index.column());
    }

}

bool ElementModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role != Qt::EditRole)
        return false;

    AbstractElement *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

Qt::ItemFlags ElementModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ElementModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//QModelIndex ElementModel::index(int row, int column, const QModelIndex &parent) const
//{
//    if (parent.isValid() && parent.column() != 0)
//        return QModelIndex();

//    AbstractElement *parentItem = getItem(parent);

//    AbstractElement *childItem = parentItem->child(row);
//    if (childItem)
//        return createIndex(row, column, childItem);
//    else
//        return QModelIndex();
//}


QModelIndex ElementModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    AbstractElement *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<AbstractElement*>(parent.internalPointer());

    AbstractElement *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ElementModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

//    AbstractElement *childItem = static_cast<AbstractElement*>(index.internalPointer());
    AbstractElement *childItem = getItem(index);
    AbstractElement *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ElementModel::rowCount(const QModelIndex &parent) const
{
    AbstractElement *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<AbstractElement*>(parent.internalPointer());

    return parentItem->childCount();
}

//bool ElementModel::insertColumns(int position, int columns, const QModelIndex &parent)
//{
//    bool success;

//    beginInsertColumns(parent, position, position + columns - 1);
//    success = rootItem->insertColumns(position, columns);
//    endInsertColumns();

//    return success;
//}

//bool ElementModel::insertRows(int position, int rows, const QModelIndex &parent)
//{
//    AbstractElement *parentItem = getItem(parent);
//    bool success;

//    beginInsertRows(parent, position, position + rows - 1);
//    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
//    endInsertRows();

//    return success;
//}

AbstractElement *ElementModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        AbstractElement *item = static_cast<AbstractElement*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}


bool ElementModel::insertChild(AbstractElement *childElement, const QModelIndex &parentIndex){

    AbstractElement *parentElement;

    QModelIndex parent;

    if(!parentIndex.isValid()){
        parent = QModelIndex();
        childElement->setParent(rootItem);
        parentElement = rootItem;
    }
    else {
        parent = parentIndex;
        parentElement = static_cast<AbstractElement*>(parent.internalPointer());
        childElement->setParent(parentElement);
    }


    beginInsertRows(parent, parentElement->childCount(), parentElement->childCount() + 1);
    parentElement->appendChild(childElement);
    endInsertRows();
    return true;
}

//bool ElementModel::appendElement(QList<QString> s, AbstractElement::type t, AbstractElement *parentElement){
//    if (parentElement == 0) parentElement = rootItem;
////    qDebug() << static_cast<AbstractElement::type>(t);
//    switch(t){
//    case AbstractElement::GRUPPE:
//        parentElement->appendChild(new Gruppe(s.at(0), s.at(1), "UUID", parentElement));
//        break;
//    case AbstractElement::SCAN:
//        parentElement->appendChild(new Scan("asd", parentElement));
//        break;
//    case AbstractElement::TEXTUR:
//        parentElement->appendChild(new Textur("asd", parentElement));
//        break;
//    }
//}

bool ElementModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    AbstractElement *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}
