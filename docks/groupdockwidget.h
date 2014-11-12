#ifndef GROUPDOCKWIDGET_H
#define GROUPDOCKWIDGET_H

#include <QDockWidget>
#include <QDebug>
#include <QMenu>
#include <QSortFilterProxyModel>

#include "dialoge/newgroupdialog.h"

#include "elemente/gruppe.h"
#include "container/project.h"

#include "models/elementmodel.h"
#include "models/texturefilterproxymodel.h"

//#include "models/gruppemodelitem.h"

namespace Ui {
    class GroupDockWidget;
}

class GroupDockWidget : public QDockWidget {
    Q_OBJECT
public:
    GroupDockWidget(QWidget *parent = 0);
    ~GroupDockWidget();

    void setProject(Project *p);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::GroupDockWidget *ui;
    Project* project;

    ElementModel *model_elemente;

    QModelIndex scanParentIndex;
    Gruppe *scanGruppe, *rootGruppe;


private slots:
    void newGroupDialog();
    void showContextMenu(const QPoint &p);

    void addNewGroup(QString name);
    void deleteGroup();
    void on_elementeView_doubleClicked(const QModelIndex &index);
    void on_elementeView_clicked(const QModelIndex &index);
    void on_display_toggled(bool checked);


    void on_gruppenView_clicked(const QModelIndex &index);

signals:
    void updateGl();
};

#endif // GROUPDOCKWIDGET_H
