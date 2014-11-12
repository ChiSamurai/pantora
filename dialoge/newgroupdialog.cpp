#include "newgroupdialog.h"
#include "ui_newgroupdialog.h"

NewGroupDialog::NewGroupDialog(QList<GruppenTyp*> t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGroupDialog)
{
    ui->setupUi(this);
    typen = t;

    foreach(GruppenTyp *gt, typen){
        ui->gruppenTypenSelect->addItem(gt->getName());
    }
}

NewGroupDialog::~NewGroupDialog()
{
    delete ui;
}

void NewGroupDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void NewGroupDialog::on_ColorButton_clicked()
{
    //    QColor color = QColorDialog::getColor(*selectedColor, this);
    //    if (color.isValid())
    //    {
    //        selectedColor = new QColor(color);
    //        setColorFrameColor(selectedColor);
    //        if(actualPG) actualPG->setLineColor(selectedColor);

}

void NewGroupDialog::on_addButton_clicked()
{
    emit addNewGroup(this->ui->name->text());
}


