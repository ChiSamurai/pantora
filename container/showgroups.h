#ifndef SHOWGROUPS_H
#define SHOWGROUPS_H

#include <QObject>
#include <QDebug>

#include "models/elementmodel.h"
#include "elemente/gruppe.h"
#include "elemente/abstractelement.h"

class ShowGroups : public QObject
{
    Q_OBJECT
public:
    explicit ShowGroups(QObject *parent = 0);
    QString loadFromXML(QString projectPath);
    bool loadGroupElement(QXmlStreamReader *xmlReader, AbstractElement *parentElement = 0);
    ElementModel *getModel() { return &gruppenModel; }

private:
    ElementModel gruppenModel;
    
signals:
    
public slots:
    void addGroup(QString name, QModelIndex parent = QModelIndex());

    
};

#endif // SHOWGROUPS_H
