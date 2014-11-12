/********************************************************************************
** Form generated from reading UI file 'textureeditormenu.ui'
**
** Created: Thu Oct 10 15:37:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTUREEDITORMENU_H
#define UI_TEXTUREEDITORMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextureEditorMenu
{
public:
    QWidget *paint;
    QWidget *trans;
    QWidget *cut;
    QWidget *clip;

    void setupUi(QTabWidget *TextureEditorMenu)
    {
        if (TextureEditorMenu->objectName().isEmpty())
            TextureEditorMenu->setObjectName(QString::fromUtf8("TextureEditorMenu"));
        TextureEditorMenu->resize(300, 300);
        paint = new QWidget();
        paint->setObjectName(QString::fromUtf8("paint"));
        TextureEditorMenu->addTab(paint, QString());
        trans = new QWidget();
        trans->setObjectName(QString::fromUtf8("trans"));
        TextureEditorMenu->addTab(trans, QString());
        cut = new QWidget();
        cut->setObjectName(QString::fromUtf8("cut"));
        TextureEditorMenu->addTab(cut, QString());
        clip = new QWidget();
        clip->setObjectName(QString::fromUtf8("clip"));
        TextureEditorMenu->addTab(clip, QString());

        retranslateUi(TextureEditorMenu);

        TextureEditorMenu->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(TextureEditorMenu);
    } // setupUi

    void retranslateUi(QTabWidget *TextureEditorMenu)
    {
        TextureEditorMenu->setWindowTitle(QApplication::translate("TextureEditorMenu", "TabWidget", 0, QApplication::UnicodeUTF8));
        TextureEditorMenu->setTabText(TextureEditorMenu->indexOf(paint), QApplication::translate("TextureEditorMenu", "Zeichnen", 0, QApplication::UnicodeUTF8));
        TextureEditorMenu->setTabText(TextureEditorMenu->indexOf(trans), QApplication::translate("TextureEditorMenu", "Transparenz", 0, QApplication::UnicodeUTF8));
        TextureEditorMenu->setTabText(TextureEditorMenu->indexOf(cut), QApplication::translate("TextureEditorMenu", "Zuschneiden", 0, QApplication::UnicodeUTF8));
        TextureEditorMenu->setTabText(TextureEditorMenu->indexOf(clip), QApplication::translate("TextureEditorMenu", "Einh\303\244ngen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TextureEditorMenu: public Ui_TextureEditorMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTUREEDITORMENU_H
