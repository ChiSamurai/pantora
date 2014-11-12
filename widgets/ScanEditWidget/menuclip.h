#ifndef MENUCLIP_H
#define MENUCLIP_H

#include <QWidget>
#include <QPoint>
#include <QVector3D>
#include <QDebug>
#include <QString>
#include <QModelIndex>
#include <QRect>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QDataWidgetMapper>

#include "elemente/einhaengepunkt.h"
#include "editmenu.h"
#include "renderarea.h"


#define LINE_WIDTH 2

namespace Ui {
    class MenuClip;
}

class MenuClip : public EditMenu {
    Q_OBJECT

public:
    enum einhaengepunktLabel{A, B};
    MenuClip(const QModelIndex &i, QGraphicsScene *s, QWidget *parent = 0);
    ~MenuClip();
    void setClipPoints(Einhaengepunkt einA, Einhaengepunkt einB);
    void setTyp(int);
    int getTyp();
//    void setName(QString);
    QString getName();

    Einhaengepunkt getEin(einhaengepunktLabel);

public slots:
    void setPixelCoords(int pId, QPoint p);
    void updatePens();
//    void clearItems();
    void factorUpdate(qreal f);
    void setActivated(bool);

signals:
//    void setCoord(int pId, QVector3D coord);
//    void clearPixelCoords();
//    void typ_changed(int);

protected:
    void changeEvent(QEvent *e);

private slots:
//    void on_AGlobx_editingFinished();
//    void on_AGloby_editingFinished();
//    void on_AGlobz_editingFinished();

//    void on_BGlobx_editingFinished();
//    void on_BGloby_editingFinished();
//    void on_BGlobz_editingFinished();

    void on_globLoeschen_clicked();
    void on_pixelLoeschen_clicked();

    void newMousePos(QPoint p);
    void newSelectionRect(QRect sr);
    void newCoordsForPoint(QPoint p);
    void selectionStopped(QMouseEvent *);

//    void typ_changed(int);

    void on_showScanPic_clicked();

private:
    Ui::MenuClip *ui;

    void toggleUIItems(bool enable);
    void updateLine();

    int lineWidth;
    int selectedPoint;
    int clipPointFontSize;
    bool tempLine;
    bool activated;

    QModelIndex index;
    ElementModel *model;
    QGraphicsScene *scene;
    Textur *_textur;
    Einhaengepunkt einA, einB;
    QGraphicsTextItem *clipPointA, *clipPointB;
    QFont clipPointFont;

    QPen linePen;
    QGraphicsLineItem *clipLine;

};

#endif // MENUCLIP_H
