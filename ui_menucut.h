/********************************************************************************
** Form generated from reading UI file 'menucut.ui'
**
** Created: Thu Oct 10 15:37:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUCUT_H
#define UI_MENUCUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuCut
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *addPoint;
    QPushButton *deleteAll;
    QSpacerItem *verticalSpacer;
    QPushButton *deletePoint;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *MenuCut)
    {
        if (MenuCut->objectName().isEmpty())
            MenuCut->setObjectName(QString::fromUtf8("MenuCut"));
        MenuCut->resize(269, 302);
        verticalLayout = new QVBoxLayout(MenuCut);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        addPoint = new QPushButton(MenuCut);
        addPoint->setObjectName(QString::fromUtf8("addPoint"));

        gridLayout->addWidget(addPoint, 0, 0, 1, 1);

        deleteAll = new QPushButton(MenuCut);
        deleteAll->setObjectName(QString::fromUtf8("deleteAll"));

        gridLayout->addWidget(deleteAll, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        deletePoint = new QPushButton(MenuCut);
        deletePoint->setObjectName(QString::fromUtf8("deletePoint"));

        gridLayout->addWidget(deletePoint, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(MenuCut);

        QMetaObject::connectSlotsByName(MenuCut);
    } // setupUi

    void retranslateUi(QWidget *MenuCut)
    {
        MenuCut->setWindowTitle(QApplication::translate("MenuCut", "Form", 0, QApplication::UnicodeUTF8));
        addPoint->setText(QApplication::translate("MenuCut", "Punkt hinzuf\303\274gen", 0, QApplication::UnicodeUTF8));
        deleteAll->setText(QApplication::translate("MenuCut", "alles l\303\266schen", 0, QApplication::UnicodeUTF8));
        deletePoint->setText(QApplication::translate("MenuCut", "Punkt l\303\266schen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MenuCut: public Ui_MenuCut {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUCUT_H
