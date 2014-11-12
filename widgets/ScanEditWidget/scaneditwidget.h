#ifndef SCANEDITWIDGET_H
#define SCANEDITWIDGET_H

#include <QDialog>
#include <QTabWidget>
#include <QGraphicsView>
#include <QMenuBar>
#include <QGridLayout>
#include <QFileDialog>
#include <QImageReader>

#include "scanrenderarea.h"
#include "menusplit.h"

#include "elemente/abstractelement.h"
#include "models/elementmodel.h"

#include "container/contscans.h"

class ScanEditWidget : public QDialog
{
Q_OBJECT
public:
    ScanRenderArea *renderArea;
//    RenderArea *renderArea;
//    QGraphicsView *renderArea;

    explicit ScanEditWidget(const QModelIndex &i, QWidget *parent = 0);
    explicit ScanEditWidget(QModelIndex scansIndex, QString scansDir, QString filename, QWidget *parent = 0);
//    explicit ScanEditWidget(Scan *scan, QWidget *parent = 0);
//    bool loadImageDialog(QString *);
//    void loadScan(Scan *s);
//    void clear();

    QMap<QPersistentModelIndex, QPersistentModelIndex> getOldToNewMapping();

private slots:
//    void openImageClicked();
    void deleteTextureClicked(int index);
    void saveScan();

signals:
    void clearMenus();
    void modusChanged(int);
    void textureDeleted(int);
    
private:
//    bool loadImage();
    void init();

//    QPixmap image;
//    void scaleImage(double);
    void createActions();
    void createMenus();
    void createConnections();
    void activateMenu(bool activate);

    Scan *_scan, *_origScan;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

//    QAction *openAct;
//    QAction *saveAct;
    QAction *exportAct;
    QAction *printAct;
    QAction *exitAct;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;

    QTabWidget *menu;
    MenuSplit *ms;

    QGridLayout *mainLayout;

//    void fillList(Scan *s);

    ContScans *scansCont;
    AbstractElement* element;
    QPersistentModelIndex index, _scanIndex, _origScansIndex, _tempTexturenIndex, _origTexturenIndex;
    ElementModel *model;
    ElementModel *texturenListe;

    QMap<QPersistentModelIndex, QPersistentModelIndex> indexOldToNewMap;

    QString lastDir;
protected:
    void closeEvent(QCloseEvent *);

public:


};

#endif // SCANEDITWIDGET_H
