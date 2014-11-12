#ifndef MENUSPLIT_H
#define MENUSPLIT_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QModelIndex>
#include <QDataWidgetMapper>

#include "models/elementmodel.h"

namespace Ui {
    class MenuSplit;
}

class MenuSplit : public QWidget {
    Q_OBJECT
public:
    MenuSplit(const QModelIndex &i, QWidget *parent = 0);
    ~MenuSplit();
//    void fillList(QList <QString> *list);
    void setName(QString);
    QString getName();
    void setDebugViewModel(ElementModel*);

public slots:
//    void addRect(QString, QRect);

private slots:
    void on_deleteArea_clicked();
    void changeModus(int modusIndex);
//    void listItemChanged();

    void on_rectView_clicked(const QModelIndex &index);

signals:
    void subModusChanged(int modusIndex);

    void textureActivated(QModelIndex &index);

    //DIRTY
    void deleteTexture(QPersistentModelIndex);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MenuSplit *ui;
    ElementModel *model;
    QModelIndex texturesIndex;

    //DIRTY
    int initialRows;

//    void clearItems();
};

#endif // MENUSPLIT_H
