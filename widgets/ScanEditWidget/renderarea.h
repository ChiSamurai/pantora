#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QAction>
#include <QScrollArea>
#include <QGraphicsView>

#include <QImage>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QCursor>
#include <QPixmap>
#include <QMouseEvent>

#include <QMessageBox>
#include <QDebug>
#include <QGraphicsItem>

class RenderArea : public QGraphicsView
{
Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    ~RenderArea();
    void showEvent(QShowEvent * event );

    void setImage(QPixmap);
    void setImage(QImage);
    QImage getImage() { return image.toImage(); }

    qreal getFactor() { return factor; }

    QGraphicsScene *getScene() {return scene; }


    QPixmap image;
    QGraphicsScene *scene;

protected:
    void wheelEvent(QWheelEvent* event);
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);

public slots:
    void zoomIn();
    void zoomOut();
    void zoomFull();
    void zoomReset();

    void clearImage();
signals:
    void factorChanged(qreal factor);

private:
    void makeCrosshair();
    void updateFactor();

    double scaleFactor;

    QPixmap *crosshairPixmap;
    QPainter *crosshairPainter;
    QCursor *crosshair;

    bool antialiased;
    bool transformed;

    qreal factor;
};

#endif // RenderArea_H
