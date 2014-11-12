#ifndef ELEMENTMODEL_H
#define ELEMENTMODEL_H

#include <QAbstractItemModel>
#include "elemente/abstractelement.h"
#include "elemente/scan.h"
#include "elemente/textur.h"
#include "elemente/gruppe.h"

class ElementModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ElementModel(QObject *parent = 0);
    ~ElementModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                      int role = Qt::EditRole);
    bool removeRows(int row, int count, const QModelIndex &parent);

//    bool insertColumns(int column, int count, const QModelIndex &parent);
//    bool insertRows(int row, int count, const QModelIndex &parent);

//    bool insertChild(AbstractElement *childElement, QModelIndex &parentIndex);
//    bool appendElement(QList<QString> s, AbstractElement::type t, AbstractElement *parentElement = 0);
    bool insertChild(AbstractElement *childElement, const QModelIndex &parentIndex = QModelIndex());
//    bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
    AbstractElement *getItem(const QModelIndex &index = QModelIndex()) const;

private:
//    void setupModelData(const QStringList &lines, AbstractElement *parent);
    AbstractElement *rootItem;

};

#endif // ELEMENTMODEL_H
