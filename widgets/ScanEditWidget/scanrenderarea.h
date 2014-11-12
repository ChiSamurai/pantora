#ifndef SCANRENDERAREA_H
#define SCANRENDERAREA_H

#include <QAction>
//#include <QScrollArea>

#include <QImage>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QCursor>
#include <QPixmap>
#include <QMouseEvent>
#include <QVector3D>

#include <QMessageBox>
#include <QDebug>
#include <QGraphicsItem>

#include "widgets/ScanEditWidget/renderarea.h"

#include "elemente/scan.h"
#include "elemente/textur.h"
#include "elemente/abstractelement.h"

#include "models/elementmodel.h"


class ScanRenderArea : public RenderArea
{
Q_OBJECT
public:
    enum Mode { New, Edit};

    explicit ScanRenderArea(const QModelIndex &i, QWidget *parent = 0);
    ~ScanRenderArea();

    int getPointAtMousePos(QRect, QPoint);

    void loadScan(QModelIndex i);

//    QList<QModelIndex> getNewRects() { return newRects; }

private slots:

protected:
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void wheelEvent(QWheelEvent* event);

public slots:
    void changeModus(int m);
//    void changeSubModus(int m);

    void setTextureSelected(QModelIndex &i);

    void removeTexture(QPersistentModelIndex index);

signals:
//    void newRect(QString, QRect);

private:
    void updateDrawing();
    void updatePenWidth();

    int pointtolerance; //wie groß ist Toleranz für Auswahl der Ecken in Pixeln ?

    Mode modus;
//    SubMode subModus;

    QPoint mousePos;

    Scan *scan;

    QModelIndex index;
    QModelIndex texturenIndex;
    QModelIndex selectedIndex;

    ElementModel *model;

    QMap<QModelIndex, QGraphicsRectItem*> rectsMap;

//    QList<QModelIndex> newRects;

    QPen highlightPen, rectPen;
    qreal rPwidth, hPwidth;
    QColor fillColor;

    int resizeFlag;

private slots:
    void factorUpdated();
};

#endif // SCANRENDERAREA_H
