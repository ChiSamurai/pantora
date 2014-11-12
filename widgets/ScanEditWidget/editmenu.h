#ifndef EDITMENU_H
#define EDITMENU_H

#include <QWidget>
#include <QModelIndex>

#include <models/elementmodel.h>

class EditMenu : public QWidget
{
    Q_OBJECT
public:
    explicit EditMenu(const QModelIndex &i, QWidget *parent = 0);

public slots:

protected:
    QModelIndex index;
    ElementModel *model;
private:
};

#endif // TEXTUREEDITMENU_H
