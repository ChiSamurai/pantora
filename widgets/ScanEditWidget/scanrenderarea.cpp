#include "scanrenderarea.h"

ScanRenderArea::ScanRenderArea(const QModelIndex &i, QWidget *parent) : RenderArea(parent)
{
    pointtolerance = 20;

    model = (ElementModel*) i.model();

    resizeFlag = -1;

    rPwidth = 2;
    hPwidth = 5;
    rectPen = QPen(Qt::red, rPwidth);
    highlightPen = QPen(Qt::red, hPwidth);

    fillColor = Qt::red;
    fillColor.setAlpha(50);

    //Scan laden
    loadScan(i);
}

ScanRenderArea::~ScanRenderArea(){
}


void ScanRenderArea::loadScan(QModelIndex index){
    changeModus(New);
    scan = (Scan*)((ElementModel*)index.model())->getItem(index);
    setImage(scan->getImage());

    //Texturrahmen zeichnen
    texturenIndex = model->index(0, 0, index);
    for(int i = 0; i < model->rowCount(texturenIndex); i++){
        QModelIndex thisTextureIndex = model->index(i, 0, texturenIndex);
        Textur *t = (Textur*) model->getItem(thisTextureIndex);
        QGraphicsRectItem *rect = scene->addRect(t->getRect(), rectPen, QBrush(fillColor, Qt::SolidPattern));
        rect->setFlag(QGraphicsItem::ItemIsSelectable);
        //In Rects->QModelIndex - Mapping einfügen
        rectsMap.insert(thisTextureIndex, rect);
        //ToDo: In QModelIndex (alt) <-> QModelIndex (neu) einfügen
    }
}


void ScanRenderArea::changeModus(int m){
    modus = (Mode)m;
    scene->clearSelection();
    updateDrawing();
}

//void ScanRenderArea::changeSubModus(int m){
//    subModus = (SubMode)m;
//}


int ScanRenderArea::getPointAtMousePos(QRect rect, QPoint pos){
//    qreal factor = matrix().m11();

    //Eckpunkte durchgehen
    QRect dragRect(pos.x() - pointtolerance / getFactor(), pos.y() - pointtolerance / getFactor(), (pointtolerance / getFactor()) * 2, (pointtolerance / getFactor()) * 2);
    //Wenn Rect der der Größe pointtolerance*2 x pointtolerance*2 mit Mittelpunkt mousePos eine der Ecken enthält, diese zurückgeben
    if(dragRect.contains(rect.topLeft())) return Qt::TopLeftCorner;
    else if(dragRect.contains(rect.topRight())) return Qt::TopRightCorner;
    else if(dragRect.contains(rect.bottomLeft())) return Qt::BottomLeftCorner;
    else if(dragRect.contains(rect.bottomRight())) return Qt::BottomRightCorner;

    return -1;
}

void ScanRenderArea::mouseMoveEvent ( QMouseEvent * event ){
    int button = event->buttons();
    mousePos = mapToScene(event->pos()).toPoint();
    //Ecke Ausgewählt
    if(button == Qt::LeftButton && resizeFlag > -1){
        //Größe ändern
        QGraphicsRectItem *gr = (QGraphicsRectItem*)scene->selectedItems().at(0);
        QRect r = gr->rect().toRect();
        //Ausgewählte Ecke ändern, wenn QRect irregulär werden würde
        switch(resizeFlag){
        case Qt::TopLeftCorner:
            if(mousePos.x() >= r.right()){
                resizeFlag = Qt::TopRightCorner;
                break;
            }
            if(mousePos.y() >= r.bottom()){
                resizeFlag = Qt::BottomLeftCorner;
                break;
            }
            r.setTopLeft(mousePos);
            break;
        case Qt::TopRightCorner:
            if(mousePos.x() <= r.left()){
                resizeFlag = Qt::TopLeftCorner;
                break;
            }
            if(mousePos.y() >= r.bottom()){
                resizeFlag = Qt::BottomRightCorner;
                break;
            }
            r.setTopRight(mousePos);
            break;
        case Qt::BottomLeftCorner:
            if(mousePos.x() >= r.right()){
                resizeFlag = Qt::BottomRightCorner;
                break;
            }
            if(mousePos.y() <= r.top()){
                resizeFlag = Qt::TopLeftCorner;
                break;
            }
            r.setBottomLeft(mousePos);
            break;
        case Qt::BottomRightCorner:
            if(mousePos.x() <= r.left()){
                resizeFlag = Qt::BottomLeftCorner;
                break;
            }
            if(mousePos.y() <= r.top()){
                resizeFlag = Qt::TopRightCorner;
                break;
            }
            r.setBottomRight(mousePos);
            break;
        }
//                gr->setRect(r.normalized());
        gr->setRect(r);
    }
    QGraphicsView::mouseMoveEvent(event);
}

void ScanRenderArea::mousePressEvent(QMouseEvent *event){
    QPointF pos = mapToScene(event->pos());
    if(modus == New){
        //neue Textur hinzufügen
        Textur *t = new Textur(scan->getScanPath(), QRect(pos.toPoint(), pos.toPoint()), model->getItem(texturenIndex));
        //Textur in Model einfügen
        model->insertChild(t, texturenIndex);

        //Modelindex der neuen Textur in Mapping einfügen
        QModelIndex i = model->index(model->rowCount(texturenIndex) - 1, 0, texturenIndex);
        QGraphicsRectItem *ri = scene->addRect(t->getRect(), rectPen, QBrush(fillColor, Qt::SolidPattern));
        rectsMap.insert(i, ri);
//        newRects.append(i);
        scene->clearSelection();
        ri->setFlag(QGraphicsItem::ItemIsSelectable);
        ri->setSelected(true);
        selectedIndex = i;
    }

    //Ausgewählten Ausschnit ändern
    if(scene->selectedItems().count() > 0){
        QGraphicsRectItem *i = (QGraphicsRectItem*)scene->selectedItems().at(0);
        QRect r = i->rect().toRect();
        //Testen, ob Ecken angeklickt

        resizeFlag = (Qt::Corner)getPointAtMousePos(r, pos.toPoint());
//                qDebug() << r << " = " << r.toRect();

//            if(subModus == Edit && actualRect){
//                qDebug() << scene->itemAt(mousePos);
//                hit = getPointAtMousePos(QRect(*actualRect), &mousePos);
//            }
    }
}

void ScanRenderArea::mouseReleaseEvent ( QMouseEvent * event ){
//    int button = event->button();
    if(modus == New){
        scene->clearSelection();
    }
    //Wenn Resize Flag, Textur updaten
    if(resizeFlag > -1){
        if(selectedIndex.isValid()){
            //hier Textur Updaten
            Textur *t = (Textur*)model->getItem(selectedIndex);
            t->setRect(rectsMap.value(selectedIndex)->rect().toRect());
        }
        resizeFlag = -1;
    }
    updateDrawing();
}

void ScanRenderArea::wheelEvent(QWheelEvent *event){
    RenderArea::wheelEvent(event);
    if(event->modifiers() == Qt::ControlModifier){
        updateDrawing();
    }
}

//void ScanRenderArea::saveScan(){
//    try{
////        if(!scan->saveScanImage(*image)) throw 0; //Scanbild speichern
//        if(!orig_scan->saveScan(image, scan)) throw 0; //Scaninformationen speichern
//    }
//    catch(int e){
//        QString errorText;
//        if(e == 0) errorText = tr("Speichern des Bildes fehlgeschlagen");

//        QMessageBox::critical(this, tr("Speichern fehlgeschlagen"), errorText);
//        return;
//    }
//    emit scanSaved(orig_scan);
//    QMessageBox::information(this, tr("Scan gespeichert"), tr("Scan und Bereiche wurde erfolgreich gespeichert."));
//}

void ScanRenderArea::updateDrawing(){
    updatePenWidth();
    foreach(QModelIndex i, rectsMap.keys()){
        QGraphicsRectItem *ri = rectsMap.value(i);
        if(ri->isSelected()){
//                ri->setBrush(ri->brush().setColor(Qt::green));
            ri->setPen(highlightPen);
        } else {
            ri->setPen(rectPen);
        }
    }
}

void ScanRenderArea::removeTexture(QPersistentModelIndex index){
    if(index.isValid()){
        QGraphicsRectItem *tr = rectsMap.value(index);
        scene->removeItem(tr);
        rectsMap.remove(index);
    }
}

void ScanRenderArea::setTextureSelected(QModelIndex &i){
    if(modus == Edit){
        scene->clearSelection();
        rectsMap.value(i)->setSelected(true);
        selectedIndex = i;
        updateDrawing();
    }
}

void ScanRenderArea::updatePenWidth(){
    if (getFactor() < 1){
        rectPen.setWidth(rPwidth / getFactor());
        highlightPen.setWidth(hPwidth / getFactor());
    }
    else {
        rectPen.setWidth(rPwidth);
        highlightPen.setWidth(hPwidth);
    }
}

void ScanRenderArea::factorUpdated(){
    updateDrawing();
}
