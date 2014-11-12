#include "projectproperties.h"
#include "ui_projectproperties.h"

ProjectProperties::ProjectProperties(Project *p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectProperties)
{
    ui->setupUi(this);
    project = p;

    QValidator *validator = new QDoubleValidator(this);

    ui->nullX->setValidator(validator);
    ui->nullY->setValidator(validator);
    ui->nullZ->setValidator(validator);

    ui->camX->setValidator(validator);
    ui->camY->setValidator(validator);
    ui->camZ->setValidator(validator);

    QString temp;
    ui->nullX->setText(temp.setNum(p->getNullPoint().x(), 'f', 3));
    ui->nullY->setText(temp.setNum(p->getNullPoint().y(), 'f', 3));
    ui->nullZ->setText(temp.setNum(p->getNullPoint().z(), 'f', 3));

    ui->camX->setText(temp.setNum(p->getCamPos().x(), 'f', 3));
    ui->camY->setText(temp.setNum(p->getCamPos().y(), 'f', 3));
    ui->camZ->setText(temp.setNum(p->getCamPos().z(), 'f', 3));

    if(project->getInvertXAxis()) ui->flipx->setChecked(true);
}

ProjectProperties::~ProjectProperties()
{
    delete ui;
}

void ProjectProperties::on_buttonBox_accepted()
{
    QVector3D p;
    p.setX(ui->nullX->text().toFloat());
    p.setY(ui->nullY->text().toFloat());
    p.setZ(ui->nullZ->text().toFloat());
    project->setNullPoint(p);

    p.setX(ui->camX->text().toFloat());
    p.setY(ui->camY->text().toFloat());
    p.setZ(ui->camZ->text().toFloat());
    project->setCamPos(p);


    if(ui->flipx->isChecked()) project->setInvertXAxis(true);
    else project->setInvertXAxis(false);
}
