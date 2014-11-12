#include "managescansdialog.h"
#include "ui_managescansdialog.h"

ManageScansDialog::ManageScansDialog(Project *p, QGLWidget *glwidget, QWidget *parent) : QDialog(parent),
    ui(new Ui::ManageScansDialog)
{
    this->parent = parent;
    project = p;
    ui->setupUi(this);
    glw = glwidget;
    setWindowTitle(tr("Scans verwalten"));
    elementmodel = new ElementModel(this);
//    setupTree();
//    scanListDelegate = new GruppenItemDelegate(ui->listView);

    ui->scanView->setIconSize(QSize(150,150));
    ui->scanView->setAlternatingRowColors(true);
    ui->scanView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->scanView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->scanView->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    ui->scanView->setContextMenuPolicy(Qt::CustomContextMenu);

    //    ui->texturesView->setEnabled(true);
    ui->texturesView->setIconSize(QSize(150,150));
    ui->texturesView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->texturesView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->texturesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->texturesView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->deleteScanButton, SIGNAL(clicked()), this, SLOT(deleteScan()));
    connect(ui->deleteTextureButton, SIGNAL(clicked()), this, SLOT(deleteTexture()));

    connect(ui->scanView, SIGNAL(clicked(QModelIndex)), this, SLOT(setTextureRoot(QModelIndex)));

//    connect(ui->gruppenView, SIGNAL(customContextMenuRequested( const QPoint& )), this, SLOT(showContextMenu(const QPoint &)));

}

void ManageScansDialog::loadScanContainer(ContScans *scans){
    scancontainer = scans;
    scansDir = scans->getScansDir();
//    fillTreeModel(scans->getScans());
}

void ManageScansDialog::setModel(ElementModel *em){
    elementmodel = em;
    ui->scanView->setModel(em);
    ui->scanView->setIconSize(QSize(150,150));
    ui->scanView->setRootIndex(em->index(0, 0));

//    ui->texturesView->setModel(em);

//    ui->scanView->setCurrentIndex(em->index(0,0, ui->scanView->rootIndex()));
//    ui->texturesView->setEnabled(false);
}


ManageScansDialog::~ManageScansDialog()
{
    delete ui;
}

void ManageScansDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//void ManageScansDialog::saveScan(Scan *s){
//    //Wenn -1 zurückkommt, dann wurde der Scan erst hinzugefügt
//    int index = scancontainer->saveScan(s);
//    if(index == -1) addScanToModel(s);
////    else updateModelAtIndex(index);
//}

//QStandardItem *ManageScansDialog::makeBranch(Scan *s){
//    QStandardItem *si = new QStandardItem(s->getThumbnailIcon(), s->getName());
//    foreach(Textur *t, s->getTextures()){
////        qDebug() << t->getName();
//        QStandardItem *textur = new QStandardItem(t->getThumbnailIcon(), t->getName());
//        si->appendRow(textur);
//    }
//    return si;
//}

void ManageScansDialog::addScanToModel(Scan *s){
//    QStandardItem *item = makeBranch(s);
//    model->appendRow(item);
}

//void ManageScansDialog::on_saveButton_clicked(){
//    saveScans();
//}
//
//void ManageScansDialog::on_openButton_clicked(){
//    loadScans();
//}

//bool ManageScansDialog::saveScans(){
//    if (QMessageBox::question(this, tr("Projekt überschreiben?"), QString("Soll das Projekt in ") + scansDir + QString(" überschrieben werden?"), QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
//        try{
//            //Bilder speichern
//            QString error = scancontainer->saveToXML();
//            if(!error.isNull()) throw error;
//        }
//        catch (QString error){
//            QMessageBox::critical(this,
//                                  tr("Fehler beim Speichern"),
//                                  error,
//                                  QMessageBox::Ok);
//            return false;
//        }
//    }
//    return true;
//}

//bool ManageScansDialog::loadScans(){
//    QString valid("Pantora Scan-XML(*.xml)");
//    QString fileName = QFileDialog::getOpenFileName(this,
//                                                    tr("Open File"), QDir::currentPath(), valid);
//    if (fileName.isEmpty()) return false;
//    scancontainer->setXmlFile(fileName);
//    QString error = scancontainer->loadFromXML(QFileInfo(fileName).absolutePath());
//    if(error != NULL) {
//        //Nachricht bei Fehler
//        QMessageBox::critical(this,
//                              "Load from XML::parseXML",
//                              error,
//                              QMessageBox::Ok);
//        return false;
//    }
//    fillTreeModel(scancontainer->scans);
//    return true;
//}

//void ManageScansDialog::deleteTexture(int index){
//    elementmodel->removeRow(index, selectedScan);
//}

bool ManageScansDialog::loadFromXml(){
//    try{
//        QString error = scancontainer->loadFromXML();
//        if(!error.isNull()) throw QString("Fehler beim Laden aus XML");
//    }catch (QString s){
//        QMessageBox::critical(this, tr("Fehler beim Laden der Scans"), s, QMessageBox::Ok);
//        return false;
//    }
//    return true;
}

void ManageScansDialog::textureUpdated(Textur *t){
    t->GLupdate(glw);
    glw->update();
}

void ManageScansDialog::show(){
    QDialog::show();
}


void ManageScansDialog::on_addScan_clicked(){
    //Bild auswählen
    scansIndex = elementmodel->index(0,0);
    QString filename = loadImageDialog(lastDir);
    if (!filename.isNull()){
        ScanEditWidget *sw = new ScanEditWidget(scansIndex, project->getScansDir(), filename, this);
        //toDo: Scancontainer komplett entfernen: hier backup für save

        sw->setModal(true);
//        sw->show();
        sw->exec();
    }
}

void ManageScansDialog::on_scanView_doubleClicked(const QModelIndex &index)
{
//    AbstractElement *e = elementmodel->getItem(index);
    //Nur DisplayWidget (Scan- und Textureneditor) öffnen
    ScanEditWidget *sw = new ScanEditWidget(index, this);

    sw->setModal(true);
//    sw->show();
    sw->exec();
}

void ManageScansDialog::on_texturesView_doubleClicked(const QModelIndex &index)
{
    if(!index.isValid()) return;
    TextureEditWidget *tw = new TextureEditWidget(index, this);
    connect(tw, SIGNAL(updated(Textur*)), this, SLOT(textureUpdated(Textur*)));
    tw->setModal(true);
//    tw->show();
    tw->exec();
}

void ManageScansDialog::setTextureRoot(QModelIndex i){
    if(ui->texturesView->model() != elementmodel)     ui->texturesView->setModel(elementmodel);

    if(i.isValid()){
        ui->texturesView->setRootIndex(elementmodel->index(0, 0, i));
    }
}

QString ManageScansDialog::loadImageDialog(QString dir){
    if(dir.isNull()) dir = QDir::currentPath();
    lastDir = dir;
    qDebug() << lastDir;

    QString valid("Images (");
    foreach(QByteArray ba, QImageReader::supportedImageFormats()){
        valid.append("*." + ba + " ");
    }

    valid.chop(1);
    valid.append(")");
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), dir, valid);
    if (fileName.isEmpty())  return fileName;

    dir = QFileInfo(fileName).absolutePath();
    lastDir = dir;
//    *fn = filename;

//    renderArea->setImage(fileName);

//    activateMenu(true);
    return fileName;
}

void ManageScansDialog::deleteScan(){
    QPersistentModelIndex i = ui->scanView->currentIndex();
    if(i.isValid()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Scan löschen"), tr("Soll der Scan und seine gesamten Zeichnungen inklusive Befundgrenzen wirklich gelöscht werden?"),
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if(i.isValid()){
              ui->scanView->model()->removeRow(i.row(), i.parent());
              ui->scanView->setRootIndex(elementmodel->index(0, 0));
              ui->texturesView->setModel(new ElementModel());
              emit updateGl();
            }
        }
    }
}

void ManageScansDialog::deleteTexture(){
    QPersistentModelIndex i = ui->texturesView->currentIndex();
    if(i.isValid()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Zeichnung löschen"), tr("Soll die Zeichnung inklusive Befundlisten wirklch gelöscht werden?"),
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if(i.isValid()){
              ui->texturesView->model()->removeRow(i.row(), i.parent());
              emit updateGl();
            }
        }
    }
}
