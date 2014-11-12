/********************************************************************************
** Form generated from reading UI file 'menusplit.ui'
**
** Created: Thu Oct 10 15:37:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUSPLIT_H
#define UI_MENUSPLIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuSplit
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *modus;
    QPushButton *deleteArea;
    QListView *rectView;
    QTreeView *treeView;
    QTreeView *treeView_2;

    void setupUi(QWidget *MenuSplit)
    {
        if (MenuSplit->objectName().isEmpty())
            MenuSplit->setObjectName(QString::fromUtf8("MenuSplit"));
        MenuSplit->resize(267, 517);
        verticalLayout_2 = new QVBoxLayout(MenuSplit);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(MenuSplit);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        name = new QLineEdit(MenuSplit);
        name->setObjectName(QString::fromUtf8("name"));

        horizontalLayout->addWidget(name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(MenuSplit);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        modus = new QComboBox(MenuSplit);
        modus->setObjectName(QString::fromUtf8("modus"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(modus->sizePolicy().hasHeightForWidth());
        modus->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(modus);


        verticalLayout->addLayout(horizontalLayout_2);

        deleteArea = new QPushButton(MenuSplit);
        deleteArea->setObjectName(QString::fromUtf8("deleteArea"));

        verticalLayout->addWidget(deleteArea);

        rectView = new QListView(MenuSplit);
        rectView->setObjectName(QString::fromUtf8("rectView"));

        verticalLayout->addWidget(rectView);

        treeView = new QTreeView(MenuSplit);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);

        treeView_2 = new QTreeView(MenuSplit);
        treeView_2->setObjectName(QString::fromUtf8("treeView_2"));

        verticalLayout->addWidget(treeView_2);


        verticalLayout_2->addLayout(verticalLayout);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(name);
        label->setBuddy(modus);
#endif // QT_NO_SHORTCUT

        retranslateUi(MenuSplit);

        QMetaObject::connectSlotsByName(MenuSplit);
    } // setupUi

    void retranslateUi(QWidget *MenuSplit)
    {
        MenuSplit->setWindowTitle(QApplication::translate("MenuSplit", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MenuSplit", "Name", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MenuSplit", "Textur", 0, QApplication::UnicodeUTF8));
        deleteArea->setText(QApplication::translate("MenuSplit", "Textur  l\303\266schen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MenuSplit: public Ui_MenuSplit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUSPLIT_H
