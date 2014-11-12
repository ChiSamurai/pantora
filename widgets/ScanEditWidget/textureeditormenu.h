#ifndef TEXTUREEDITORMENU_H
#define TEXTUREEDITORMENU_H

#include <QTabWidget>

namespace Ui {
    class TextureEditorMenu;
}

class TextureEditorMenu : public QTabWidget {
    Q_OBJECT
public:
    TextureEditorMenu(QWidget *parent = 0);
    ~TextureEditorMenu();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TextureEditorMenu *ui;

};

#endif // TEXTUREEDITORMENU_H
