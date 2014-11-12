#ifndef PROJECTPROPERTIES_H
#define PROJECTPROPERTIES_H

#include <QDialog>
#include "container/project.h"

namespace Ui {
class ProjectProperties;
}

class ProjectProperties : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProjectProperties(Project * p, QWidget *parent = 0);
    ~ProjectProperties();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::ProjectProperties *ui;
    Project *project;
};

#endif // PROJECTPROPERTIES_H
