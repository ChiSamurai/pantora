#include "menuclip.h"
#include "ui_menuclip.h"

MenuClip::MenuClip(const QModelIndex &i, QGraphicsScene *s, QWidget *parent) : EditMenu(i, parent),
    ui(new Ui::MenuClip)
{
    ui->setupUi(this);

    index = i;
    model = (ElementModel*) i.model();
    scene = s;

    tempLine = false;
    selectedPoint = -1;

    _textur = (Textur*)model->getItem(i);
    lineWidth = LINE_WIDTH;

    linePen = QPen(Qt::red);
    linePen.setWidth(lineWidth);

    //    QRegExp pattern( "(-)?[0-9]+[,.][0-9]*" );
//    QValidator* validator = new QRegExpValidator( pattern, this );
    QValidator *validator = new QDoubleValidator(this);

    ui->AGlobx->setValidator(validator);
    ui->AGloby->setValidator(validator);
    ui->AGlobz->setValidator(validator);
    ui->AGlobx->setText(QString("0.000"));
    ui->AGloby->setText(QString("0.000"));
    ui->AGlobz->setText(QString("0.000"));
    ui->pixelAx->setEnabled(false);
    ui->pixelAy->setEnabled(false);

    ui->BGlobx->setValidator(validator);
    ui->BGloby->setValidator(validator);
    ui->BGlobz->setValidator(validator);
    ui->BGlobx->setText(QString("0.000"));
    ui->BGloby->setText(QString("0.000"));
    ui->BGlobz->setText(QString("0.000"));
    ui->pixelBx->setEnabled(false);
    ui->pixelBy->setEnabled(false);

    toggleUIItems(false);
//    ui->planum->setChecked(true);

    ui->typ->setId(ui->planum, 0);
    ui->typ->setId(ui->profil, 1);

    //Texturinformationen einsetzen
    ui->name->setText(_textur->getName());

    einA = _textur->getEinA();
    einB = _textur->getEinB();

    clipPointFontSize = 18;
    clipPointFont.setPointSize(clipPointFontSize);
    clipLine = scene->addLine(einA.x(), einA.y(), einB.x(), einB.y());
    clipPointA = scene->addText("A", clipPointFont);
    clipPointB = scene->addText("B", clipPointFont);
    clipPointA->setPos(einA.koords_pixel);
    clipPointB->setPos(einB.koords_pixel);

    setClipPoints(einA, einB);

    if(_textur->getTyp() == Textur::Profil) ui->profil->setChecked(true);
    else ui->planum->setChecked(true);

    if(einA.koords_pixel == einB.koords_pixel){
        clipLine->setVisible(false);
        clipPointA->setVisible(false);
        clipPointB->setVisible(false);
    }

    activated = false;


//        clipLine = scene->addLine(einA.koords_pixel.x(), einA.koords_pixel.y(), einB.koords_pixel.x(), einB.koords_pixel.y(), linePen);
//        clipLine->setVisible(true);
//    connect(ui->typ, SIGNAL(buttonClicked(int)), this, SLOT(typ_changed(int)));
}


MenuClip::~MenuClip()
{
    delete ui;
}

void MenuClip::changeEvent(QEvent *e)
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

void MenuClip::setPixelCoords(int pId, QPoint p){
    switch (pId){
    case 0:
        ui->pixelAx->setText(QString::number(p.x()));
        ui->pixelAy->setText(QString::number(p.y()));
        ui->AGlobx->setDisabled(false);
        ui->AGloby->setDisabled(false);
        ui->AGlobz->setDisabled(false);
        ui->globLoeschen->setDisabled(false);
        break;
    case 1:
        ui->pixelBx->setText(QString::number(p.x()));
        ui->pixelBy->setText(QString::number(p.y()));
        ui->BGlobx->setDisabled(false);
        ui->BGloby->setDisabled(false);
        ui->BGlobz->setDisabled(false);
        ui->globLoeschen->setDisabled(false);
        break;
    }
}

void MenuClip::on_pixelLoeschen_clicked()
{
    ui->pixelAx->setText(QString(""));
    ui->pixelAy->setText(QString(""));

    ui->pixelBx->setText(QString(""));
    ui->pixelBy->setText(QString(""));

    einA.koords_pixel.setX(0.0);
    einA.koords_pixel.setY(0.0);

    einB.koords_pixel.setX(0.0);
    einB.koords_pixel.setY(0.0);

    clipLine->setLine(0.0, 0.0, 0.0, 0.0);
    clipLine->setVisible(false);
    clipPointA->setVisible(false);
    clipPointB->setVisible(false);


//    emit clearPixelCoords();
}

void MenuClip::on_globLoeschen_clicked()
{
    ui->AGlobx->setText(QString("0.000"));
    ui->AGloby->setText(QString("0.000"));
    ui->AGlobz->setText(QString("0.000"));
//    emit setCoord(0, QVector3D(0,0,0));

    ui->BGlobx->setText(QString("0.000"));
    ui->BGloby->setText(QString("0.000"));
    ui->BGlobz->setText(QString("0.000"));
//    emit setCoord(1, QVector3D(0,0,0));
}

void MenuClip::setClipPoints(Einhaengepunkt einA, Einhaengepunkt einB){
    ui->pixelAx->setText(QString::number(einA.koords_pixel.x()));
    ui->pixelAy->setText(QString::number(einA.koords_pixel.y()));

    ui->pixelBx->setText(QString::number(einB.koords_pixel.x()));
    ui->pixelBy->setText(QString::number(einB.koords_pixel.y()));

    QString temp;

    ui->AGlobx->setText(temp.setNum(einA.x(), 'f', 3));
    ui->AGloby->setText(temp.setNum(einA.y(), 'f', 3));
    ui->AGlobz->setText(temp.setNum(einA.z(), 'f', 3));

    ui->BGlobx->setText(temp.setNum(einB.x(), 'f', 3));
    ui->BGloby->setText(temp.setNum(einB.y(), 'f', 3));
    ui->BGlobz->setText(temp.setNum(einB.z(), 'f', 3));

    if(einA.koords_pixel != einB.koords_pixel){
        clipLine->setLine(einA.koords_pixel.x(), einA.koords_pixel.y(), einB.koords_pixel.x(), einB.koords_pixel.y());
        clipLine->setVisible(true);
        clipPointA->setPos(einA.koords_pixel);
        clipPointB->setPos(einB.koords_pixel);
        clipPointA->setVisible(true);
        clipPointB->setVisible(true);
    }

    toggleUIItems(true);
}

void MenuClip::toggleUIItems(bool enable){
    ui->AGlobx->setEnabled(enable);
    ui->AGloby->setEnabled(enable);
    ui->AGlobz->setEnabled(enable);

    ui->BGlobx->setEnabled(enable);
    ui->BGloby->setEnabled(enable);
    ui->BGlobz->setEnabled(enable);

    ui->globLoeschen->setEnabled(enable);
}

void MenuClip::setTyp(int t){
    if (t == 0) ui->planum->setChecked(true);
    else ui->profil->setChecked(true);
}

int MenuClip::getTyp(){
    return ui->typ->checkedId();
}

//void MenuClip::setName(QString n){
//    ui->name->setText(n);
//}

QString MenuClip::getName(){
    return ui->name->text();
}

void MenuClip::updatePens(){
    clipLine->setPen(linePen);
    clipPointA->setFont(clipPointFont);
    clipPointB->setFont(clipPointFont);
}

void MenuClip::factorUpdate(qreal f){
    if (f < 1){
        linePen.setWidth(lineWidth / f);
        clipPointFont.setPointSize(clipPointFontSize / f);

    }
    else {
        linePen.setWidth(lineWidth);
        clipPointFont.setPointSize(clipPointFontSize);
    }
    updatePens();
}

void MenuClip::newSelectionRect(QRect sr){
    if(activated){
        //Noch keine PixelKoordinaten gesetzt
        if(einA.koords_pixel.isNull() && einB.koords_pixel.isNull()){
            //Mittelpunkt des SelRects als koordinaten für einA und einB
            einA.koords_pixel.setX(sr.x() + sr.width() / 2);
            einA.koords_pixel.setY(sr.y() + sr.height() / 2);
            ui->pixelAx->setText(QString::number(einA.koords_pixel.x()));
            ui->pixelAy->setText(QString::number(einA.koords_pixel.y()));

            clipPointA->setPos(einA.koords_pixel);

            selectedPoint = 1;
            tempLine = true;
            clipLine->setVisible(true);
            clipPointA->setVisible(true);
            clipPointB->setVisible(true);

        }
        //einA bereits gewählt, setze einB
        else if(tempLine){
            einB.koords_pixel.setX(sr.x() + (sr.width() / 2));
            einB.koords_pixel.setY(sr.y() + (sr.height() / 2));
            clipPointB->setPos(einB.koords_pixel);

            selectedPoint = -1;
            tempLine = false;
        }

        else if(clipLine->isVisible()){
            //einA liegt im SelectionRect
            if(sr.contains(einA.koords_pixel)){
                selectedPoint = 0;
            }
            //einB liegt im SelectionRect
            else if(sr.contains(einB.koords_pixel)) selectedPoint = 1;
            else selectedPoint = -1;
        }
    }
}

void MenuClip::newCoordsForPoint(QPoint p){
//    qDebug() << p;
    if(activated){
        if (!tempLine && clipLine->isVisible()){
            if (selectedPoint == 0){
                einA.koords_pixel = p;
                ui->pixelAx->setText(QString::number(einA.koords_pixel.x()));
                ui->pixelAy->setText(QString::number(einA.koords_pixel.y()));
                clipPointA->setPos(einA.koords_pixel);
            }
            else if (selectedPoint == 1){
                einB.koords_pixel = p;
                ui->pixelBx->setText(QString::number(einB.koords_pixel.x()));
                ui->pixelBy->setText(QString::number(einB.koords_pixel.y()));
                clipPointB->setPos(einB.koords_pixel);
            }
            updateLine();
        }
    }
}

void MenuClip::newMousePos(QPoint p){
    if(activated){
        if(tempLine){
            einB.koords_pixel = p;
            ui->pixelBx->setText(QString::number(einB.koords_pixel.x()));
            ui->pixelBy->setText(QString::number(einB.koords_pixel.y()));
            clipPointB->setPos(einB.koords_pixel);

            updateLine();
        }
    }
}

void MenuClip::selectionStopped(QMouseEvent *event){
    if(activated){
        if(event->button() == Qt::LeftButton){
            if(!tempLine)
                selectedPoint = -1;
        }
    }
}

void MenuClip::updateLine(){
    clipLine->setLine(einA.koords_pixel.x(),
                      einA.koords_pixel.y(),
                      einB.koords_pixel.x(),
                      einB.koords_pixel.y());
    clipPointA->setPos(einA.koords_pixel);
    clipPointB->setPos(einB.koords_pixel);

}

void MenuClip::setActivated(bool activate){
    activated = activate;
    //Menu bekommt focus
    if(activate){
        if(!einA.koords_pixel.isNull() && !einA.koords_pixel.isNull()){
            clipLine->setVisible(activate);
            clipPointA->setVisible(activate);
            clipPointB->setVisible(activate);
        }
    //Menu verliert focus
    } else {
        if(tempLine){
            einA.koords_pixel = QPoint(0.0, 0.0);
            einB.koords_pixel = QPoint(0.0, 0.0);
            tempLine = false;
        }
        clipLine->setVisible(false);
        clipPointA->setVisible(false);
        clipPointB->setVisible(false);
    }
}

Einhaengepunkt MenuClip::getEin(einhaengepunktLabel el){
    Einhaengepunkt e;
    if (el == A){
        e.setX(ui->AGlobx->text().toFloat());
        e.setY(ui->AGloby->text().toFloat());
        e.setZ(ui->AGlobz->text().toFloat());

        e.koords_pixel.setX(ui->pixelAx->text().toFloat());
        e.koords_pixel.setY(ui->pixelAy->text().toFloat());
    }else{
        e.setX(ui->BGlobx->text().toFloat());
        e.setY(ui->BGloby->text().toFloat());
        e.setZ(ui->BGlobz->text().toFloat());

        e.koords_pixel.setX(ui->pixelBx->text().toFloat());
        e.koords_pixel.setY(ui->pixelBy->text().toFloat());
    }
    return e;
}

void MenuClip::on_showScanPic_clicked()
{
    QPersistentModelIndex texturenIndex = model->parent(index);
    QPersistentModelIndex scanIndex = model->parent(texturenIndex);

    Scan *s = (Scan*)model->getItem(scanIndex);

    QDialog *d = new QDialog(this);
    QGridLayout *layout = new QGridLayout(d);

    RenderArea *scanWindow = new RenderArea(d);
    scanWindow->setImage(s->getImage());
    layout->addWidget(scanWindow, 0, 0);

    d->setLayout(layout);
    d->resize(800, 600);
    d->show();
}
