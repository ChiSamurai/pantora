#include "menucut.h"
#include "ui_menucut.h"

MenuCut::MenuCut(const QModelIndex &i, QGraphicsScene *s, QWidget *parent) : EditMenu(i, parent),
    ui(new Ui::MenuCut)
{
    ui->setupUi(this);

//    modus = New;
    ui->addPoint->setDisabled(true);
    ui->deletePoint->setDisabled(true);
    ui->deleteAll->setDisabled(true);


    linePenWidth = 1;
    highlightPenWidth = 1;
    ellipsePenWidth = 1;
    ellipseRadius = 10;

    selectedPointIndex = -1;

    scene = s;
    model = (ElementModel*)i.model();
    index = i;
    _textur = (Textur*)model->getItem(index);

    linePen = QPen(Qt::blue);
    linePen.setWidth(linePenWidth);


    //Pen & Brush
    highlightPen = QPen(linePen);
    highlightPen.setWidth(highlightPenWidth);

    QColor transBlue = QColor(Qt::blue);
    transBlue.setAlpha(50);
    fillBrush = QBrush(transBlue);

    //Punkte zu Border hinzufügen
    borderPolygon = QPolygon((QPolygon)_textur->getRahmen());

    QPainterPath p;
    p.addRect(0, 0, _textur->getImage().width(), _textur->getImage().height());
    p.addPolygon(borderPolygon);

    p.closeSubpath();

    border = scene->addPath(p, linePen, fillBrush);


    //Border-Punkte nachzeichnen
    QPainterPath points;
    foreach(QPointF point, borderPolygon) points.addEllipse(point, ellipseRadius, ellipseRadius);
    borderPoints = scene->addPath(points, linePen);

    ellipsePen = QPen(Qt::red, ellipsePenWidth);
    ellipsePen.setStyle(Qt::DashLine);

    QPainterPath hellipse;
    hellipse.addEllipse(QPointF(0.0, 0.0), ellipseRadius, ellipseRadius);
    highlightEllipse = scene->addPath(hellipse, ellipsePen);

//    ui->modus->addItem(tr("zeichnen"));
//    ui->modus->addItem(tr("bearbeiten"));
    if(borderPolygon.count() < 3){
        border->setVisible(false);
        borderPoints->setVisible(false);
        highlightEllipse->setVisible(false);
        ui->addPoint->setEnabled(true);
        ui->deletePoint->setEnabled(true);
        ui->deleteAll->setEnabled(true);
    }
    //Temporäre Zeichenitems
    drawTempLine = false;
    activated = false;
}

MenuCut::~MenuCut()
{
    delete ui;
}

void MenuCut::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//void MenuCut::on_modus_currentIndexChanged(int modus)
//{
//    if(modus == Edit){
//        ui->addPoint->setDisabled(false);
//        ui->deletePoint->setDisabled(false);
//        ui->deleteAll->setDisabled(false);
//        if(borderPolygon.count() > 2){
//            border->setVisible(true);
//            borderPoints->setVisible(true);
//        }
//    }else{
//        ui->addPoint->setDisabled(true);
//        ui->deletePoint->setDisabled(true);
//        ui->deleteAll->setDisabled(true);
//        border->setVisible(false);
//        borderPoints->setVisible(false);
//    }
//}

void MenuCut::on_addPoint_clicked()
{
    if(selectedPointIndex > -1){
        if (selectedPointIndex == 0){
            borderPolygon.insert(1, (borderPolygon.at(0) + borderPolygon.at(1)) / 2);
        } else if (selectedPointIndex == borderPolygon.count() - 1){
            borderPolygon.append((borderPolygon.last() + borderPolygon.first()) / 2 );
        } else {
            borderPolygon.insert(selectedPointIndex + 1, (borderPolygon.at(selectedPointIndex) + borderPolygon.at(selectedPointIndex + 1)) / 2);
        }
    }
    updateBorder();


//    emit addPoint();
}

void MenuCut::on_deletePoint_clicked()
{
    if(selectedPointIndex > -1) borderPolygon.remove(selectedPointIndex);
    if(borderPolygon.count() < 3){
        selectedPointIndex = -1;
        border->setVisible(false);
        borderPoints->setVisible(false);
    }
    else if(selectedPointIndex > 0)
        selectedPointIndex = selectedPointIndex - 1;
    else selectedPointIndex = borderPolygon.count() - 1;

    updateBorder();
//    emit deletePoint();
}

void MenuCut::on_deleteAll_clicked()
{
    borderPolygon.clear();
    border->setVisible(false);
    borderPoints->setVisible(false);

    ui->addPoint->setEnabled(false);
    ui->deletePoint->setEnabled(false);
    ui->deleteAll->setEnabled(false);
    selectedPointIndex = -1;
    updateBorder();
}

void MenuCut::newSelectionRect(QRect sr){
    if(activated){
        if(drawTempLine){
            QPoint p = QPoint(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            borderPolygon.append(p);
            updateBorder();
        }
        else if(border->isVisible()){
            for(int i = 0; i < borderPolygon.count(); i++){
                if(sr.contains(borderPolygon.at(i))){
                    selectedPointIndex = i;
                    QPainterPath hellipse;
                    hellipse.addEllipse(borderPolygon.at(i), ellipseRadius / factor, ellipseRadius / factor);
                    highlightEllipse->setPath(hellipse);
                    highlightEllipse->setVisible(true);
                    return;
                }
            }
            selectedPointIndex = -1;
            highlightEllipse->setVisible(false);
        }

        else if(!drawTempLine){
            drawTempLine = true;
            borderPolygon.clear();
            borderPolygon.append(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            borderPolygon.append(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            border->setBrush(QBrush(Qt::transparent));
            border->setVisible(true);

            updateBorder();
        }
    }
}

void MenuCut::newCoordsForPoint(QPoint p){
    if (selectedPointIndex > -1 && border->isVisible()){
        QPainterPath pp = border->path();
        pp.setElementPositionAt(selectedPointIndex + 5, p.x(), p.y());
        if(selectedPointIndex == 0) pp.setElementPositionAt(pp.elementCount() - 1, p.x(), p.y());
        else if(selectedPointIndex == pp.elementCount() - 6) pp.setElementPositionAt(5, p.x(), p.y());
        border->setPath(pp);

        borderPolygon.setPoint(selectedPointIndex, p);
        QPainterPath points;
        foreach(QPointF point, borderPolygon) points.addEllipse(point, (linePenWidth / factor) * 3, (linePenWidth / factor) * 3);
        borderPoints->setPath(points);


        QPainterPath hellipse;
        hellipse.addEllipse(p, ellipseRadius / factor, ellipseRadius / factor);
        highlightEllipse->setPath(hellipse);
    }
}

void MenuCut::newMousePos(QPoint p){
    if(activated){
        if(drawTempLine){
            borderPolygon.setPoint(borderPolygon.count() - 1, p);
            updateBorder();
        }
    }
}

void MenuCut::selectionStopped(QMouseEvent *event){
    if(drawTempLine && event->button() == Qt::RightButton){
        drawTempLine = false;
        borderPolygon.remove(borderPolygon.count() - 1);
        if(borderPolygon.count() > 2){
            borderPoints->setVisible(true);
            highlightEllipse->setVisible(false);
            ui->addPoint->setEnabled(true);
            ui->deletePoint->setEnabled(true);
            ui->deleteAll->setEnabled(true);
            border->setBrush(fillBrush);
        }
        updateBorder();
    }
}

void MenuCut::factorUpdate(qreal f){
    if (f < 1){
        linePen.setWidth(linePenWidth / f);
        highlightPen.setWidth(highlightPenWidth / f);
        ellipsePen.setWidth(ellipsePenWidth / f);

        //Punkte skalieren
        QPainterPath points;
        foreach(QPointF point, borderPolygon) points.addEllipse(point, (linePenWidth / f) * 3, (linePenWidth / f) * 3);
        borderPoints->setPath(points);

        if(selectedPointIndex > -1){
            QPainterPath hellipse;
            hellipse.addEllipse(borderPolygon.at(selectedPointIndex), ellipseRadius / f, ellipseRadius / f);
            highlightEllipse->setPath(hellipse);
        }
        factor = f;
    }
    else {
        linePen.setWidth(linePenWidth);
        highlightPen.setWidth(highlightPenWidth);
        ellipsePen.setWidth(ellipsePenWidth);

        //Punkte skalieren
        QPainterPath points;
        foreach(QPointF point, borderPolygon) points.addEllipse(point, linePenWidth * 3, linePenWidth * 3);
        borderPoints->setPath(points);

        if(selectedPointIndex > -1){
            QPainterPath hellipse;
            hellipse.addEllipse(borderPolygon.at(selectedPointIndex), ellipseRadius, ellipseRadius);
            highlightEllipse->setPath(hellipse);
        }
        factor = 1;
    }
    updatePens();
}

void MenuCut::updatePens(){
    border->setPen(linePen);
    borderPoints->setPen(linePen);
    highlightEllipse->setPen(ellipsePen);


//    qDebug() << "factor " << factor << "| normalPenWidth " << normalPen.width();
//    qDebug() << "factor " << factor << "| highlightPenWidth " << highlightPen.width();
//    foreach(QGraphicsPathItem *path, indexPathsMap){
//        if (path->isSelected()){
//            path->setPen(highlightPen);
//        } else {
//            path->setPen(normalPen);
//        }
//    }

}

void MenuCut::setActivated(bool activate){
    activated = activate;
    //Menu bekommt focus
    if(activate){
//        ui->modus->setCurrentIndex(New);
        if(borderPolygon.count() > 2){
            border->setVisible(true);
            borderPoints->setVisible(true);
            highlightEllipse->setVisible(true);
            ui->addPoint->setEnabled(true);
            ui->deletePoint->setEnabled(true);
            ui->deleteAll->setEnabled(true);
        }
        //Menu verliert focus
    } else {
        if(drawTempLine){
            drawTempLine = false;
            selectedPointIndex = -1;
            borderPolygon.remove(borderPolygon.count() - 1);
            border->setBrush(fillBrush);
            updateBorder();
        }
        border->setVisible(false);
        borderPoints->setVisible(false);
        highlightEllipse->setVisible(false);
    }
}

void MenuCut::updateBorder(){
    if(drawTempLine){
        QPainterPath p;
        p.addPolygon(borderPolygon);
        border->setPath(p);
    }
    else if(borderPolygon.count() > 2){
        QPainterPath p;
        p.addRect(0, 0, _textur->getImage().width(), _textur->getImage().height());
        p.addPolygon(borderPolygon);
        p.closeSubpath();
        border->setPath(p);

        QPainterPath points;
        foreach(QPointF point, borderPolygon) points.addEllipse(point, (linePenWidth / factor) * 3, (linePenWidth / factor) * 3);
        borderPoints->setPath(points);

        border->setVisible(true);
        borderPoints->setVisible(true);
    }else{
        border->setVisible(false);
        borderPoints->setVisible(false);
    }

    if(selectedPointIndex > -1){
        QPainterPath hellipse;
        hellipse.addEllipse(borderPolygon.at(selectedPointIndex), ellipseRadius / factor, ellipseRadius / factor);
        highlightEllipse->setPath(hellipse);
    }
    else highlightEllipse->setVisible(false);

}

Linie MenuCut::getRahmen(){
    Linie l;
    foreach(QPoint p, borderPolygon){
        l.append(p);
    }
    return l;
}
