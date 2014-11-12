#ifndef TEXTURERENDERAREA_H
#define TEXTURERENDERAREA_H

#include <QAction>
#include <QScrollArea>
//#include <QGraphicsView>

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

#include "models/elementmodel.h"

#include "elemente/abstractelement.h"
#include "elemente/textur.h"

#include "elemente/linie.h"
#include "elemente/einhaengepunkt.h"

class TextureRenderArea : public RenderArea
{
Q_OBJECT
public:
    enum Mode { Clip, Cut, Line, Transparency};
    enum SubMode { New, Edit};

    explicit TextureRenderArea(const QModelIndex &i, QWidget *parent = 0);
    ~TextureRenderArea();

//    void showEvent(QShowEvent * event );

//    QPoint *getPointAtMousePos(QPolygon *, QPointF *);
//    int getPointAtMousePos(QRect, QPoint);

    void saveTexture(int typ);

protected:
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );

public slots:
//    void changeModus(int m);
    void clearSelection();

signals:
    void subModusChanged();

    //Mouse press & remove Signals
    void selectionRect(QRect);
    void newPointForSelection(QPoint);
    void newMousePos(QPoint);
    void mouseReleased(QMouseEvent *);

private:
    void loadTexture(QModelIndex i);

    int pointtolerance;//wie groﬂ darf Toleranz in Pixeln sein?

    Mode modus;
    SubMode subModus;

    QPoint mousePos;
    bool closeLine;

    QString *exportName;

    Textur *_textur;

    ElementModel *model;
    QModelIndex index, befGrenzenIndex;

    QModelIndex selectedIndex;

    bool pointDragFlag;

};

#endif // TEXTURERENDERAREA_H
