/********************************************************************************
** Form generated from reading UI file 'newgroupdialog.ui'
**
** Created: Thu Oct 10 15:37:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGROUPDIALOG_H
#define UI_NEWGROUPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewGroupDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *ColorButton;
    QLineEdit *name;
    QPushButton *addButton;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QComboBox *gruppenTypenSelect;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewGroupDialog)
    {
        if (NewGroupDialog->objectName().isEmpty())
            NewGroupDialog->setObjectName(QString::fromUtf8("NewGroupDialog"));
        NewGroupDialog->resize(383, 234);
        verticalLayout_2 = new QVBoxLayout(NewGroupDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ColorButton = new QPushButton(NewGroupDialog);
        ColorButton->setObjectName(QString::fromUtf8("ColorButton"));

        gridLayout->addWidget(ColorButton, 2, 1, 1, 1);

        name = new QLineEdit(NewGroupDialog);
        name->setObjectName(QString::fromUtf8("name"));

        gridLayout->addWidget(name, 1, 1, 1, 1);

        addButton = new QPushButton(NewGroupDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 5, 1, 1, 1, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 1, 1, 1);

        label_3 = new QLabel(NewGroupDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        gruppenTypenSelect = new QComboBox(NewGroupDialog);
        gruppenTypenSelect->setObjectName(QString::fromUtf8("gruppenTypenSelect"));

        gridLayout->addWidget(gruppenTypenSelect, 3, 1, 1, 1);

        label_2 = new QLabel(NewGroupDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(NewGroupDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(NewGroupDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout_2->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label_3->setBuddy(gruppenTypenSelect);
        label_2->setBuddy(ColorButton);
        label->setBuddy(name);
#endif // QT_NO_SHORTCUT

        retranslateUi(NewGroupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewGroupDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewGroupDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewGroupDialog);
    } // setupUi

    void retranslateUi(QDialog *NewGroupDialog)
    {
        NewGroupDialog->setWindowTitle(QApplication::translate("NewGroupDialog", "Neue Gruppe erstellen", 0, QApplication::UnicodeUTF8));
        ColorButton->setText(QApplication::translate("NewGroupDialog", "PushButton", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("NewGroupDialog", "hinzuf\303\274gen", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewGroupDialog", "Typ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewGroupDialog", "Farbe", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewGroupDialog", "Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewGroupDialog: public Ui_NewGroupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGROUPDIALOG_H
