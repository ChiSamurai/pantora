#include "movecameradialog.h"
#include "ui_movecameradialog.h"

MoveCameraDialog::MoveCameraDialog(Project *p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoveCameraDialog)
{
    ui->setupUi(this);

    QValidator *validator = new QDoubleValidator(this);
    ui->lookAtX->setValidator(validator);
    ui->lookAtY->setValidator(validator);
    ui->lookAtZ->setValidator(validator);

    ui->camX->setValidator(validator);
    ui->camY->setValidator(validator);
    ui->camZ->setValidator(validator);

    setProject(p);

    connect(ui->doButton, SIGNAL(clicked()), this, SLOT(doMovement()));
}

MoveCameraDialog::~MoveCameraDialog()
{
    delete ui;
}

void MoveCameraDialog::setProject(Project *p){
    project = p;
    ui->lookAtX->setText(QString::number(p->getNullPoint().x()));
    ui->lookAtY->setText(QString::number(p->getNullPoint().y()));
    ui->lookAtZ->setText(QString::number(p->getNullPoint().z()));

    ui->camX->setText(QString::number(p->getCamPos().x()));
    ui->camY->setText(QString::number(p->getCamPos().y()));
    ui->camZ->setText(QString::number(p->getCamPos().z()));

}

void MoveCameraDialog::doMovement(){
    QVector3D p;
    p.setX(ui->lookAtX->text().toFloat());
    p.setY(ui->lookAtY->text().toFloat());
    p.setZ(ui->lookAtZ->text().toFloat());
    emit setLookAt(p);

    p.setX(ui->camX->text().toFloat());
    p.setY(ui->camY->text().toFloat());
    p.setZ(ui->camZ->text().toFloat());
    emit setCamera(p);
}

void MoveCameraDialog::newLookAt(QVector3D p){
    ui->lookAtX->setText(QString::number(p.x()));
    ui->lookAtY->setText(QString::number(p.y()));
    ui->lookAtZ->setText(QString::number(p.z()));
}


void MoveCameraDialog::newCameraPos(QVector3D p){
    ui->camX->setText(QString::number(p.x()));
    ui->camY->setText(QString::number(p.y()));
    ui->camZ->setText(QString::number(p.z()));

}

