#include "editmenu.h"

EditMenu::EditMenu(const QModelIndex &i, QWidget *parent) :
    QWidget(parent)
{
    index = i;
    model = (ElementModel*)i.model();
}
