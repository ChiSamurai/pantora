#ifndef TEXTUREEDITWIDGET_H
#define TEXTUREEDITWIDGET_H

//#include <QDockWidget>
#include <QScrollArea>
#include <QGraphicsView>
#include <QMenuBar>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QTabWidget>
#include <QDialog>
#include <QtGui>
#include <QModelIndex>
#include <QDataWidgetMapper>
#include <QSvgGenerator>

#include "texturerenderarea.h"
#include "editmenu.h"

#include "menupaint.h"
#include "menutransparency.h"
#include "menuclip.h"
#include "menucut.h"
#include "menusplit.h"

#include "elemente/abstractelement.h"
#include "models/elementmodel.h"

#include "container/contscans.h"



class TextureEditWidget : public QDialog
{
Q_OBJECT

public:
    TextureEditWidget(const QModelIndex &i, QWidget *parent = 0);

public slots:
    void updateActions();

private slots:
    void saveImage();
    void print();
    void tabChanged(int);
    void exportImage();

signals:
//    void clearMenus();
    void mainModusChanged(int);
    void textureSaved();
    void updated(Textur *t);
    void glRedraw();

private:

    void createActions();
    void createMenus();
    void createConnections();

    void createTemp();

    double scaleFactor;

    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

    QAction *saveAct;
    QAction *exportAct;
    QAction *printAct;
    QAction *exitAct;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *viewMenu;

    TextureRenderArea *renderArea;
    QLabel *modusLabel;

    QComboBox *modusComboBox;

    QTabWidget *menu;
    MenuPaint *mp;
    MenuTransparency *mt;
    MenuClip *mc;
    MenuCut *mcut;

    QGridLayout *mainLayout;


    Textur *_texture;

    ElementModel *model, *tempModel;
    QModelIndex index, befGrenzenIndex, tempBefGrenzenIndex;

    QMap<QPersistentModelIndex, QPersistentModelIndex> indexOldToNewMap;

protected:
    void closeEvent(QCloseEvent *);
};

#endif // TEXTUREEDITWIDGET_H
