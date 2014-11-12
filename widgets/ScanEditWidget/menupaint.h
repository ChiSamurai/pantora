#ifndef MENUPAINT_H
#define MENUPAINT_H

#include <QWidget>
#include <QString>
#include <QPolygon>
#include <QListWidget>
#include <QMap>
#include <QPoint>
#include <QDebug>
#include <QModelIndex>
#include <QDataWidgetMapper>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QMouseEvent>
#include <QColorDialog>

#include "widgets/ScanEditWidget/editmenu.h"
#include "models/elementmodel.h"

#include "elemente/linie.h"

namespace Ui {
    class MenuPaint;
}

class MenuPaint: public QWidget{
    Q_OBJECT
public:
    enum mode {New, Edit};
    MenuPaint(ElementModel *em, QGraphicsScene *s, QWidget *parent = 0);
    ~MenuPaint();

    void setActivated(bool);
    ElementModel *getModel() { return model;}
    QPersistentModelIndex getBefundgrenzenIndex() {return befGrenzenIndex;}
//    void fillList(QList< Linie > *list);
protected:
    void changeEvent(QEvent *e);
    int punktgruppenCount;

public slots:
    void closeLineStatusChanged(bool status);
    void changeModus(int modus);

    //Slots für RenderArea-Signale
    void newSelectionRect(QRect);
    void newCoordsForPoint(QPoint);
    void factorUpdate(qreal factor);
    void selectionStopped(QMouseEvent *);
    void newMousePos(QPoint);

private slots:
//    void on_deleteLine_clicked();
    void on_deletePoint_clicked();
    void on_addPoint_clicked();
    void on_closedLine_toggled(bool checked);
    void on_befundgrenzenList_clicked(const QModelIndex&);

    void on_befundgrenzenList_customContextMenuRequested(const QPoint &pos);
    void deleteSelectedItem();

    void on_changeColor_clicked();

    void on_copyButton_clicked();

private:
    void drawBefGrenzen();
    void updatePens();

    void updatePoints();
    void updateItem();
    void updateSelectedGraphicsPath();

    qreal factor;
    int ellipseRadius, selectionRadius;

    QGraphicsScene *scene;
    ElementModel *model;
//    QModelIndex index;
    Ui::MenuPaint *ui;
    QPersistentModelIndex index, befGrenzenIndex;
    QMap<QPersistentModelIndex, QGraphicsPathItem*> indexPathMap;


    QPainterPath pointsPath;
    QGraphicsPathItem *pointsGraphicsPath;
    QGraphicsPathItem *selectionEllipse;


    QPen highlightPen, normalPen, ellipsePen, selectionPen;
    qreal nPwidth, hPwidth;
    QColor fillColor;

    QPolygon selectionPolygon;
    QPersistentModelIndex selectedPathIndex;
    QIcon colorButtonIcon;


    int selectedPointIndex;

//    mode modus;
    bool activated;
    bool drawTempLine;
};

#endif // MENUPAINT_H
