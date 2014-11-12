/********************************************************************************
** Form generated from reading UI file 'menupaint.ui'
**
** Created: Thu Oct 10 15:37:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUPAINT_H
#define UI_MENUPAINT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuPaint
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *closedLine;
    QFrame *line;
    QLabel *label;
    QComboBox *modus;
    QGridLayout *gridLayout;
    QPushButton *deleteLine;
    QPushButton *copyButton;
    QPushButton *deletePoint;
    QPushButton *addPoint;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QListView *befundgrenzenList;
    QPushButton *changeColor;

    void setupUi(QWidget *MenuPaint)
    {
        if (MenuPaint->objectName().isEmpty())
            MenuPaint->setObjectName(QString::fromUtf8("MenuPaint"));
        MenuPaint->resize(287, 460);
        verticalLayout = new QVBoxLayout(MenuPaint);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        closedLine = new QCheckBox(MenuPaint);
        closedLine->setObjectName(QString::fromUtf8("closedLine"));

        verticalLayout->addWidget(closedLine);

        line = new QFrame(MenuPaint);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label = new QLabel(MenuPaint);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        modus = new QComboBox(MenuPaint);
        modus->setObjectName(QString::fromUtf8("modus"));

        verticalLayout->addWidget(modus);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        deleteLine = new QPushButton(MenuPaint);
        deleteLine->setObjectName(QString::fromUtf8("deleteLine"));

        gridLayout->addWidget(deleteLine, 6, 2, 1, 1);

        copyButton = new QPushButton(MenuPaint);
        copyButton->setObjectName(QString::fromUtf8("copyButton"));

        gridLayout->addWidget(copyButton, 6, 0, 1, 1);

        deletePoint = new QPushButton(MenuPaint);
        deletePoint->setObjectName(QString::fromUtf8("deletePoint"));

        gridLayout->addWidget(deletePoint, 3, 0, 1, 1);

        addPoint = new QPushButton(MenuPaint);
        addPoint->setObjectName(QString::fromUtf8("addPoint"));

        gridLayout->addWidget(addPoint, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 6, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        befundgrenzenList = new QListView(MenuPaint);
        befundgrenzenList->setObjectName(QString::fromUtf8("befundgrenzenList"));

        verticalLayout->addWidget(befundgrenzenList);

        changeColor = new QPushButton(MenuPaint);
        changeColor->setObjectName(QString::fromUtf8("changeColor"));

        verticalLayout->addWidget(changeColor);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(modus);
#endif // QT_NO_SHORTCUT

        retranslateUi(MenuPaint);

        QMetaObject::connectSlotsByName(MenuPaint);
    } // setupUi

    void retranslateUi(QWidget *MenuPaint)
    {
        MenuPaint->setWindowTitle(QApplication::translate("MenuPaint", "Form", 0, QApplication::UnicodeUTF8));
        closedLine->setText(QApplication::translate("MenuPaint", "Geschlossene Linie", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MenuPaint", "Modus", 0, QApplication::UnicodeUTF8));
        deleteLine->setText(QApplication::translate("MenuPaint", "l\303\266schen", 0, QApplication::UnicodeUTF8));
        copyButton->setText(QApplication::translate("MenuPaint", "kopieren", 0, QApplication::UnicodeUTF8));
        deletePoint->setText(QApplication::translate("MenuPaint", "Punkt l\303\266schen", 0, QApplication::UnicodeUTF8));
        addPoint->setText(QApplication::translate("MenuPaint", "Punkt hinzuf\303\274gen", 0, QApplication::UnicodeUTF8));
        changeColor->setText(QApplication::translate("MenuPaint", "Farbe \303\244ndern", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MenuPaint: public Ui_MenuPaint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUPAINT_H
