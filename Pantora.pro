# -------------------------------------------------
# Project created by QtCreator 2013-06-21T11:17:14
# -------------------------------------------------
QT += opengl \
    svg \
    xml
TARGET = Pantora
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    viewWindow.cpp \
    container/project.cpp \
    container/contpunktgruppen.cpp \
    elemente/punktgruppe.cpp \
    elemente/punkt.cpp \
    container/contpunkte.cpp \
    tools/filetools.cpp \
    elemente/gruppe.cpp \
    docks/groupdockwidget.cpp \
    elemente/gruppentyp.cpp \
    dialoge/newgroupdialog.cpp \
    glerror.cpp \
    container/contgruppen.cpp \
    widgets/ScanEditWidget/scaneditwidget.cpp \
    widgets/ScanEditWidget/menutransparency.cpp \
    widgets/ScanEditWidget/menusplit.cpp \
    widgets/ScanEditWidget/menupaint.cpp \
    widgets/ScanEditWidget/menucut.cpp \
    widgets/ScanEditWidget/menuclip.cpp \
    container/contscans.cpp \
    dialoge/managescansdialog.cpp \
    elemente/textur.cpp \
    elemente/scan.cpp \
    elemente/linie.cpp \
    elemente/einhaengepunkt.cpp \
    models/elementmodel.cpp \
    elemente/abstractelement.cpp \
    widgets/ScanEditWidget/texturerenderarea.cpp \
    widgets/ScanEditWidget/textureeditwidget.cpp \
    widgets/ScanEditWidget/scanrenderarea.cpp \
    widgets/ScanEditWidget/editmenu.cpp \
    widgets/ScanEditWidget/renderarea.cpp \
    container/showgroups.cpp \
    dialoge/projectproperties.cpp \
    dialoge/movecameradialog.cpp \
    models/texturefilterproxymodel.cpp
HEADERS += mainwindow.h \
    viewWindow.h \
    container/project.h \
    container/contpunktgruppen.h \
    elemente/punktgruppe.h \
    elemente/punkt.h \
    container/contpunkte.h \
    tools/filetools.h \
    elemente/gruppe.h \
    docks/groupdockwidget.h \
    elemente/gruppentyp.h \
    dialoge/newgroupdialog.h \
    glerror.h \
    container/contgruppen.h \
    widgets/ScanEditWidget/scaneditwidget.h \
    widgets/ScanEditWidget/menutransparency.h \
    widgets/ScanEditWidget/menusplit.h \
    widgets/ScanEditWidget/menupaint.h \
    widgets/ScanEditWidget/menucut.h \
    widgets/ScanEditWidget/menuclip.h \
    container/contscans.h \
    dialoge/managescansdialog.h \
    elemente/textur.h \
    elemente/scan.h \
    elemente/linie.h \
    elemente/einhaengepunkt.h \
    models/elementmodel.h \
    elemente/abstractelement.h \
    tools/vectors.h \
    tools/quaternion.h \
    tools/matrix.h \
    tools/arcball.h \
    widgets/ScanEditWidget/texturerenderarea.h \
    widgets/ScanEditWidget/textureeditwidget.h \
    widgets/ScanEditWidget/scanrenderarea.h \
    widgets/ScanEditWidget/editmenu.h \
    widgets/ScanEditWidget/renderarea.h \
    container/showgroups.h \
    dialoge/projectproperties.h \
    dialoge/movecameradialog.h \
    models/texturefilterproxymodel.h
FORMS += mainwindow.ui \
    docks/groupdockwidget.ui \
    dialoge/newgroupdialog.ui \
    widgets/ScanEditWidget/menutransparency.ui \
    widgets/ScanEditWidget/menusplit.ui \
    widgets/ScanEditWidget/menupaint.ui \
    widgets/ScanEditWidget/menucut.ui \
    widgets/ScanEditWidget/menuclip.ui \
    dialoge/managescansdialog.ui \
    widgets/ScanEditWidget/textureeditormenu.ui \
    dialoge/projectproperties.ui \
    dialoge/movecameradialog.ui

INCLUDEPATH *= /usr/include
INCLUDEPATH += /usr/include/GL
INCLUDEPATH += /usr/lib

LIBS += -lglut -lGLU -lQGLViewer

RESOURCES +=
