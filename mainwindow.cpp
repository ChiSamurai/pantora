#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    appName = QString("Pantora v0.3");
    ui->setupUi(this);

    resize(1024, 800);

    setWindowTitle(appName);

    gdw = new GroupDockWidget(this);
    vw = new viewWindow(this); //GL window
    setCentralWidget(vw);
    addDockWidget(Qt::RightDockWidgetArea, gdw);

    //Application Path herausfinden
    #ifdef Q_WS_WIN
    appDir.setPath(QDir::homePath() + "/Application Data/Pantora/");
    #elif defined(Q_WS_X11)
    appDir.setPath(QDir::homePath() + "/.Pantora/");
    #endif

    tempDir = QDir(appDir.absolutePath() + "/tempFiles");

    //wenn Data-Directories nicht existieren, anlegen
    if(!appDir.exists()) appDir.mkpath(".");
    if(!tempDir.exists()) tempDir.mkpath(".");
    //Temp-Verzeichnis leeren
    FileTools::clearFolder(tempDir.absolutePath());

    //Die zuletzt benutzten Projekte holen
    loadLastUsed();

    project = new Project(tempDir.absolutePath(), this);

    vw->setProject(project);
    project->GLinit(vw);
    gdw->setProject(project);

    //Dialoge erstellen
    scanManager = new ManageScansDialog(project, vw, this);
    scanManager->setModal(true);
    //Kamera-Dialog
    cameraDialog = new MoveCameraDialog(project, this);
    connect(cameraDialog, SIGNAL(setCamera(QVector3D)), vw, SLOT(setCamPos(QVector3D)));
    connect(cameraDialog, SIGNAL(setLookAt(QVector3D)), vw, SLOT(setLookAtPoint(QVector3D)));

    connect(vw, SIGNAL(camPosChanged(QVector3D)), cameraDialog, SLOT(newCameraPos(QVector3D)));
    connect(vw, SIGNAL(lookAtPointChanged(QVector3D)), cameraDialog, SLOT(newLookAt(QVector3D)));

    scanManager->setProject(project);
//            scanManager->loadScanContainer(project->getScanContainer());

//    scanManager->setModel(project->getElementModel());

    //Umschaltung der Anzeige:
    connect(gdw, SIGNAL(updateGl()), vw, SLOT(updateGL()));
    connect(scanManager, SIGNAL(updateGl()), vw, SLOT(updateGL()));

    //Menu erstellen und hinzufügen
    menuBar = new QMenuBar();
    createActions();
    createMenus();
    setMenuBar(menuBar);

}

MainWindow::~MainWindow(){
    project->close();
    delete ui;
}

void MainWindow::createMenus(){
    fileMenuLastProjects = new QMenu(tr("zuletzt geöffnet"), this);
    buildLastUsedMenu(fileMenuLastProjects);
    connect(fileMenuLastProjects, SIGNAL(triggered(QAction*)), this, SLOT(projectClicked(QAction*)));

    fileMenu = new QMenu(tr("&Projekt"), this);
    fileMenu->addAction(newProjectAct);
    fileMenu->addAction(openProjectAct);
    fileMenu->addAction(saveProjectAct);
    fileMenu->addAction(saveAsProjectAct);
    fileMenu->addSeparator();
    fileMenu->addAction(propertiesAct);
    fileMenu->addSeparator();
    fileMenu->addMenu(fileMenuLastProjects);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    elementsMenu = new QMenu(tr("&Elemente"), this);
    elementsMenu->addAction(openScanManagerAct);

    viewMenu = new QMenu(tr("&Ansicht"), this);
    viewMenu->addAction(groupManagerAct);
    viewMenu->addAction(cameraDialogAct);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(viewMenu);
    menuBar->addMenu(elementsMenu);
}

void MainWindow::createActions(){
    newProjectAct = new QAction(tr("&neues Projekt"), this);
    newProjectAct->setShortcut(tr("Ctrl+N"));
    connect(newProjectAct, SIGNAL(triggered()), this, SLOT(newProject()));

    openProjectAct = new QAction(tr("Projekt öffnen..."), this);
    openProjectAct->setShortcut(tr("Ctrl+O"));
    connect(openProjectAct, SIGNAL(triggered()), this, SLOT(loadProject()));

    saveProjectAct = new QAction(tr("Projekt &speichern"), this);
    saveProjectAct->setShortcut(tr("Ctrl+S"));
    connect(saveProjectAct, SIGNAL(triggered()), this, SLOT(saveProject()));

    saveAsProjectAct = new QAction(tr("Projekt speichern &unter..."), this);
    saveAsProjectAct->setShortcut(tr("Ctrl+U"));
    connect(saveAsProjectAct, SIGNAL(triggered()), this, SLOT(saveProjectAs()));

    propertiesAct = new QAction(tr("Eigenschaften"), this);
    propertiesAct->setShortcut(tr("CTRL+E"));
    connect(propertiesAct, SIGNAL(triggered()), this, SLOT(openProperties()));

    exitAct = new QAction(tr("Beenden"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // *** Elemente-Menü
    openScanManagerAct = new QAction(tr("Scans verwalten..."), this);
    openScanManagerAct->setShortcut(tr("Ctrl+Alt+S"));
    connect(openScanManagerAct, SIGNAL(triggered()), this, SLOT(openScanManager()));

    // *** View-Menü
    groupManagerAct = new QAction(tr("Gruppenmanager"), this);
    groupManagerAct->setCheckable(true);
    groupManagerAct->setChecked(true);
    connect(groupManagerAct, SIGNAL(triggered()), this, SLOT(toggleGroupManager()));
    connect(gdw, SIGNAL(visibilityChanged(bool)), groupManagerAct, SLOT(setChecked(bool)));

    cameraDialogAct = new QAction(tr("manuelle Kamerasteuerung"), this);
    cameraDialogAct->setCheckable(true);
    cameraDialogAct->setChecked(false);

    connect(cameraDialogAct, SIGNAL(triggered(bool)), cameraDialog, SLOT(setVisible(bool)));
    connect(cameraDialog, SIGNAL(accepted()), cameraDialogAct, SLOT(toggle()));
    connect(cameraDialog, SIGNAL(rejected()), cameraDialogAct, SLOT(toggle()));

    //Menuitems deaktivieren
    toggleMenuItems(false);
}

void MainWindow::changeEvent(QEvent *e){
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::openScanManager(){
    if(project) scanManager->show();
}

void MainWindow::newProject(){
    project = new Project(tempDir.absolutePath());
    //ToDo: wenn temp-Dir nicht leer: nachfragen, ob überschrieben werden soll
    clearProject();
    project->setProjectDir(tempDir.absolutePath());

    //Model setzen
    scanManager->setModel(project->getElementModel());

    //ScanManager neu initialisieren
    vw->setProject(project);
    gdw->setProject(project);
    scanManager->setProject(project);
    cameraDialog->setProject(project);
//    scanManager->loadScanContainer(project->getScanContainer());
    project->GLinit(vw);

    //Speicherpfad zurücksetzen
    originalDir = QString();
    //Fenstertitel setzen
    setWindowTitle(appName + " - <" + tr("neues Projekt") + ">");

    saveAsProjectAct->setEnabled(true);
    saveProjectAct->setEnabled(false);
    openScanManagerAct->setEnabled(true);

    openProperties();
}

void MainWindow::loadProject(){

    QString valid("Pantora Projekt-XML (project.xml)");
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Projekt Öffnen"), QDir::currentPath(), valid);

//    QString dirName = QFileDialog::getExistingDirectory(this, tr("Projekt öffnen"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::ReadOnly);
    if(!fileName.isEmpty()){
        QFileInfo file(fileName);
        QString dirName = file.absolutePath();
        loadProject(dirName);
    }
}

void MainWindow::loadProject(QString dirName){
    if (!dirName.isEmpty()){
        //Projekt bereinigen
        clearProject();

        //Kopieren des Projekts in temporäres Verzeichnis
        FileTools::copyFolder(dirName, tempDir.absolutePath());

        originalDir = dirName;
        QString loadError = project->load(tempDir.absolutePath());
        if(!loadError.isNull()){
            QMessageBox::critical(this, tr("Fehler beim Laden des Projekts"), loadError, QMessageBox::Ok);
        }else{

            //Model setzen
            scanManager->setModel(project->getElementModel());

            vw->setProject(project);
            gdw->setProject(project);
            scanManager->setProject(project);
            cameraDialog->setProject(project);

//            scanManager->loadScanContainer(project->getScanContainer());
            project->GLinit(vw);

            scanManager->setModel(project->getElementModel());
//            scanManager->setModel(project->getScanModel());
            //Projekt der "zuletzt geöffnet" Liste hinzufügen
            addToLastUsed(dirName);
            setWindowTitle(appName + " - " + dirName);
            toggleMenuItems(true);
            vw->update();
        }
    }
}

void MainWindow::saveProject(){
    //Zuerst xml im tempVerzeichnis speichern
    QString error = project->save();
    if(!error.isNull()){
        QMessageBox::critical(this,
                      tr("Fehler beim Speichern"),
                      error,
                      QMessageBox::Ok);
    } else {
        //Bereinigen des Projektverzeichnisses
        FileTools::clearFolder(originalDir);

        //Kopieren des Projekts in temporäres Verzeichnis
        FileTools::copyFolder(tempDir.absolutePath(), originalDir);
    }
}

void MainWindow::saveProjectAs(){
    QString startdir = originalDir.isNull()?QDir::currentPath():originalDir;
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Projekt in Verzeichnis speichern"), startdir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dirName.isEmpty()){
        bool overwrite = true;
        //wenn Directory nicht leer: nachfragen ob Dateien gelöscht werden sollen
        if(QDir(dirName).exists() && QDir(dirName).count() > 0){
            if(QMessageBox::Ok != QMessageBox::warning(this,
                          tr("Alle Dateien löschen"),
                          tr("<b>Achtung:</b> alle Dateien im Verzeichnis werden gelöscht! Sind sicher?"),
                          QMessageBox::Cancel | QMessageBox::Ok))
                overwrite = false;
        }
        if(overwrite){
            originalDir = dirName;
            saveProject();
            addToLastUsed(dirName);
            toggleMenuItems(true);
            setWindowTitle(appName + " - " + dirName);
        }
    }
}

void MainWindow::loadLastUsed(){
    QFile lastUsedProjects(appDir.absolutePath() + "/lastUsedProjects.xml");
    if(lastUsedProjects.exists()){
        //letzte Projekte lesen
        if (!lastUsedProjects.open(QIODevice::ReadOnly)){
////        if (!file.open(QIODevice::ReadOnly)) QString(QObject::tr("Fehler beim Laden der Datei: ") + filename);
        }
        QXmlStreamReader xmlReader(&lastUsedProjects);
//        if(xmlReader->name() == "name") name =  xmlReader->readElementText();
        if(!xmlReader.hasError()){
            while(!xmlReader.atEnd() && !xmlReader.hasError()) {
                if(xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "projectList"){
                    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "projectList")) {
                        // *** Pfade zu den letzten Projekten
                      if(xmlReader.name() == "project"){
                            lastUsedProjectFiles.append(QDir(xmlReader.readElementText()));
                        }
                        xmlReader.readNext();
                    }
                }
                xmlReader.readNext();
            }
        }
    }
}

void MainWindow::saveLastUsed(){
    QFile file(appDir.absolutePath() + "/lastUsedProjects.xml");
//    //Scan-XML schreiben
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) std::cout << "Fehler beim Speichern der letzten Projekte";
    else{
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

        xmlWriter.writeStartElement("projectList");
        foreach(QDir d, lastUsedProjectFiles){
            xmlWriter.writeTextElement("project", d.absolutePath());
        }
        xmlWriter.writeEndElement();

        xmlWriter.writeEndDocument();
        file.close();
    }
}

void MainWindow::closeEvent ( QCloseEvent * event ){
    //Bereinigen des Temporären Verzeichnisses
    FileTools::clearFolder(tempDir.absolutePath());
    saveLastUsed();
}

void MainWindow::projectClicked(QAction *qa){
     loadProject(qa->data().toString());
}

void MainWindow::updateGL(){
    vw->updateGL();
}

void MainWindow::addToLastUsed(QString path){
    //Wenn Projekt bereits in Liste, diesen Eintrag löschen
    bool found = false;
    QList<QDir>::iterator i = lastUsedProjectFiles.begin();
    while(i != lastUsedProjectFiles.end() && found == false){
        QDir d = *i;
        if(d.absolutePath() == path){
            lastUsedProjectFiles.erase(i);
            found = true;
        }
        ++i;
    }
    lastUsedProjectFiles.append(QDir(path));
    buildLastUsedMenu(fileMenuLastProjects);
}

void MainWindow::buildLastUsedMenu(QMenu *m){
    m->clear();
    QListIterator<QDir> i(lastUsedProjectFiles);
    i.toBack();
    while (i.hasPrevious()) {
        QDir d = i.previous();
        QAction *a = m->addAction(d.absolutePath());
        a->setData(d.absolutePath());
    }

}

void MainWindow::clearProject(){
    //Bereinigen des Temporären Verzeichnisses
    FileTools::clearFolder(tempDir.absolutePath());

    //Projekt leeren
    if (project){
        project->close();
        delete project;
    }
    project = new Project(tempDir.absolutePath(), this);
}

void MainWindow::toggleMenuItems(bool activate){
    saveAsProjectAct->setEnabled(activate);
    saveProjectAct->setEnabled(activate);
    openScanManagerAct->setEnabled(activate);
    propertiesAct->setEnabled(activate);
}

void MainWindow::toggleGroupManager(){
    if(groupManagerAct->isChecked()){
        gdw->show();
    }
    else
        gdw->hide();
}

void MainWindow::openProperties(){
    ProjectProperties *pp = new ProjectProperties(project, this);
    pp->show();

}
