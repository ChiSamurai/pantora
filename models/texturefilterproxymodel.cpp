#include "texturefilterproxymodel.h"

TextureFilterProxyModel::TextureFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool TextureFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &index) const
{
//    qDebug() << source_row;
    if (index.isValid()) {
        ElementModel *model = (ElementModel*)(sourceModel());

        if (model){
            AbstractElement *item = model->getItem(index);
            qDebug() << item->getName();
            return TextureFilterProxyModel::filterAcceptsRow(source_row, index);
            if (item->getElementType() == AbstractElement::TEXTUR) qDebug() << "hier";
////                if (item and item->child(source_row)->hasChildren())
////                    return true;
        }
//        return true;
    }
//    return true;

////    if (index.isValid())
////    {
////        ElementModel *model = (ElementModel*)(sourceModel());

////        if (model)
////        {
////            AbstractElement *item = model->getItem(index);
////            qDebug() << item->getName();

////            if (item and item->child(source_row)->hasChildren())
////                return true;
////        }
////    }
//////    else if (source_row == 1)
//////        return true;
////    else
////    else if (source_row < 4) return true;

////    return false;
    return false;
}
