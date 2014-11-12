#ifndef PROJECT_H_
#define PROJECT_H_

#include <QWidget>
#include <QGLWidget>
#include <QDebug>
#include <QStandardItem>
#include <QVector3D>
#include "models/elementmodel.h"

//Elemente
//#include "elemente/koordinatenkreuz.h"
//#include "elemente/RecordUnit.h"

#include "elemente/gruppentyp.h"
#include "elemente/gruppe.h"

//Container
#include "container/showgroups.h"
#include "container/contgruppen.h"
#include "container/contpunkte.h"
#include "container/contpunktgruppen.h"
#include "contscans.h"

//#include "container/ContRecordUnits.h"
//#include "container/ContKoordinatenkreuze.h"
//#include "container/ContLines.h"
//#include "container/ContGruben.h"

//#include "werkzeuge/Massstab.h"

//#include "viewWindow.h"
//#include "qthreadinterface.h"

//#include "scan.h"

#define SCANSDIR "scans"


class Project : public QObject
 {
     Q_OBJECT

    public:
        Project(QString path, QWidget *parent = 0);
        ~Project();
        void close();

        ContPunktgruppen *getPunktgruppen() { return &punktgruppen; }
        ContScans *getScanContainer() { return &scans; }
        ContGruppen *getGruppen() { return &gruppen; }
        ContGruppen *getScanGruppen() { return &elementeGruppen; }

//        void setOrigDir(QString dir){ projectsOrigDir = dir; };
//        QString getOrigDir() { return projectsOrigDir; };

        void setProjectDir(QString dir){ projectsDir = dir; scans.setScansDir(projectsDir + "/scans");}
        QString getProjectDir() { return projectsDir;}

        QString getScansDir() { return projectsDir + "/" + SCANSDIR; }

        QList<GruppenTyp*> getGruppenTypen() { return gruppenTypen; }

        QVector3D getNullPoint(){ return nullPoint; }
        void setNullPoint(QVector3D v) { nullPoint = v; }

        QVector3D getCamPos(){ return camPos; }
        void setCamPos(QVector3D v) { camPos = v; }

        bool getInvertXAxis() { return invertXAxis; }
        void setInvertXAxis(bool s) { invertXAxis = s; }

        void GLinit(QGLWidget *glw);

        void GLdraw(QGLWidget *glw);

        QString load(QString dir);
        QString save();

        bool loadGroupTypes();

        ElementModel *getElementModel(){ return model; }
        ElementModel *getAnzeigeModel(){ return anzeigeModel; }

public slots:
        void setDrawKoordinatenkreuze(bool dk) { drawKoordinatenkreuz = dk;}
    //	void redraw(void);

    private:
        QVector3D nullPoint, camPos;
        bool invertXAxis;

        QString name;

        QString loadProjectSettings(QString path);
        QString saveProjectSettings(QString path);

        QPersistentModelIndex scansGruppe;
        ElementModel *model;

        ElementModel *anzeigeModel;
        ShowGroups anzeigegruppen;
        Gruppe* am_texturenGruppe;
        QPersistentModelIndex am_texturenIndex;

        QList<GruppenTyp*> gruppenTypen;

        ContPunktgruppen punktgruppen;
        ContScans scans;

        ContGruppen elementeGruppen;
        ContGruppen gruppen;

        QString projectsDir;
//        QString projectTempDir;
//        QString projectsOrigDir;

        QPersistentModelIndex scanRoot;

        bool drawKoordinatenkreuz;
//        ContPunkte punkte;
//        ContGruben *grubencontainer;
//        ContRecordUnits *recordunitscontainer;
//        Koordinatenkreuz *koordKreuz;

//	qThreadInterface* interface;

//        QString saveScans(QString path);

};

#endif /* PROJECT_H_ */
