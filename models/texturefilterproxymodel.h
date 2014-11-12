#ifndef TEXTUREFILTERPROXYMODEL_H
#define TEXTUREFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "elementmodel.h"
#include "elemente/abstractelement.h"

class TextureFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TextureFilterProxyModel(QObject *parent = 0);
    bool filterAcceptsRow(int source_row, const QModelIndex &index) const;
    
signals:
    
public slots:
    
};

#endif // TEXTUREFILTERPROXYMODEL_H
