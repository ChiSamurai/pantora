#include "textureeditormenu.h"
#include "ui_textureeditormenu.h"

TextureEditorMenu::TextureEditorMenu(const QModelIndex &i, QWidget *parent): EditMenu(i, parent),
    ui(new Ui::TextureEditorMenu)
{
    ui->setupUi(this);
}

TextureEditorMenu::~TextureEditorMenu()
{
    delete ui;
}

void TextureEditorMenu::changeEvent(QEvent *e)
{
    QTabWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
