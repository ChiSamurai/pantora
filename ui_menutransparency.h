/********************************************************************************
** Form generated from reading UI file 'menutransparency.ui'
**
** Created: Thu Oct 10 15:37:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUTRANSPARENCY_H
#define UI_MENUTRANSPARENCY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuTransparency
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *modus;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *deletePoint;
    QPushButton *addPoint;
    QPushButton *deleteLine;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QListWidget *punktgruppenListe;

    void setupUi(QWidget *MenuTransparency)
    {
        if (MenuTransparency->objectName().isEmpty())
            MenuTransparency->setObjectName(QString::fromUtf8("MenuTransparency"));
        MenuTransparency->resize(268, 373);
        verticalLayout = new QVBoxLayout(MenuTransparency);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(MenuTransparency);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        modus = new QComboBox(MenuTransparency);
        modus->setObjectName(QString::fromUtf8("modus"));

        verticalLayout->addWidget(modus);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        deletePoint = new QPushButton(MenuTransparency);
        deletePoint->setObjectName(QString::fromUtf8("deletePoint"));

        gridLayout->addWidget(deletePoint, 1, 0, 1, 1);

        addPoint = new QPushButton(MenuTransparency);
        addPoint->setObjectName(QString::fromUtf8("addPoint"));

        gridLayout->addWidget(addPoint, 0, 0, 1, 1);

        deleteLine = new QPushButton(MenuTransparency);
        deleteLine->setObjectName(QString::fromUtf8("deleteLine"));

        gridLayout->addWidget(deleteLine, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        punktgruppenListe = new QListWidget(MenuTransparency);
        punktgruppenListe->setObjectName(QString::fromUtf8("punktgruppenListe"));

        verticalLayout->addWidget(punktgruppenListe);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(modus);
#endif // QT_NO_SHORTCUT

        retranslateUi(MenuTransparency);

        QMetaObject::connectSlotsByName(MenuTransparency);
    } // setupUi

    void retranslateUi(QWidget *MenuTransparency)
    {
        MenuTransparency->setWindowTitle(QApplication::translate("MenuTransparency", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MenuTransparency", "Modus", 0, QApplication::UnicodeUTF8));
        deletePoint->setText(QApplication::translate("MenuTransparency", "Punkt l\303\266schen", 0, QApplication::UnicodeUTF8));
        addPoint->setText(QApplication::translate("MenuTransparency", "Punkt hinzuf\303\274gen", 0, QApplication::UnicodeUTF8));
        deleteLine->setText(QApplication::translate("MenuTransparency", "Linie l\303\266schen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MenuTransparency: public Ui_MenuTransparency {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUTRANSPARENCY_H
