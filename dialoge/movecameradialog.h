#ifndef MOVECAMERADIALOG_H
#define MOVECAMERADIALOG_H

#include <QDialog>
#include "container/project.h"

namespace Ui {
class MoveCameraDialog;
}

class MoveCameraDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MoveCameraDialog(Project *p, QWidget *parent = 0);
    ~MoveCameraDialog();
    void setProject(Project *p);

signals:
    void setCamera(QVector3D);
    void setLookAt(QVector3D);

public slots:
    void doMovement();
    void newCameraPos(QVector3D);
    void newLookAt(QVector3D);

private:
    Ui::MoveCameraDialog *ui;
    Project *project;
};

#endif // MOVECAMERADIALOG_H
