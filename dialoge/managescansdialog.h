#ifndef MANAGESCANSDIALOG_H
#define MANAGESCANSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTreeWidgetItem>
#include <QGLWidget>

#include "container/contscans.h"
#include "widgets/ScanEditWidget/scaneditwidget.h"
#include "widgets/ScanEditWidget/textureeditwidget.h"
#include "elemente/textur.h"
#include "container/project.h"
#include "models/elementmodel.h"


namespace Ui {
    class ManageScansDialog;
}

class ManageScansDialog : public QDialog {
    Q_OBJECT

    public:
//        ManageScansDialog(QWidget *parent = 0);
        ManageScansDialog(Project *p, QGLWidget *glwidget, QWidget *parent = 0);
        ~ManageScansDialog();
        void setProject(Project *p) { project = p; loadScanContainer(p->getScanContainer()) ;}
        bool loadFromXml();
        virtual void show();
        void setModel(ElementModel *em);

        void loadScanContainer(ContScans *scans);
    protected:
        void changeEvent(QEvent *e);

    private:

        void addScanToModel(Scan* s);

        bool removeDir(const QString &dirName);
        bool loadFromXML();

        bool loadScans();
        bool saveScans();

        Project* project;

        QString loadImageDialog(QString dir = QString());

        QModelIndex scansIndex;
        QModelIndex selectedScan;
        ContScans *scancontainer;
        Ui::ManageScansDialog *ui;
        ElementModel *elementmodel;
        QString scansDir;
        QString lastDir;
        QGLWidget *glw;
        QWidget *parent;


    private slots:
//        void on_openButton_clicked();
//        void on_saveButton_clicked();
        void on_addScan_clicked();
        void deleteScan();
        void deleteTexture();
//        void doubleClicked(QTreeWidgetItem * item, int column);
//        void on_treeView_doubleClicked(QModelIndex index);
//        void saveScan(Scan*);
//        void deleteTexture(int);

        void textureUpdated(Textur *t);

//        void on_listView_clicked(const QModelIndex &index);

        void on_scanView_doubleClicked(const QModelIndex &index);
        void on_texturesView_doubleClicked(const QModelIndex &index);

        void setTextureRoot(QModelIndex i);

//        void on_texturesView_doubleClicked(const QModelIndex &index);

//        void on_scanView_customContextMenuRequested(const QPoint &pos);

//        void on_texturesView_customContextMenuRequested(const QPoint &pos);

signals:
        void updateGl();
};

#endif // MANAGESCANSDIALOG_H
