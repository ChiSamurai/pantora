#ifndef MENUTRANSPARENCY_H
#define MENUTRANSPARENCY_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QMap>
#include <QModelIndex>
#include <QMouseEvent>

#include "editmenu.h"
#include "elemente/linie.h"

namespace Ui {
    class MenuTransparency;
}

class MenuTransparency : public EditMenu{
    Q_OBJECT
public:
    enum mode{New, Edit};

    MenuTransparency(const QModelIndex &i, QGraphicsScene *s, QWidget *parent = 0);
    ~MenuTransparency();

    void setActivated(bool);
    QList<Linie> getTransPunktgruppen();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_deleteLine_clicked();
    void on_deletePoint_clicked();
    void on_addPoint_clicked();

    void on_punktgruppenListe_itemSelectionChanged();

public slots:
    void changeModus(int modusIndex);

    //Slots für RenderArea-Signale
    void factorUpdate(qreal factor);
    void newSelectionRect(QRect);
    void newCoordsForPoint(QPoint);
    void selectionStopped(QMouseEvent *);
    void newMousePos(QPoint);

private:
    Ui::MenuTransparency *ui;
    void updatePens();
    void updatePoints();
    void updateSelectedGraphicsPath();

    QPen normalPen, highlightPen, ellipsePen, selectionPen;
    QBrush fillBrush;
    int nPwidth, hPwidth;

    qreal factor;
    int ellipseRadius, selectionRadius;

    QGraphicsPathItem *selectionEllipse, *pointsGraphicsPath;
    int selectedPolyIndex;
    int selectedPointIndex;

    QPolygon selectedTransPoly;


    QMap<QListWidgetItem*, QGraphicsPathItem*> indexPathMap;
    Textur *_textur;
    QGraphicsScene *scene;

    ElementModel *model;
    QModelIndex index;

    bool drawTempLine;

    bool activated;

};

#endif // MENUTRANSPARENCY_H
