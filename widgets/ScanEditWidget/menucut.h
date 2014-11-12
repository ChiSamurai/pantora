#ifndef MENUCUT_H
#define MENUCUT_H

#include <QWidget>
#include <QModelIndex>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

#include "editmenu.h"


namespace Ui {
    class MenuCut;
}

class MenuCut : public EditMenu{
    Q_OBJECT
public:
    enum mode{New, Edit};
    MenuCut(const QModelIndex &i, QGraphicsScene* s, QWidget *parent = 0);
    ~MenuCut();

    Linie getRahmen();
//    void changeModus(mode);

public slots:
    void newSelectionRect(QRect);
    void newCoordsForPoint(QPoint);
    void newMousePos(QPoint);
    void selectionStopped(QMouseEvent *);
    void factorUpdate(qreal factor);
    void setActivated(bool);

signals:
//    void modusChanged(int);
//    void addPoint();
//    void deletePoint();
//    void deleteAll();
//    void resetLine();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MenuCut *ui;

    void updateBorder();

    mode modus;

    QModelIndex index;
    ElementModel *model;
    QGraphicsScene *scene;
    Textur *_textur;

    QGraphicsPathItem *border;
    QGraphicsPathItem *borderPoints;
    QGraphicsPathItem *highlightEllipse;

    QPolygon borderPolygon;

    int ellipseRadius;

    QPen linePen, highlightPen, ellipsePen;
    QBrush fillBrush;

    int linePenWidth, highlightPenWidth, ellipsePenWidth;

    int selectedPointIndex;

    qreal factor;

    bool drawTempLine;
    bool activated;

private slots:
    void on_deleteAll_clicked();
//    void on_modus_currentIndexChanged(int index);
    void on_deletePoint_clicked();
    void on_addPoint_clicked();

    void updatePens();
};

#endif // MENUCUT_H
