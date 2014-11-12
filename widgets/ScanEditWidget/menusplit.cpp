#include "menusplit.h"
#include "ui_menusplit.h"

MenuSplit::MenuSplit(const QModelIndex &i, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuSplit)
{
    model = (ElementModel*)(i.model());
    texturesIndex = i;

    ui->setupUi(this);
    ui->modus->addItem(tr("neu"));
    ui->modus->addItem(tr("bearbeiten"));

    ui->deleteArea->setDisabled(true);

    connect(ui->modus, SIGNAL(currentIndexChanged(int)), this, SLOT(changeModus(int)));

//    ui->rectListe->setModel(i.model());
//    ui->rectListe->setRootIndex(i);

    ui->rectView->setModel(model);
    ui->rectView->setRootIndex(model->index(0, 0, i));
    ui->rectView->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->rectView->setIconSize();
    ui->rectView->setDisabled(true);

    ui->treeView->setVisible(false);
    ui->treeView_2->setVisible(false);

//    ui->treeView->setModel(model);

    //DIRTY
    initialRows = model->rowCount(model->index(0, 0, i));

//    connect(ui->rectListe, SIGNAL(itemSelectionChanged()), this, SLOT(listItemChanged()));

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);

    mapper->setModel(model);
    mapper->addMapping(ui->name, 0);
    mapper->setRootIndex(i.parent());
    mapper->setCurrentModelIndex(i);

}

MenuSplit::~MenuSplit()
{
    delete ui;
}

void MenuSplit::setName(QString s){
    ui->name->setText(s);
}

QString MenuSplit::getName(){
    return ui->name->text();
}

//void MenuSplit::listItemChanged(){
//    int index = this->ui->rectListe->currentRow();
//    emit this->rectActivated(index);
//}

void MenuSplit::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//void MenuSplit::addRect(QString name, QRect rect){
////    ui->rectListe->insertItem(punktgruppenCount++, line.name);
//    ui->rectListe->addItem(name);
//    //punktgruppenMapping.insert(punktgruppenCount++, linie);
//}

void MenuSplit::changeModus(int modusIndex){
    //Wenn editieren ausgewählt: Buttons enablen
    if(modusIndex == 1){
        ui->deleteArea->setEnabled(true);
        ui->rectView->setEnabled(true);
    }else{
        ui->deleteArea->setEnabled(false);
        ui->rectView->setEnabled(false);
    }

    emit subModusChanged(modusIndex);
}

//void MenuSplit::fillList(QList< QString > *list){
//    clearItems();
//    foreach(QString s, *list){
//         ui->rectListe->addItem(s);
//    }
//}

//void MenuSplit::clearItems(){
//    ui->rectListe->clear();
//}


void MenuSplit::on_deleteArea_clicked()
{
    QPersistentModelIndex index = ui->rectView->currentIndex();
    if(index.isValid() && index.row() > initialRows - 1){
        //DIRTY
        emit deleteTexture(index);

        ((ElementModel*)index.model())->removeRow(index.row(), index.parent());

//        if (QMessageBox::Ok == QMessageBox::question(this, tr("Textur löschen?"),
//                                                     tr("Soll die ausgewählte Textur gelöscht werden? Alle Linien, Transparente Bereiche etc. werden ebenfalls gelöscht!"), (QMessageBox::Ok | QMessageBox::Cancel))){
    }
//        int index = ui->rectListe->currentRow();
//        if (index > -1){
//            ui->rectListe->takeItem(index);
//            ui->rectListe->setCurrentRow(-1);
//            emit deleteTexture(index);
//        }
}

//void MenuSplit::removeFromList(int index){
//    if (index > -1){
//        ui->rectListe->takeItem(index);
//        ui->rectListe->setCurrentRow(-1);
//    }
//}

void MenuSplit::on_rectView_clicked(const QModelIndex &index)
{
    QModelIndex i = index;
    emit textureActivated(i);
}

void MenuSplit::setDebugViewModel(ElementModel *m){
    ui->treeView_2->setModel(m);
}
