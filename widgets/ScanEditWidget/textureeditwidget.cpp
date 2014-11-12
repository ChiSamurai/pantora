#include "textureeditwidget.h"

TextureEditWidget::TextureEditWidget(const QModelIndex &i, QWidget *parent):
        QDialog (parent)
{
    model = (ElementModel*)(i.model());
    index = i;
    _texture = (Textur*)model->getItem(index);

    renderArea = new TextureRenderArea(i, this);

    //Index der Befundgrenzengruppe holen
    befGrenzenIndex = model->index(0,0, index);

    //temporäres Model erstellen
    tempModel = new ElementModel(this);
    createTemp();

    setMinimumHeight(400);
    setMinimumWidth(800);

    menuBar = new QMenuBar();
    mainLayout = new QGridLayout();

    menu = new QTabWidget(this);
    menu->setMinimumWidth(300);

    mp = new MenuPaint(tempModel, renderArea->getScene(), menu);
    mt = new MenuTransparency(index, renderArea->getScene(), menu);
    mc = new MenuClip(index, renderArea->getScene(), menu);
    mcut = new MenuCut(index, renderArea->getScene(), menu);

    menu->insertTab(0, mc, tr("Einhängen"));
    menu->insertTab(1, mcut, tr("Grabungskante"));
    menu->insertTab(2, mp, tr("Befundgrenzen"));
    menu->insertTab(3, mt, tr("Transparenz"));

    mainLayout->addWidget(renderArea, 0, 0);
    mainLayout->addWidget(menu, 0, 1);
    mainLayout->setColumnStretch(0, 10);

    setLayout(mainLayout);

    layout()->setMenuBar(menuBar);

    createActions();
    createMenus();
    createConnections();

    setWindowTitle(tr("Zeichnungen bearbeiten"));


    menu->setCurrentIndex(0);
    tabChanged(0);
}

//Temporäre Kopien erstellen
void TextureEditWidget::createTemp(){
    //Befundgrenzen kopieren
    for(int c = 0; c < model->rowCount(befGrenzenIndex); c++){
        QPersistentModelIndex origIndex = model->index(c, 0, befGrenzenIndex); //Originaler Index
        Linie *l_orig = (Linie*)model->getItem(origIndex);

        Linie *l = new Linie(l_orig->getUuid());
        l->copyFrom(l_orig);

        tempModel->insertChild(l, QModelIndex());

        QPersistentModelIndex newIndex = tempModel->index(tempModel->rowCount() - 1, 0);
        indexOldToNewMap.insert(origIndex, newIndex);
    }
}

void TextureEditWidget::createActions()
{
    saveAct = new QAction(tr("&Speichern..."), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveImage()));

    exportAct = new QAction(tr("&Exportieren..."), this);
    exportAct->setShortcut(tr("Ctrl+E"));
    connect(exportAct, SIGNAL(triggered()), this, SLOT(exportImage()));

    printAct = new QAction(tr("&Drucken..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom +n"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    connect(zoomInAct, SIGNAL(triggered()), renderArea, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom -"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    connect(zoomOutAct, SIGNAL(triggered()), renderArea, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normalgröße"), this);
    normalSizeAct->setShortcut(tr("Ctrl+N"));
    connect(normalSizeAct, SIGNAL(triggered()), renderArea, SLOT(zoomReset()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), renderArea, SLOT(zoomFull()));
}

void TextureEditWidget::createConnections(){
//    connect(menu, SIGNAL(currentChanged(int)), renderArea, SLOT(changeModus(int)));
    connect(menu, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
//    connect(this, SIGNAL(mainModusChanged(int)), renderArea, SLOT(changeModus(int)));

    connect(renderArea, SIGNAL(factorChanged(qreal)), mc, SLOT(factorUpdate(qreal)));
    connect(renderArea, SIGNAL(selectionRect(QRect)), mc, SLOT(newSelectionRect(QRect)));
    connect(renderArea, SIGNAL(mouseReleased(QMouseEvent*)), mc, SLOT(selectionStopped(QMouseEvent*)));
    connect(renderArea, SIGNAL(newPointForSelection(QPoint)), mc, SLOT(newCoordsForPoint(QPoint)));
    connect(renderArea, SIGNAL(newMousePos(QPoint)), mc, SLOT(newMousePos(QPoint)));

    connect(renderArea, SIGNAL(factorChanged(qreal)), mcut, SLOT(factorUpdate(qreal)));
    connect(renderArea, SIGNAL(selectionRect(QRect)), mcut, SLOT(newSelectionRect(QRect)));
    connect(renderArea, SIGNAL(mouseReleased(QMouseEvent*)), mcut, SLOT(selectionStopped(QMouseEvent*)));
    connect(renderArea, SIGNAL(newPointForSelection(QPoint)), mcut, SLOT(newCoordsForPoint(QPoint)));
    connect(renderArea, SIGNAL(newMousePos(QPoint)), mcut, SLOT(newMousePos(QPoint)));

    connect(renderArea, SIGNAL(factorChanged(qreal)), mp, SLOT(factorUpdate(qreal)));
    connect(renderArea, SIGNAL(selectionRect(QRect)), mp, SLOT(newSelectionRect(QRect)));
    connect(renderArea, SIGNAL(mouseReleased(QMouseEvent*)), mp, SLOT(selectionStopped(QMouseEvent*)));
    connect(renderArea, SIGNAL(newPointForSelection(QPoint)), mp, SLOT(newCoordsForPoint(QPoint)));
    connect(renderArea, SIGNAL(newMousePos(QPoint)), mp, SLOT(newMousePos(QPoint)));

    connect(renderArea, SIGNAL(factorChanged(qreal)), mt, SLOT(factorUpdate(qreal)));
    connect(renderArea, SIGNAL(selectionRect(QRect)), mt, SLOT(newSelectionRect(QRect)));
    connect(renderArea, SIGNAL(mouseReleased(QMouseEvent*)), mt, SLOT(selectionStopped(QMouseEvent*)));
    connect(renderArea, SIGNAL(newPointForSelection(QPoint)), mt, SLOT(newCoordsForPoint(QPoint)));
    connect(renderArea, SIGNAL(newMousePos(QPoint)), mt, SLOT(newMousePos(QPoint)));

}

void TextureEditWidget::createMenus()
{
    fileMenu = new QMenu(tr("&Datei"), this);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exportAct);
    fileMenu->addAction(printAct);
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

void TextureEditWidget::print(){
}

void TextureEditWidget::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void TextureEditWidget::exportImage(){
    //SVG-Export
    QString path = QFileDialog::getSaveFileName(this, tr("Befundgrenzen als SVG Speichern"),"", tr("SVG Datei(*.svg)"));

    if (path.isEmpty())
        return;
    _texture->saveSVG(path);

//    renderArea->exportImage();
}

void TextureEditWidget::saveImage(){
//    tex->setName(mc->getName());
//    renderArea->saveTexture(mc->getTyp());
}


void TextureEditWidget::tabChanged(int i){
    switch(i){
    //Clipping Menu
    case 0:
        mc->setActivated(true);
        mcut->setActivated(false);
        mp->setActivated(false);
        mt->setActivated(false);

        break;
    //Cut Menu
    case 1:
        mc->setActivated(false);
        mcut->setActivated(true);
        mp->setActivated(false);
        mt->setActivated(false);
        break;
    //Paint Menu
    case 2:
        mc->setActivated(false);
        mcut->setActivated(false);
        mp->setActivated(true);
        mt->setActivated(false);
        break;
    //Transparency Menu
    case 3:
        mc->setActivated(false);
        mcut->setActivated(false);
        mp->setActivated(false);
        mt->setActivated(true);
        break;

    }
}

void TextureEditWidget::closeEvent(QCloseEvent *event){

//    QList<QModelIndex> newRects;
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Editieren beenden"));
    msgBox.setText(tr("Änderungen übernehmen?"));

    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes );
    msgBox.setDefaultButton(QMessageBox::Yes);
    int result = msgBox.exec();
    switch (result) {
    case QMessageBox::Yes:
        //Änderungen Speichern!
        //Name übernehmen
        _texture->setName(mc->getName());

        //Einhängepunkte übernehmen
        _texture->setEinA(mc->getEin(MenuClip::A));
        _texture->setEinB(mc->getEin(MenuClip::B));

        //Befundgrenzen übernehmen
        //Bestehene Befundgrenzen abgleichen
        foreach(QPersistentModelIndex o, indexOldToNewMap.keys()){
            QPersistentModelIndex n = indexOldToNewMap.value(o);
            // wurde BefGrenze gelöscht?
            if(!n.isValid()){
                //löschen
                model->removeRow(o.row(), o.parent());
            }
            else{
                //updaten
                Linie *newLine = (Linie*)tempModel->getItem(n);
                Linie *l = (Linie*)model->getItem(o);
                l->copyFrom(newLine);
            }
        }
        //Neue Befundgrenzen einfügen
        for(int i = 0; i < tempModel->rowCount(); i++){
            QPersistentModelIndex n = tempModel->index(i, 0);
            //in Map suchen
            bool found = false;
            foreach(QPersistentModelIndex old, indexOldToNewMap.keys()){
                if (indexOldToNewMap.value(old) == n){
                    found = true;
                    continue;
                }
            }
            //wenn nicht vorhanden, hinzufügen
            if(!found){
                Linie *newLine = new Linie("", model->getItem(befGrenzenIndex));
                newLine->copyFrom((Linie*)tempModel->getItem(n));
                model->insertChild(newLine, befGrenzenIndex);
            }
        }

        //Transparente Polygone übernehmen
        _texture->setTransPuktgruppen(mt->getTransPunktgruppen());

        //Grabungskante übernehmen
        _texture->setRahmen(mcut->getRahmen());

        //Profil/Planum übernehmen
        _texture->setTyp(mc->getTyp());


        //Textur Pixmaps Updaten
        _texture->makeTextureImage();
        emit updated(_texture);
        event->accept();
        break;
    case QMessageBox::Cancel:
        event->ignore();
        break;
    default:
        QDialog::closeEvent(event);
        break;
    }
}    
