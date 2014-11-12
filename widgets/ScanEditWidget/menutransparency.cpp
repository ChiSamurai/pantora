#include "menutransparency.h"
#include "ui_menutransparency.h"

MenuTransparency::MenuTransparency(const QModelIndex &i, QGraphicsScene *s, QWidget *parent): EditMenu(i, parent),
    ui(new Ui::MenuTransparency)
{
    ui->setupUi(this);
    ui->modus->addItem(tr("neu zeichnen"));
    ui->modus->addItem(tr("bearbeiten"));

    ui->addPoint->setDisabled(true);
    ui->deletePoint->setDisabled(true);
    ui->deleteLine->setDisabled(true);
    ui->punktgruppenListe->setDisabled(true);

    ui->punktgruppenListe->setSelectionMode(QListWidget::SingleSelection);

    index = i;
    model = (ElementModel*) i.model();
    scene = s;
    _textur = (Textur*)model->getItem(i);
    ellipseRadius = 5;
    selectionRadius = 10;


    //Stifte
    nPwidth = 1;
    hPwidth = 2;
    normalPen = QPen(Qt::blue, nPwidth);
    highlightPen = QPen(Qt::blue, hPwidth);
    ellipsePen = QPen(Qt::blue, nPwidth );
    selectionPen = QPen(Qt::red, nPwidth, Qt::DashLine );

    QColor fillColor = normalPen.color();
    fillColor.setAlpha(50);

    fillBrush = QBrush(fillColor);
    //Auswahl
    QPainterPath hellipse;
    hellipse.addEllipse(0, 0, selectionRadius, selectionRadius);
    selectionEllipse = scene->addPath(hellipse);
    selectionEllipse->setVisible(false);
    selectionEllipse->setPen(selectionPen);

    selectedPointIndex = -1;


    //Bereichliste füllen
    foreach (Linie l, *_textur->getTransPunktgruppen()){
//        QPolygon poly  = (QPolygon)l;
        QPainterPath pp;
        pp.addPolygon(l);
        pp.closeSubpath();
        ui->punktgruppenListe->addItem("Bereich");
        indexPathMap.insert(ui->punktgruppenListe->item(ui->punktgruppenListe->count() - 1), scene->addPath(pp, normalPen, fillBrush));
    }

    //Grabber Points
    pointsGraphicsPath = scene->addPath(QPainterPath(), normalPen);

    drawTempLine = false;
    activated = false;

    connect(ui->modus, SIGNAL(currentIndexChanged(int)), this, SLOT(changeModus(int)));
}

MenuTransparency::~MenuTransparency()
{
    delete ui;
}

void MenuTransparency::changeEvent(QEvent *e)
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

void MenuTransparency::changeModus(int modusIndex){
    //Wenn editieren ausgewählt: Buttons enablen
    if(modusIndex == Edit){
        ui->addPoint->setEnabled(true);
        ui->deletePoint->setEnabled(true);
        ui->deleteLine->setEnabled(true);
        ui->punktgruppenListe->setEnabled(true);
    }else{
        ui->addPoint->setDisabled(true);
        ui->deletePoint->setDisabled(true);
        ui->deleteLine->setDisabled(true);
        ui->punktgruppenListe->setDisabled(true);
        ui->punktgruppenListe->clearSelection();
        pointsGraphicsPath->setVisible(false);
        selectionEllipse->setVisible(false);
    }
    updatePens();
}


void MenuTransparency::on_addPoint_clicked()
{
    if(ui->punktgruppenListe->selectedItems().count() == 1 && selectedPointIndex > -1 && selectedPointIndex < selectedTransPoly.count()){
        if (selectedPointIndex == selectedTransPoly.count() - 1){
            selectedTransPoly.append((selectedTransPoly.last() + selectedTransPoly.first()) / 2 );
        } else {
            selectedTransPoly.insert(selectedPointIndex + 1, (selectedTransPoly.at(selectedPointIndex) + selectedTransPoly.at(selectedPointIndex + 1)) / 2);
        }
        QPainterPath newPath;
        newPath.addPolygon(selectedTransPoly);
        newPath.closeSubpath();
        indexPathMap.value(ui->punktgruppenListe->selectedItems().at(0))->setPath(newPath);

        updatePoints();
    }
}

void MenuTransparency::on_deletePoint_clicked()
{
    if(ui->punktgruppenListe->selectedItems().count() == 1 && selectedPointIndex > -1 && selectedPointIndex < selectedTransPoly.count()){
        selectedTransPoly.remove(selectedPointIndex);
        QPainterPath newPath;
        newPath.addPolygon(selectedTransPoly);
        newPath.closeSubpath();
        indexPathMap.value(ui->punktgruppenListe->selectedItems().at(0))->setPath(newPath);

        selectedPointIndex = -1;
        selectionEllipse->setVisible(false);

        updatePoints();
    }
}


void MenuTransparency::on_deleteLine_clicked(){
    if(ui->punktgruppenListe->selectedItems().count() == 1){
        QListWidgetItem *listItem = ui->punktgruppenListe->selectedItems().at(0);
        QGraphicsPathItem *graphicsItem = indexPathMap.value(listItem);

        //GraphicsItem aus szene entfernen
        scene->removeItem(graphicsItem);
        ui->punktgruppenListe->takeItem(ui->punktgruppenListe->currentRow());
        indexPathMap.remove(listItem);
        delete graphicsItem;
        delete listItem;

        selectedPointIndex = -1;
        selectionEllipse->setVisible(false);
        pointsGraphicsPath->setVisible(false);
//        selectedTransPoly = QPolygon();
    }
}

void MenuTransparency::setActivated(bool activate){
    activated = activate;
    if(!activate){
        selectionEllipse->setVisible(false);
        pointsGraphicsPath->setVisible(false);
        selectedPointIndex = -1;
//        if(drawTempLine && selectedTransPoly.count() > 1) selectedTransPoly.remove(selectedTransPoly.count() - 1);
        if(drawTempLine){
            if(selectedTransPoly.count() > 1) selectedTransPoly.remove(selectedTransPoly.count() - 1);
            indexPathMap.value(ui->punktgruppenListe->selectedItems().at(0))->setBrush(fillBrush);
        }
        drawTempLine = false;
        updateSelectedGraphicsPath();
        updatePoints();
    } else {
        selectedTransPoly.clear();
        selectedPointIndex = -1;
        pointsGraphicsPath->setVisible(true);
        selectionEllipse->setVisible(false);
        ui->punktgruppenListe->clearSelection();
        drawTempLine = false;
        updateSelectedGraphicsPath();
        updatePoints();
    }
    //Alle Befundgrenzen ein- bzw. ausblenden
    foreach(QGraphicsPathItem *pathItem, indexPathMap){
        pathItem->setVisible(activate);
    }


}

void MenuTransparency::newSelectionRect(QRect sr){
    if(activated){
        if(ui->modus->currentIndex() == Edit && ui->punktgruppenListe->selectedItems().count() == 1){
            // *** enthält SelectionRect einen Punkt des ausgewählten Polygons?
            selectedPointIndex = -1;
            for(int i = 0; i < selectedTransPoly.count(); i++){
                if(sr.contains(selectedTransPoly.at(i))){
                    selectedPointIndex = i;
                    QPainterPath hellipse;
                    hellipse.addEllipse(selectedTransPoly.at(i), selectionRadius / factor, selectionRadius / factor);
                    selectionEllipse->setPath(hellipse);
                    selectionEllipse->setVisible(true);
                    continue;
                }
            }
        }else if(ui->modus->currentIndex() == New && !drawTempLine){
            // *** Neues Polygon zeichnen
            selectedTransPoly = QPolygon();
            selectedTransPoly.append(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            selectedTransPoly.append(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));

            QPainterPath newPath;
            newPath.addPolygon(selectedTransPoly);
            QGraphicsPathItem *newPathItem = scene->addPath(newPath, normalPen);
            QListWidgetItem *listItem = new QListWidgetItem(tr("transp. Bereich"));
            ui->punktgruppenListe->addItem(listItem);

            indexPathMap.insert(listItem, newPathItem);
            selectedPointIndex = selectedTransPoly.count() - 1;

            drawTempLine = true;
            listItem->setSelected(true);

        } else if(drawTempLine){
            // *** Temporäre Linie "fixieren"
            //Gewählten Punkt "Fixieren"
            selectedTransPoly.setPoint(selectedPointIndex, QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            //Neuen Punkt hinzufügen
            selectedTransPoly.append(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            selectedPointIndex = selectedTransPoly.count() - 1;

            updateSelectedGraphicsPath();
        }
        updatePoints();
    }
}

void MenuTransparency::newCoordsForPoint(QPoint p){
    if(ui->modus->currentIndex() == Edit && !drawTempLine && ui->punktgruppenListe->selectedItems().count() == 1 && selectedPointIndex > -1){
        QGraphicsPathItem * pi = indexPathMap.value(ui->punktgruppenListe->selectedItems().at(0));

        selectedTransPoly.setPoint(selectedPointIndex, p);
        QPainterPath pp ;
        pp.addPolygon(selectedTransPoly);
        pp.closeSubpath();
        pi->setPath(pp);

        updatePoints();
    }

}

void MenuTransparency::selectionStopped(QMouseEvent *event){
    if(activated){
        if(ui->modus->currentIndex() == New){
            if(event->button() == Qt::RightButton){
                if(selectedTransPoly.count() > 1) selectedTransPoly.remove(selectedTransPoly.count() - 1);
                drawTempLine = false;
                selectedPointIndex = -1;
                pointsGraphicsPath->setVisible(false);
                selectionEllipse->setVisible(false);
                indexPathMap.value(ui->punktgruppenListe->selectedItems().at(0))->setBrush(fillBrush);
                updateSelectedGraphicsPath();
                ui->punktgruppenListe->clearSelection();
                updatePoints();
            }
        }
    }
}

void MenuTransparency::newMousePos(QPoint p){
    if(activated){
        if (drawTempLine && ui->punktgruppenListe->selectedItems().count() == 1 && selectedPointIndex > -1 && selectedPointIndex < selectedTransPoly.count()){
            QGraphicsPathItem * pi = indexPathMap.value(ui->punktgruppenListe->selectedItems().at(0));
            selectedTransPoly.setPoint(selectedPointIndex, p);

            QPainterPath pp ;
            pp.addPolygon(selectedTransPoly);
            pi->setPath(pp);
            updatePoints();
        }
    }
}
void MenuTransparency::factorUpdate(qreal f){
    if (f < 1){
        factor = f;
        normalPen.setWidth(nPwidth / f);
        highlightPen.setWidth(hPwidth / f);
        ellipsePen.setWidth(nPwidth / f);
        selectionPen.setWidth(nPwidth / f);
    }
    else {
        factor = 1;
        normalPen.setWidth(nPwidth);
        highlightPen.setWidth(hPwidth);
        ellipsePen.setWidth(nPwidth);
        selectionPen.setWidth(nPwidth);
    }
    updatePens();
    updatePoints();
}

void MenuTransparency::updatePens(){
    foreach(QListWidgetItem *i, indexPathMap.keys()){
        if(ui->punktgruppenListe->selectedItems().count() > 0 && i == ui->punktgruppenListe->selectedItems().at(0)){
            indexPathMap.value(i)->setPen(highlightPen);
        }else{
            indexPathMap.value(i)->setPen(normalPen);
        }
    }
    pointsGraphicsPath->setPen(ellipsePen);
    selectionEllipse->setPen(selectionPen);
}

void MenuTransparency::updatePoints(){
    QPainterPath pointsPath;
    //Ellipsen zeichnen
    foreach(QPoint p, selectedTransPoly){
        pointsPath.addEllipse(p, ellipseRadius / factor, ellipseRadius / factor);
    }
    pointsGraphicsPath->setPath(pointsPath);

    QPainterPath pp;
    if(selectedPointIndex > -1 && selectedPointIndex < selectedTransPoly.count()){
        pp.addEllipse(selectedTransPoly.at(selectedPointIndex),
                      selectionRadius / factor,
                      selectionRadius / factor);
    }
    selectionEllipse->setPath(pp);
}

void MenuTransparency::updateSelectedGraphicsPath(){
    if(ui->punktgruppenListe->selectedItems().count() == 1){
        ui->punktgruppenListe->selectedItems().at(0);
        QGraphicsPathItem *pi = indexPathMap.value(ui->punktgruppenListe->selectedItems().at(0));
        QPainterPath pp ;
        pp.addPolygon(selectedTransPoly);
        if(!drawTempLine) pp.closeSubpath();
        pi->setPath(pp);
        updatePoints();
    }
}

void MenuTransparency::on_punktgruppenListe_itemSelectionChanged()
{
    if(!drawTempLine && ui->punktgruppenListe->selectedItems().count() == 1){
        selectedTransPoly = QPolygonF(indexPathMap.value(ui->punktgruppenListe->selectedItems().at(0))->path().toSubpathPolygons().at(0)).toPolygon();
        selectedTransPoly.remove(selectedTransPoly.count() - 1);
        selectedPointIndex = -1;
        pointsGraphicsPath->setVisible(true);
        updatePoints();
        updatePens();
    }
}

QList<Linie> MenuTransparency::getTransPunktgruppen(){
    QList<Linie> ret;
    foreach(QGraphicsPathItem *pi, indexPathMap.values()){
        QPolygon poly = pi->path().toSubpathPolygons().at(0).toPolygon();
        if(poly.count() > 1) poly.remove(poly.count() - 1);
        Linie l;
        foreach(QPoint p, poly) l.append(p);

        ret.append(l);
    }
    return ret;

}
