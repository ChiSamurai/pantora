#include "groupdockwidget.h"
#include "ui_groupdockwidget.h"

GroupDockWidget::GroupDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::GroupDockWidget)
{
    ui->setupUi(this);
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    ui->addGroupButton->setDisabled(true);

    //ModelViews Setup
    ui->elementeView->setAcceptDrops(false);
    ui->elementeView->setDragEnabled(false);
    ui->elementeView->setSelectionMode(QAbstractItemView::SingleSelection);


    ui->gruppenView->setAcceptDrops(false);
    ui->gruppenView->setDragEnabled(false);
    ui->gruppenView->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->gruppenView->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->display->setEnabled(false);

    ui->elementeView->setVisible(true);

    ui->gruppenView->setVisible(false);
    ui->addGroupButton->setVisible(false);
    ui->label_3->setVisible(false);
    //Model für Elemente
//    model_gruppen = new GruppeModel(this);

    //Initialgruppen hinzufügen

//    rootGruppe = new Gruppe(tr("Gruppen"), "", "");
//    model_gruppen->insertRow(0);
//    model_gruppen->itemFromIndex(model_gruppen->index(0,0))->setGruppe(rootGruppe);

//    model_elemente->setGruppe(model_elemente->index(0,0), "BLABLA");
//    QModelIndex elementeRoot;
//    scanParentIndex = model_elemente->insertGroupAtIndex(scanGruppe, QModelIndex());

//    model_elemente->appendChild(scanGruppe, model_elemente->rootItem, elementeRoot);


//    ui->gruppenView->setModel(model_gruppen);
//    ui->elementeView->setModel(model_elemente);

    //Beschreibungen ausblenden
    ui->gruppenView->setHeaderHidden(true);
    ui->gruppenView->hideColumn(1);
    ui->elementeView->setHeaderHidden(true);
    ui->elementeView->hideColumn(1);

    connect(ui->addGroupButton, SIGNAL(clicked()), this, SLOT(newGroupDialog()));

//    connect(ui->gruppenView, SIGNAL(customContextMenuRequested( const QPoint& )), this, SLOT(showContextMenu(const QPoint &)));
}

GroupDockWidget::~GroupDockWidget()
{
    delete ui;
}

void GroupDockWidget::setProject(Project *p){
    project = p;
    model_elemente = p->getElementModel();
    ui->elementeView->setModel(model_elemente);

//    TextureFilterProxyModel *proxyModel = new TextureFilterProxyModel(this);

//    proxyModel->setSourceModel(model_elemente);
//    ui->gruppenView->setModel(proxyModel);
//    ui->gruppenView->setModel(p->getAnzeigeModel());

    //Activate "Add" button
    ui->addGroupButton->setDisabled(false);
}

void GroupDockWidget::changeEvent(QEvent *e)
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void GroupDockWidget::newGroupDialog()
{
    //TEST
    model_elemente->insertChild(new Gruppe("test", "test2", "uuid"));
//     //ToDo: Dialog nicht in Abhängigkeit von project
//    NewGroupDialog* n = new NewGroupDialog(project->getGruppenTypen(), this);
//    connect(n, SIGNAL(addNewGroup(QString)), this, SLOT(addNewGroup(QString)));
//    n->setModal(false);
//    n->show();
}

void GroupDockWidget::addNewGroup(QString name){
    QModelIndexList il = ui->gruppenView->selectionModel()->selectedIndexes();

//    foreach(QModelIndex i, il){

//        qDebug() << model_gruppen->data(i, Qt::DisplayRole);
//    }
//    model_gruppen->insertRows(1, 1, il.at(1));
//    model_gruppen->setData(il.at(1), name);
//    model_gruppen->insertGroupAtIndex(new Gruppe(name, "", ""), il.at(1));
}

void GroupDockWidget::deleteGroup(){
    QModelIndex i = ui->gruppenView->currentIndex().parent();
    int row = ui->gruppenView->currentIndex().row();

    if(!ui->gruppenView->model()->removeRow(row, i)) qDebug() << "Fehler beim Löschen";
}

void GroupDockWidget::showContextMenu(const QPoint &p){
    QMenu contextMenu;
    QAction *addAction = contextMenu.addAction(tr("Untergruppen hinzufügen"));
    QAction *removeAction = contextMenu.addAction(tr("Gruppe löschen"));

    connect(addAction, SIGNAL(triggered()), this, SLOT(newGroupDialog()));
    connect(removeAction, SIGNAL(triggered()), this, SLOT(deleteGroup()));

    if (ui->gruppenView->currentIndex().isValid())
        contextMenu.exec(ui->gruppenView->mapToGlobal(QPoint(p.x() + 20, p.y())));
}



void GroupDockWidget::on_elementeView_doubleClicked(const QModelIndex &index)
{
//    AbstractElement *e = static_cast<ElementModel*>(ui->elementeView->model())->getItem(index);
//    switch (e->getElementType()){
//    case AbstractElement::GRUPPE:
//        Gruppe *g = static_cast<Gruppe*>(e);
//        break;
//    }

}

void GroupDockWidget::on_elementeView_clicked(const QModelIndex &index){
    AbstractElement *e = ((ElementModel*)ui->elementeView->model())->getItem(index);
    switch (e->getElementType()){
    case AbstractElement::TEXTUR:
        Textur *t;
        t = (Textur*)e;
        ui->display->setEnabled(true);
        ui->display->setChecked(t->getDisplay());
        break;
    case AbstractElement::BEFUNDGRENZE:
        Linie *l;
        l = (Linie*)e;
        ui->display->setEnabled(true);
        ui->display->setChecked(l->getDisplay());
        break;
    default:
        ui->display->setEnabled(false);
        break;
    }
}

void GroupDockWidget::on_display_toggled(bool checked)
{
    if (ui->elementeView->currentIndex().isValid()){
        AbstractElement *e = ((ElementModel*)ui->elementeView->model())->getItem(ui->elementeView->currentIndex());
        switch (e->getElementType()){
        case AbstractElement::TEXTUR:
            Textur *t;
            t = (Textur*)e;
            t->setDisplay(checked);
            emit updateGl();
            break;
        case AbstractElement::BEFUNDGRENZE:
            Linie *l;
            l = (Linie*)e;
            l->setDisplay(checked);
            emit updateGl();
            break;
        default:
            break;
        }
    }
}

void GroupDockWidget::on_gruppenView_clicked(const QModelIndex &index)
{
//    qDebug() << "hier";
//    AbstractElement *e = ((ElementModel*)ui->gruppenView->model())->getItem(index);
//    switch (e->getElementType()){
//    case AbstractElement::TEXTUR:
//        Textur *t;
//        t = (Textur*)e;
//        ui->display->setEnabled(true);
//        ui->display->setChecked(t->getDisplay());
//        break;
//    default:
//        ui->display->setEnabled(false);
//        break;
//    }

}
