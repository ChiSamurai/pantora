#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewWindow.h"
#include "docks/groupdockwidget.h"
#include "container/project.h"
#include "elemente/punktgruppe.h"
#include "elemente/punkt.h"
#include "elemente/gruppe.h"
#include "elemente/gruppentyp.h"

#include "dialoge/managescansdialog.h"
#include "dialoge/projectproperties.h"
#include "dialoge/movecameradialog.h"

#include "tools/filetools.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QString appName;
    void changeEvent(QEvent *e);
    virtual void closeEvent ( QCloseEvent * event );

private:
    void createMenus();
    void createActions();

    void addToLastUsed(QString path);
    void buildLastUsedMenu(QMenu *m);

    void clearProject();

    Ui::MainWindow *ui;

    viewWindow *vw;
    GroupDockWidget *gdw;
    Project *project;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *fileMenuLastProjects;

    QMenu *elementsMenu;

    QMenu *viewMenu;

    QAction *newProjectAct, *openProjectAct, *saveProjectAct, *saveAsProjectAct, *propertiesAct, *exitAct;

    QAction *groupManagerAct, *cameraDialogAct;

    QAction *openScanManagerAct;

    ManageScansDialog *scanManager;
    MoveCameraDialog *cameraDialog;

    QList<QDir> lastUsedProjectFiles;
    QDir appDir;
    QDir tempDir;
    
    QString originalDir;

private slots:
    void projectClicked(QAction *qa);

    void newProject();

    void loadProject();
    void loadProject(QString dirName);

    void saveProject();
    void saveProjectAs();

    void openProperties();

    void openScanManager();
    void saveLastUsed();
    void loadLastUsed();

    void toggleMenuItems(bool activate);
    void toggleGroupManager();

public slots:
    void updateGL();
};

#endif // MAINWINDOW_H
