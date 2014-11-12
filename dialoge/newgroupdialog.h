#ifndef NEWGROUPDIALOG_H
#define NEWGROUPDIALOG_H

#include <QDialog>
#include <QColor>
#include <QList>
#include <QColorDialog>

#include "elemente/gruppentyp.h"

namespace Ui {
    class NewGroupDialog;
}

class NewGroupDialog : public QDialog {
    Q_OBJECT
public:
    NewGroupDialog(QList<GruppenTyp*>, QWidget *parent = 0);
    ~NewGroupDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::NewGroupDialog *ui;
    QList<GruppenTyp*> typen;

private slots:
    void on_ColorButton_clicked();
    void on_addButton_clicked();

signals:
    void addNewGroup(QString name);
};

#endif // NEWGROUPDIALOG_H
