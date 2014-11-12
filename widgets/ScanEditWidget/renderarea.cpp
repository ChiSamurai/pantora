#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(QRect(QPoint(0, 0), QPoint(0, 0)), this);
    scene->setBackgroundBrush(QBrush(Qt::lightGray));
    setScene(scene);

    factor = matrix().m11();

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    setAlignment (Qt::AlignLeft | Qt::AlignTop);

    scaleFactor = 1.15;
    antialiased = true;
    transformed = false;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(true);

    makeCrosshair();

}

RenderArea::~RenderArea(){
//    delete scene;
}

void RenderArea::setImage(QPixmap img){
    image = img;
//    qDebug() << "setImage" << img.size();
    //clear Scene
    scene->clear();
    scene->addPixmap(image);
    setSceneRect(-30, -30, image.width() + 60, image.height() + 60);
    zoomFull();
}

void RenderArea::setImage(QImage img){
    image = QPixmap::fromImage(img);
//    qDebug() << "setImage" << img.size();
    //clear Scene
    scene->clear();
    scene->addPixmap(image);
    setSceneRect(-30, -30, image.width() + 60, image.height() + 60);
    zoomFull();
}

void RenderArea::makeCrosshair(){
    crosshairPixmap = new QPixmap(25,25);
    crosshairPixmap->fill(Qt::transparent);
    crosshairPainter = new QPainter(crosshairPixmap);
    QPen p(Qt::black);
    p.setWidth(1);
    crosshairPainter->setPen(p);
    QPoint middle(12, 12);
    int abstand = 5;
    crosshairPainter->drawPoint(middle);
    crosshairPainter->drawLine(middle.x(), 0, middle.x(),  middle.y() - abstand);
    crosshairPainter->drawLine(middle.x(), crosshairPixmap->height(), middle.x(),  middle.y() + abstand);
    crosshairPainter->drawLine(0, middle.y(), middle.x() - abstand, middle.y());
    crosshairPainter->drawLine(crosshairPixmap->width(), middle.y(), middle.x() + abstand, middle.y());
    crosshair = new QCursor(*crosshairPixmap, middle.x(), middle.y());

}

void RenderArea::wheelEvent(QWheelEvent* event) {
    if(event->modifiers() == Qt::ControlModifier){
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        if(event->delta() > 0) {
            //Hineinzoomen
            zoomIn();
        } else {
            //Hinauszoomen
            zoomOut();
        }
}else{
        QGraphicsView::wheelEvent(event);
    }
}

void RenderArea::enterEvent(QEvent *event){
    this->setCursor(Qt::CrossCursor);
    this->setCursor(*crosshair);
}

void RenderArea::leaveEvent(QEvent *event){
    this->setCursor(Qt::ArrowCursor);
}

void RenderArea::zoomIn(){
    scale(scaleFactor, scaleFactor);
    updateFactor();
}

void RenderArea::zoomOut(){
    scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    updateFactor();
}

void RenderArea::zoomFull(){
    qreal factor = (qreal)viewport()->width() / (qreal)image.width();
    resetTransform();
    scale(factor, factor);
    updateFactor();
}

void RenderArea::zoomReset(){
    resetTransform();
    updateFactor();
}

void RenderArea::showEvent(QShowEvent *event){
    zoomFull();
}

void RenderArea::updateFactor(){
    factor = matrix().m11();
    emit factorChanged(factor);
}

void RenderArea::clearImage(){
    scene->clear();
    scene->addPixmap(image);
}
