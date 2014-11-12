/********************************************************************************
** Form generated from reading UI file 'textureeditor.ui'
**
** Created: Sun Sep 15 17:27:28 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTUREEDITOR_H
#define UI_TEXTUREEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_textureEditor
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *textureEditor)
    {
        if (textureEditor->objectName().isEmpty())
            textureEditor->setObjectName(QString::fromUtf8("textureEditor"));
        textureEditor->resize(600, 400);
        menuBar = new QMenuBar(textureEditor);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        textureEditor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(textureEditor);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        textureEditor->addToolBar(mainToolBar);
        centralWidget = new QWidget(textureEditor);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textureEditor->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(textureEditor);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        textureEditor->setStatusBar(statusBar);

        retranslateUi(textureEditor);

        QMetaObject::connectSlotsByName(textureEditor);
    } // setupUi

    void retranslateUi(QMainWindow *textureEditor)
    {
        textureEditor->setWindowTitle(QApplication::translate("textureEditor", "textureEditor", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class textureEditor: public Ui_textureEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTUREEDITOR_H
