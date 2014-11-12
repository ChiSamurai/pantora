#include "texturerenderarea.h"

TextureRenderArea::TextureRenderArea(const QModelIndex &i, QWidget *parent) : RenderArea(parent)
{
    model = (ElementModel*) i.model();
    index = i;

    //Index der Befundgrenzengruppe holen
    befGrenzenIndex = model->index(0,0, index);

    pointtolerance = 10;

    closeLine = false;
    pointDragFlag = false;
    loadTexture(i);

}

TextureRenderArea::~TextureRenderArea(){
    delete scene;
}

void TextureRenderArea::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPointF pos = mapToScene(event->pos());
        pointDragFlag = true;
        mousePos = mapToScene(event->pos()).toPoint();
        QRect selectRect(pos.x() - pointtolerance / getFactor(), pos.y() - pointtolerance / getFactor(), (pointtolerance / getFactor()) * 2, (pointtolerance / getFactor()) * 2);
        emit selectionRect(selectRect); //Signal: Im richtigen Verhältnis aufgespanntes "selectRect"
    }
}


void TextureRenderArea::mouseMoveEvent ( QMouseEvent * event ){
    QPointF pos = mapToScene(event->pos());
    int button = event->buttons();
    if (button ==  Qt::LeftButton){
        emit newPointForSelection(pos.toPoint());
    }
    emit newMousePos(pos.toPoint());
    QGraphicsView::mouseMoveEvent(event);
}

void TextureRenderArea::mouseReleaseEvent ( QMouseEvent * event ){
//    int button = event->button();
    pointDragFlag = false;
//    updateDrawing();
    emit mouseReleased(event);
}

void TextureRenderArea::loadTexture(QModelIndex i){
//    changeModus(Clip);
    _textur = (Textur*)((ElementModel*)i.model())->getItem(i);

    setImage(_textur->getImage());

}

//void TextureRenderArea::changeModus(int m){
//    scene->clearSelection();
//    modus = (Mode)m;
//    //Aktionen beenden
//    switch (modus){
//        case Line:
//            break;
//        case Transparency:
//            break;
//        case Cut:
//            break;
//        case Clip:
//            //Clipping-Szene zeichnen
//            break;
//        }
//}

void TextureRenderArea::clearSelection(){
    scene->clearSelection();
}
