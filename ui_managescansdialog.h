/********************************************************************************
** Form generated from reading UI file 'managescansdialog.ui'
**
** Created: Sat Oct 12 10:59:08 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGESCANSDIALOG_H
#define UI_MANAGESCANSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ManageScansDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *addScan;
    QSpacerItem *horizontalSpacer_2;
    QListView *scanView;
    QListView *texturesView;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *deleteScanButton;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *deleteTextureButton;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *ManageScansDialog)
    {
        if (ManageScansDialog->objectName().isEmpty())
            ManageScansDialog->setObjectName(QString::fromUtf8("ManageScansDialog"));
        ManageScansDialog->resize(800, 550);
        verticalLayout_2 = new QVBoxLayout(ManageScansDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        addScan = new QPushButton(ManageScansDialog);
        addScan->setObjectName(QString::fromUtf8("addScan"));

        horizontalLayout_2->addWidget(addScan);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        scanView = new QListView(ManageScansDialog);
        scanView->setObjectName(QString::fromUtf8("scanView"));

        gridLayout->addWidget(scanView, 3, 1, 1, 1);

        texturesView = new QListView(ManageScansDialog);
        texturesView->setObjectName(QString::fromUtf8("texturesView"));

        gridLayout->addWidget(texturesView, 3, 3, 1, 1);

        label = new QLabel(ManageScansDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 1, 1, 1);

        label_2 = new QLabel(ManageScansDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 3, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        deleteScanButton = new QPushButton(ManageScansDialog);
        deleteScanButton->setObjectName(QString::fromUtf8("deleteScanButton"));

        horizontalLayout_5->addWidget(deleteScanButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_5, 5, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        deleteTextureButton = new QPushButton(ManageScansDialog);
        deleteTextureButton->setObjectName(QString::fromUtf8("deleteTextureButton"));

        horizontalLayout_4->addWidget(deleteTextureButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_4, 5, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addLayout(verticalLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(texturesView);
        label_2->setBuddy(scanView);
#endif // QT_NO_SHORTCUT

        retranslateUi(ManageScansDialog);

        QMetaObject::connectSlotsByName(ManageScansDialog);
    } // setupUi

    void retranslateUi(QDialog *ManageScansDialog)
    {
        ManageScansDialog->setWindowTitle(QApplication::translate("ManageScansDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        addScan->setText(QApplication::translate("ManageScansDialog", "neuen Scan hinzuf\303\274gen", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ManageScansDialog", "Scans", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ManageScansDialog", "Zeichnungen des Scans", 0, QApplication::UnicodeUTF8));
        deleteScanButton->setText(QApplication::translate("ManageScansDialog", "Scan l\303\266schen", 0, QApplication::UnicodeUTF8));
        deleteTextureButton->setText(QApplication::translate("ManageScansDialog", "Zeichnung l\303\266schen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ManageScansDialog: public Ui_ManageScansDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGESCANSDIALOG_H
