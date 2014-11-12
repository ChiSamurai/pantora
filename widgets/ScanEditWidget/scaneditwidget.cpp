#include "scaneditwidget.h"

ScanEditWidget::ScanEditWidget(const QModelIndex &i, QWidget *parent) :
        QDialog(parent)
{
    model = (ElementModel*)i.model();
    index = i;

    _origScan = (Scan*)model->getItem(i);

    //Original Scan kopieren
    _scan = new Scan(_origScan->getScansPath());
    _scan->setName(_origScan->getName());
    _scan->setUuid(_origScan->getUuid());
    _scan->setScanPath(_scan->getUuid());
//    _scan = new Scan(_origScan->getScanPath(), _origScan->getUuid());
    _scan->loadScanImage();

    _origTexturenIndex = model->index(0, 0, i);

    //Temporäres Model erstellen
    texturenListe = new ElementModel(this);
    Gruppe *texturenItem = new Gruppe("Texturen", "", "", _scan);
    _scan->appendChild(texturenItem);
    texturenListe->insertChild(_scan);
    _scanIndex = texturenListe->index(0, 0);
//    _texturenIndex = texturenListe->index(0, 0, _scanIndex);
    _tempTexturenIndex = texturenListe->index(0, 0, _scanIndex);

    //Temporäre Kopien erstellen
    //Texturen kopieren
    for(int c = 0; c < model->rowCount(_origTexturenIndex); c++){
        QPersistentModelIndex origTex = model->index(c, 0, _origTexturenIndex); //Originaler Index der Textur
        Textur *orig_t = (Textur*)model->getItem(origTex);
        Textur *t = orig_t->copy();
        t->makeTextureImage();
        t->setParent(texturenItem);
//        texturenItem->appendChild(t);
        texturenListe->insertChild(t, _tempTexturenIndex);
        QPersistentModelIndex newTex = texturenListe->index(texturenListe->rowCount(_tempTexturenIndex) - 1, 0, _tempTexturenIndex);
        indexOldToNewMap.insert(origTex, newTex);
//        QModelIndex testindex = indexOldToNewMap.value(origTex);
    }
    renderArea = new ScanRenderArea(_scanIndex, this);
    ms = new MenuSplit(_scanIndex, this);
    ms->setDebugViewModel(model);
    init();
}

ScanEditWidget::ScanEditWidget(QModelIndex scansIndex, QString scansDir, QString filename, QWidget *parent){
    model = (ElementModel*)scansIndex.model();
    _origScansIndex = scansIndex;
    QImage image(filename);
    _scan = new Scan(scansDir, image);
    _scan->setImage(image);

    //ToDo:: Texturengruppe besser in Scan.cpp erstellen?
    Gruppe *texturenItem = new Gruppe("Texturen", "TexturenGruppe", "", _scan);
    _scan->appendChild(texturenItem);

    texturenListe = new ElementModel(this);
    texturenListe->insertChild(_scan);
    _scanIndex = texturenListe->index(0, 0);
    renderArea = new ScanRenderArea(_scanIndex, this);

    ms = new MenuSplit(_scanIndex, this);
    ms->setDebugViewModel((ElementModel*)_origScansIndex.model());

    init();
}

void ScanEditWidget::init(){
    setMinimumHeight(400);
    setMinimumWidth(800);

    menuBar = new QMenuBar();
    mainLayout = new QGridLayout();

    menu = new QTabWidget(this);
    menu->setMinimumWidth(300);

    menu->insertTab(0, ms, tr("Pläne ausschneiden"));

    mainLayout->addWidget(renderArea, 0, 0);
    mainLayout->addWidget(menu, 0, 1);
    mainLayout->setColumnStretch(0, 10);

    setLayout(mainLayout);
    mainLayout->setMenuBar(menuBar);

    setWindowTitle(tr("Scan bearbeiten"));

    createActions();
    createMenus();
    createConnections();

    activateMenu(true);
}
//void ScanEditWidget::loadScan(Scan *s){
//    _scan = s;
//    renderArea->loadScan(s);
////    ms->setName(s->getName());

//    fillList(_scan);
//    activateMenu(true);
//}


void ScanEditWidget::createActions(){
//    openAct = new QAction(tr("&Bildatei öffnen..."), this);
//    openAct->setShortcut(tr("Ctrl+B"));
//    connect(openAct, SIGNAL(triggered()), this, SLOT(openImageClicked()));

//    saveAct = new QAction(tr("&Speichern..."), this);
//    saveAct->setShortcut(tr("Ctrl+S"));
//    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveScan()));
//    saveAct->setEnabled(false);

    exportAct = new QAction(tr("&Exportieren..."), this);
    exportAct->setShortcut(tr("Ctrl+E"));
//    connect(exportAct, SIGNAL(triggered()), this, SLOT(exportScan()));
    exportAct->setEnabled(false);

//    printAct = new QAction(tr("Drucken (STRG P)"), this);
//    printAct->setShortcut(tr("Ctrl+P"));
//    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
//    printAct->setEnabled(false);

    exitAct = new QAction(tr("Beenden"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom +"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), renderArea, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom -"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), renderArea, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normalgröße"), this);
    normalSizeAct->setShortcut(tr("Ctrl+N"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), renderArea, SLOT(zoomReset()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), renderArea, SLOT(zoomFull()));
}

void ScanEditWidget::createMenus()
{
    fileMenu = new QMenu(tr("&Datei"), this);
//    fileMenu->addAction(openAct);
//    fileMenu->addAction(saveAct);
    fileMenu->addAction(exportAct);
//    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&Ansicht"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(viewMenu);
}

void ScanEditWidget::createConnections(){
//    connect(renderArea, SIGNAL(newRect(QString,QRect)), ms, SLOT(addRect(QString,QRect)));
    connect(ms, SIGNAL(subModusChanged(int)), renderArea, SLOT(changeModus(int)));

    connect(ms, SIGNAL(textureActivated(QModelIndex&)), renderArea, SLOT(setTextureSelected(QModelIndex&)));

//    connect(ms, SIGNAL(deleteTexture(int)), this, SLOT(deleteTextureClicked(int)));
    connect(ms, SIGNAL(deleteTexture(QPersistentModelIndex)), renderArea, SLOT(removeTexture(QPersistentModelIndex)));

}

void ScanEditWidget::activateMenu(bool activate){
    viewMenu->setEnabled(activate);
    zoomInAct->setEnabled(activate);
    zoomOutAct->setEnabled(activate);
    fitToWindowAct->setEnabled(activate);
    normalSizeAct->setEnabled(activate);

//    saveAct->setEnabled(activate);

}

//void ScanEditWidget::fillList(Scan *s){
//    QList<QString> l = s->getTextureNameList();
//    ms->fillList(&l);
//}

void ScanEditWidget::deleteTextureClicked(int index){
//    _scan->removeTextureAt(index);
    emit textureDeleted(index);
//    renderArea->loadScan(_scan);
}

void ScanEditWidget::saveScan(){
//    _scan->setName(ms->getName());
//    renderArea->saveScan();
}

void ScanEditWidget::closeEvent(QCloseEvent *event){

//    QList<QModelIndex> newRects;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Editieren beenden");
    msgBox.setText(tr("Änderungen speichern?"));
//    msgBox.addButton(tr("Ja"), QMessageBox::YesRole);
//    msgBox.addButton(tr("Nein"), QMessageBox::NoRole);
//    msgBox.addButton(tr("Abbrechen"), QMessageBox::RejectRole);
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes );
    msgBox.setDefaultButton(QMessageBox::Yes);
    int result = msgBox.exec();
    switch (result) {
    case QMessageBox::Yes:
        //Änderungen Speichern!
        //Original Scan vorhanden?
        if(index.isValid()){
            //Name des Scans übernehmen
            model->getItem(index)->setData(0, ms->getName());

            //Mittels OldToNewMapping "alte" Texturen Updaten
            foreach(QPersistentModelIndex i, indexOldToNewMap.keys()){
                QPersistentModelIndex  newTexIndex = indexOldToNewMap.value(i);
                //ToDo: entfernen einer Textur
                if(newTexIndex.isValid()){
                    Textur* origT = (Textur*)((ElementModel*)i.model())->getItem(i);
                    Textur* newT = (Textur*)((ElementModel*)newTexIndex.model())->getItem(newTexIndex);
                    //Rect übernehmen
                    origT->setRect(newT->getRect());
                    //Name übernehmen
                    model->setData(i, newT->getName());
                }
            }
            // neue Texturen hinzufügen
            QPersistentModelIndex tempTexturenIndex = texturenListe->index(0, 0, _scanIndex);
            for(int i = 0; i < texturenListe->rowCount(tempTexturenIndex); i++){
                QPersistentModelIndex tempTIndex = texturenListe->index(i, 0, tempTexturenIndex);

                if(tempTIndex.isValid()){
                    bool found = false;
                    foreach(QPersistentModelIndex testIndex, indexOldToNewMap.values()){
                        if(tempTIndex == testIndex){
                            found = true;
                            continue;
                        }
                    }
                    //Textur nicht bekannt -> hinzufügen
                    if(!found){
                        Textur* tempT = (Textur*)model->getItem(tempTIndex);
                        Gruppe *origTexturesGroup = (Gruppe*)model->getItem(_origTexturenIndex);
                        Textur *saveT = new Textur(_origScan->getScanPath(), origTexturesGroup);
                        origTexturesGroup->appendChild(saveT);
                        saveT->setRect(tempT->getRect());
                        saveT->setName(tempT->getName());
                        saveT->texImageFromScan(_scan->getImage());
                    }
                }
            }
        }else{
            //Neuen Scan anlegen
            Scan *saveScan = new Scan(_scan->getName(), _scan->getUuid(), model->getItem(_origScansIndex));

            Gruppe *scanTexturen = new Gruppe("Texturen", "", "", saveScan);
            saveScan->appendChild(scanTexturen);

            //Bild in Projektordner speichern
            saveScan->setScansPath(_scan->getScansPath());
            saveScan->setScanPath(_scan->getUuid());
            saveScan->setImage(_scan->getImage());
            saveScan->saveScanImage(_scan->getImage());
            saveScan->makeThumbnail();

            //Texturen hinzufügen
            QPersistentModelIndex newScanIndex = model->index(0, model->rowCount(_origScansIndex) - 1, _origScansIndex);
            QPersistentModelIndex newTexturesIndex = texturenListe->index(0, 0, newScanIndex);

            QPersistentModelIndex tempTexturenIndex = texturenListe->index(0, 0, _scanIndex);
            for(int i = 0; i < texturenListe->rowCount(tempTexturenIndex); i++){
                QPersistentModelIndex tempTIndex = model->index(i, 0, tempTexturenIndex);
                Textur* tempT = (Textur*)model->getItem(tempTIndex);
//                qDebug() << model->getItem(tempTIndex)->getName();
                Textur *saveT = new Textur(saveScan->getScanPath(), scanTexturen);
                scanTexturen->appendChild(saveT);
                saveT->setRect(tempT->getRect());
                saveT->setName(tempT->getName());
                saveT->texImageFromScan(saveScan->getImage());
//                saveT->Image();
//                saveT->makeTextureImage();
            }
            ((ElementModel*)_origScansIndex.model())->insertChild(saveScan, _origScansIndex);
        }

        //model->setData(_scanIndex, ms->getName());

        //Rects der Texturen anpassen
        event->accept();
        break;
    case QMessageBox::Cancel:
        //Neue Rects löschen
//        newRects = renderArea->getNewRects();
//        qDebug() << newRects;
        event->ignore();
        break;
    default:
        QDialog::closeEvent(event);
        break;
    }
}


