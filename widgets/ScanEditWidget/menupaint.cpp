#include "menupaint.h"
#include "ui_menupaint.h"

MenuPaint::MenuPaint(ElementModel *em, QGraphicsScene *s, QWidget *parent) : QWidget(parent),
    ui(new Ui::MenuPaint)
{
    ui->setupUi(this);
    factor = 1;

    model = em;
    scene = s;

    ellipseRadius = 3;
    selectionRadius = 10;

    //Index der Befundgrenzengruppe holen
    //Model für ListView Setzen
    ui->befundgrenzenList->setSelectionMode(QListView::SingleSelection);
    ui->befundgrenzenList->setModel(model);

//    ui->befundgrenzenList->setContextMenuPolicy(Qt::CustomContextMenu);

    //Moduswechsler füllen
    ui->modus->addItem(tr("neu zeichnen"));
    ui->modus->addItem(tr("bearbeiten"));

    ui->befundgrenzenList->setEnabled(false);
    ui->changeColor->setEnabled(false);
    ui->copyButton->setEnabled(false);

    QPixmap iconPm = QPixmap(32, 32);
    iconPm.fill(Qt::gray);
    colorButtonIcon = QIcon(iconPm);
    ui->changeColor->setIcon(colorButtonIcon);

    //Stifte
    nPwidth = 1;
    hPwidth = 2;
    normalPen = QPen(Qt::blue, nPwidth);
    highlightPen = QPen(Qt::blue, hPwidth);
    ellipsePen = QPen(Qt::blue, nPwidth);
    selectionPen = QPen(Qt::red, nPwidth, Qt::DashLine );

    fillColor = Qt::red;
    fillColor.setAlpha(50);

    //Auswahl
    QPainterPath hellipse;
    hellipse.addEllipse(0, 0, selectionRadius, selectionRadius);
    selectionEllipse = scene->addPath(hellipse);
    selectionEllipse->setVisible(false);
    selectionEllipse->setPen(selectionPen);

    selectedPointIndex = -1;

    //Grabber-Points
    pointsGraphicsPath = scene->addPath(QPainterPath(), normalPen);

    //Befundgrenzen auf Szene zeichnen
    drawBefGrenzen();

    changeModus(New);

    connect(ui->modus, SIGNAL(currentIndexChanged(int)), this, SLOT(changeModus(int)));
    connect(ui->deleteLine, SIGNAL(clicked()), this, SLOT(deleteSelectedItem()));
    drawTempLine = false;
}

MenuPaint::~MenuPaint()
{
    delete ui;
}

void MenuPaint::changeEvent(QEvent *e)
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

void MenuPaint::changeModus(int modus){
    ui->modus->setCurrentIndex(modus);
    ui->befundgrenzenList->clearSelection();
    //Wenn editieren ausgewählt: Buttons enablen
    if(modus == Edit){
        ui->addPoint->setEnabled(true);
        ui->deletePoint->setEnabled(true);
        ui->deleteLine->setEnabled(true);
        ui->befundgrenzenList->setEnabled(true);
        ui->changeColor->setEnabled(true);
        ui->copyButton->setEnabled(true);

    }else{
        ui->addPoint->setDisabled(true);
        ui->deletePoint->setDisabled(true);
        ui->deleteLine->setDisabled(true);
        ui->befundgrenzenList->setDisabled(true);
        ui->closedLine->setChecked(false);
        ui->changeColor->setEnabled(false);
        ui->copyButton->setEnabled(false);
    }
    selectedPointIndex = -1;
    selectionPolygon.clear();
    selectedPathIndex = QModelIndex();

    updatePens();
    updatePoints();
}


void MenuPaint::closeLineStatusChanged(bool status){
    ui->closedLine->setChecked(status);
}

void MenuPaint::on_closedLine_toggled(bool checked)
{
    QPainterPath newPath;
    if(ui->modus->currentIndex() == Edit && selectedPathIndex.isValid()){
        newPath.addPolygon(selectionPolygon);
        if(checked){
            ((Linie*)(model->getItem(selectedPathIndex)))->closed = true;
            newPath.closeSubpath();
//            if(selectionPolygon.last() != selectionPolygon.first()) selectionPolygon.append(QPoint(selectionPolygon.at(0)));
        }else{
            ((Linie*)(model->getItem(selectedPathIndex)))->closed = false;
//            if(selectionPolygon.last() == selectionPolygon.first()) selectionPolygon.remove(selectionPolygon.count() -1);
        }
        indexPathMap.value(selectedPathIndex)->setPath(newPath);

    }
}

void MenuPaint::on_addPoint_clicked(){
    if(selectedPointIndex > -1){
        if (selectedPointIndex == selectionPolygon.count() - 1){
            selectionPolygon.append((selectionPolygon.last() + selectionPolygon.first()) / 2 );
        } else {
            selectionPolygon.insert(selectedPointIndex + 1, (selectionPolygon.at(selectedPointIndex) + selectionPolygon.at(selectedPointIndex + 1)) / 2);
        }
        QPainterPath newPath;
        newPath.addPolygon(selectionPolygon);
        if (((Linie*)(model->getItem(selectedPathIndex)))->closed == true) newPath.closeSubpath();
        indexPathMap.value(selectedPathIndex)->setPath(newPath);

        updatePoints();
        updateItem();
    }
}

void MenuPaint::on_deletePoint_clicked()
{
    if(selectedPointIndex > -1 && selectedPointIndex < selectionPolygon.count() && selectionPolygon.count() > 1){
        selectionPolygon.remove(selectedPointIndex);
        QPainterPath newPath;
        newPath.addPolygon(selectionPolygon);
        if (((Linie*)(model->getItem(selectedPathIndex)))->closed == true) newPath.closeSubpath();
        indexPathMap.value(selectedPathIndex)->setPath(newPath);

        selectedPointIndex = -1;
        selectionEllipse->setVisible(false);

        updatePoints();
        updateItem();
    }

//    emit deletePoint();
}

void MenuPaint::on_befundgrenzenList_clicked(const QModelIndex &index)
{
    Linie *l = (Linie*)model->getItem(index);
    selectedPathIndex = index;
    //setze Polygon
    selectionPolygon = *l;
    if(l->closed) ui->closedLine->setChecked(true);
    else ui->closedLine->setChecked(false);

    selectedPointIndex = -1;

    ui->changeColor->setEnabled(true);
    QPixmap iconPm = QPixmap(32, 32);
    iconPm.fill(l->getColor());
    colorButtonIcon = QIcon(iconPm);
    ui->changeColor->setIcon(colorButtonIcon);


    //Ellipsen updaten
    updatePoints();
    updatePens();
//    emit selectionChanged(index);
}

void MenuPaint::newSelectionRect(QRect sr){
    if(activated){
        if(ui->modus->currentIndex() == Edit && selectedPathIndex.isValid()){
            // *** enthält SelectionRect einen Punkt des ausgewählten Polygons?
            selectedPointIndex = -1;
            for(int i = 0; i < selectionPolygon.count(); i++){
                if(sr.contains(selectionPolygon.at(i))){
                    selectedPointIndex = i;
                    QPainterPath hellipse;
                    hellipse.addEllipse(selectionPolygon.at(i), selectionRadius / factor, selectionRadius / factor);
                    selectionEllipse->setPath(hellipse);
                    selectionEllipse->setVisible(true);
                    continue;
                }
            }
        }else if(ui->modus->currentIndex() == New && !drawTempLine){
            // *** Neues Polygon zeichnen
            selectionPolygon.clear();
            selectionPolygon.append(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            selectionPolygon.append(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));

            QPainterPath newPath;
            newPath.addPolygon(selectionPolygon);

            Linie *newLine = new Linie("", model->getItem(befGrenzenIndex));
            newLine->setName(tr("Neue Befundgrenze"));
            if(ui->closedLine->isChecked()) newLine->closed = true;

            QGraphicsPathItem *newPathItem = scene->addPath(newPath, normalPen);

            model->insertChild(newLine, befGrenzenIndex);

            QPersistentModelIndex newPathIndex = model->index(model->rowCount(befGrenzenIndex) - 1, 0, befGrenzenIndex);
            indexPathMap.insert(newPathIndex, newPathItem);
            selectedPathIndex = newPathIndex;

            selectedPointIndex = selectionPolygon.count() - 1;
            drawTempLine = true;
            updatePoints();

        } else if(drawTempLine && selectedPathIndex.isValid()){
            // *** Temporäre Linie "fixieren"
            //Gewählten Punkt "Fixieren"
            selectionPolygon.setPoint(selectedPointIndex, QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            //Neuen Punkt hinzufügen
            selectionPolygon.append(QPoint(sr.x() + sr.width() / 2, sr.y() + sr.height() / 2));
            selectedPointIndex = selectionPolygon.count() - 1;

            updateSelectedGraphicsPath();
        }
    }
}

void MenuPaint::newCoordsForPoint(QPoint p){
    if(!drawTempLine && selectedPathIndex.isValid() && selectedPointIndex > -1){
        QGraphicsPathItem * pi = indexPathMap.value(selectedPathIndex);

        if(ui->modus->currentIndex() == Edit){
            selectionPolygon.setPoint(selectedPointIndex, p);
        }
        QPainterPath pp ;
        pp.addPolygon(selectionPolygon);
        if (((Linie*)(model->getItem(selectedPathIndex)))->closed == true) pp.closeSubpath();
        pi->setPath(pp);
        updateItem();

//        QPainterPath hellipse;
//        hellipse.addEllipse(selectionPolygon.at(selectedPointIndex), ellipseRadius / factor, ellipseRadius / factor);
//        selectionEllipse->setPath(hellipse);
        updatePoints();
    }
}

void MenuPaint::newMousePos(QPoint p){
    if (drawTempLine && selectedPointIndex > -1){
        QGraphicsPathItem * pi = indexPathMap.value(selectedPathIndex);
        selectionPolygon.setPoint(selectedPointIndex, p);

        QPainterPath pp ;
        pp.addPolygon(selectionPolygon);
        if (ui->closedLine->isChecked()) pp.closeSubpath();
        pi->setPath(pp);
        updatePoints();
    }
}

void MenuPaint::selectionStopped(QMouseEvent *event){
    if(ui->modus->currentIndex() == New){
        if(event->button() == Qt::RightButton){
            if(selectionPolygon.count() > 1) selectionPolygon.remove(selectionPolygon.count() - 1);
            drawTempLine = false;
            selectedPointIndex = -1;
            updateSelectedGraphicsPath();
        }
    }
}

void MenuPaint::drawBefGrenzen(){
    //Befundgrenzen durchgehen
    for (int i = 0; i < model->rowCount(QModelIndex()); i++){
        QPersistentModelIndex thisBefGrenze = model->index(i, 0, befGrenzenIndex);
        Linie *l = (Linie*)model->getItem(thisBefGrenze);
        QPainterPath p;
        p.addPolygon(*l);
        if(l->closed) p.closeSubpath();
        QPen pen = QPen(normalPen);
        pen.setColor(l->getColor());
        indexPathMap.insert(thisBefGrenze, scene->addPath(p, pen));
    }
}

void MenuPaint::factorUpdate(qreal f){
    if (f < 1){
        factor = f;
        normalPen.setWidthF(nPwidth / f);
        highlightPen.setWidthF(hPwidth / f);
        ellipsePen.setWidthF(nPwidth / f);
        selectionPen.setWidthF(nPwidth / f);
    }
    else {
        factor = 1;
        normalPen.setWidthF(nPwidth);
        highlightPen.setWidthF(hPwidth);
        ellipsePen.setWidthF(nPwidth);
        selectionPen.setWidthF(nPwidth);
    }
    updatePens();
    updatePoints();
}

void MenuPaint::updatePens(){
    foreach(QPersistentModelIndex pathIndex, indexPathMap.keys()){
        if(pathIndex == selectedPathIndex){
            QPen pen = indexPathMap.value(pathIndex)->pen();
            pen.setWidthF(highlightPen.widthF());
            indexPathMap.value(pathIndex)->setPen(pen);
        }else{
            QPen pen = indexPathMap.value(pathIndex)->pen();
            pen.setWidthF(normalPen.widthF());
            indexPathMap.value(pathIndex)->setPen(pen);
        }
    }
    QPen pen = pointsGraphicsPath->pen();
    pen.setWidthF(normalPen.widthF());

    pointsGraphicsPath->setPen(pen);
    selectionEllipse->setPen(pen);
}

void MenuPaint::setActivated(bool activate){
    activated = activate;
    if(!activate){
        selectionEllipse->setVisible(false);
        selectedPointIndex = -1;
        if(drawTempLine && selectionPolygon.count() > 1)selectionPolygon.remove(selectionPolygon.count() - 1);
        updateSelectedGraphicsPath();
        pointsGraphicsPath->setVisible(false);
        drawTempLine = false;
        selectionPolygon.clear();
        selectedPathIndex = QModelIndex();
        updatePoints();
    } else {
        pointsGraphicsPath->setVisible(true);
        selectedPointIndex = -1;
        selectedPathIndex = QModelIndex();
        drawTempLine = false;
        updateSelectedGraphicsPath();
        updatePoints();
    }
    //Alle Befundgrenzen ein- bzw. ausblenden
    foreach(QGraphicsPathItem *pathItem, indexPathMap){
        pathItem->setVisible(activate);
    }
}

void MenuPaint::updateItem(){
    Linie *l = (Linie*)model->getItem(selectedPathIndex);
    QPolygon *linePoly = (QPolygon*)l;
    *linePoly = selectionPolygon;
}

void MenuPaint::updateSelectedGraphicsPath(){
    if(selectedPathIndex.isValid()){
        QGraphicsPathItem *pi = indexPathMap.value(selectedPathIndex);

        QPainterPath pp ;
        pp.addPolygon(selectionPolygon);
        if (ui->closedLine->isChecked()) pp.closeSubpath();
        pi->setPath(pp);
        updateItem();
        updatePoints();
    }
}

void MenuPaint::updatePoints(){
    pointsPath = QPainterPath();
    //Ellipsen zeichnen
    foreach(QPoint p, selectionPolygon){
        pointsPath.addEllipse(p, ellipseRadius / factor, ellipseRadius / factor);
    }
    pointsGraphicsPath->setPath(pointsPath);

    QPainterPath pp;
    if(selectedPointIndex > -1){
        pp.addEllipse(selectionPolygon.at(selectedPointIndex),
                      selectionRadius / factor,
                      selectionRadius / factor);
    }
    selectionEllipse->setPath(pp);
    if(!selectedPathIndex.isValid()){
        selectionEllipse->setVisible(false);
        pointsGraphicsPath->setVisible(false);
    }else{
        selectionEllipse->setVisible(true);
        pointsGraphicsPath->setVisible(true);
    }
}

void MenuPaint::on_befundgrenzenList_customContextMenuRequested(const QPoint &pos)
{
    QPersistentModelIndex clickedIndex = ui->befundgrenzenList->indexAt(pos);
    if(clickedIndex.isValid()) qDebug() << "index valid";
//    QMenu myMenu;
//    myMenu.addAction("Menu Item 1");

}

void MenuPaint::deleteSelectedItem(){
    QPersistentModelIndex i = ui->befundgrenzenList->currentIndex();
    if (i.isValid()){
        QGraphicsPathItem *gi = indexPathMap.value(i);
        //Aus Mapping entfernen
        indexPathMap.remove(i);
        //Aus Model entfernen
        model->removeRow(i.row(), i.parent());
        //QGraphicsPainterPath löschen
        scene->removeItem(gi);
        selectedPathIndex = QModelIndex();
        delete gi;

        updatePens();
        updatePoints();
    }
}

void MenuPaint::on_changeColor_clicked()
{
    if(selectedPathIndex.isValid()){
        Linie* l = (Linie*)model->getItem(selectedPathIndex);
        QColor newColor = QColorDialog::getColor(l->getColor(), this);

        QPixmap iconPm = QPixmap(32, 32);
        iconPm.fill(newColor);
        colorButtonIcon = QIcon(iconPm);
        ui->changeColor->setIcon(colorButtonIcon);
        l->setColor(newColor);

        QPen p = QPen(highlightPen);
        p.setColor(l->getColor());
        indexPathMap.value(selectedPathIndex)->setPen(p);

        updatePoints();
    }
}

void MenuPaint::on_copyButton_clicked()
{
    if(selectedPathIndex.isValid()){
        QGraphicsPathItem *pi = indexPathMap.value(selectedPathIndex);
//        QPersistentModelIndex thisBefGrenze = model->index(i, 0, befGrenzenIndex);
        Linie *l_orig = (Linie*)model->getItem(selectedPathIndex);
        Linie *l = new Linie();
        l->copyFrom(l_orig);
        l->setName("copy of " + l->getName());

//QPainterPath p;
//        p.addPolygon(*l);
//        if(l->closed) p.closeSubpath();
//        QPen pen = QPen(normalPen);
//        pen.setColor(l->getColor());

        QGraphicsPathItem *newPathItem = new QGraphicsPathItem(pi);

        model->insertChild(l, befGrenzenIndex);

        QPersistentModelIndex newPathIndex = model->index(model->rowCount(befGrenzenIndex) - 1, 0, befGrenzenIndex);
        indexPathMap.insert(newPathIndex, newPathItem);
        selectedPathIndex = newPathIndex;

        selectedPointIndex = - 1;
        updatePoints();
        updateSelectedGraphicsPath();
    }

}
