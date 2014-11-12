/********************************************************************************
** Form generated from reading UI file 'groupdockwidget.ui'
**
** Created: Fri Oct 11 00:52:54 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPDOCKWIDGET_H
#define UI_GROUPDOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupDockWidget
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTreeView *elementeView;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *addGroupButton;
    QTreeView *gruppenView;
    QGridLayout *gridLayout;
    QCheckBox *display;

    void setupUi(QDockWidget *GroupDockWidget)
    {
        if (GroupDockWidget->objectName().isEmpty())
            GroupDockWidget->setObjectName(QString::fromUtf8("GroupDockWidget"));
        GroupDockWidget->resize(227, 357);
        GroupDockWidget->setMinimumSize(QSize(221, 300));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        elementeView = new QTreeView(dockWidgetContents);
        elementeView->setObjectName(QString::fromUtf8("elementeView"));
        elementeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(elementeView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(false);

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addGroupButton = new QPushButton(dockWidgetContents);
        addGroupButton->setObjectName(QString::fromUtf8("addGroupButton"));
        addGroupButton->setEnabled(false);

        horizontalLayout->addWidget(addGroupButton);


        verticalLayout->addLayout(horizontalLayout);

        gruppenView = new QTreeView(dockWidgetContents);
        gruppenView->setObjectName(QString::fromUtf8("gruppenView"));
        gruppenView->setEnabled(true);

        verticalLayout->addWidget(gruppenView);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        display = new QCheckBox(dockWidgetContents);
        display->setObjectName(QString::fromUtf8("display"));

        gridLayout->addWidget(display, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        GroupDockWidget->setWidget(dockWidgetContents);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(elementeView);
        label_3->setBuddy(gruppenView);
#endif // QT_NO_SHORTCUT

        retranslateUi(GroupDockWidget);

        QMetaObject::connectSlotsByName(GroupDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *GroupDockWidget)
    {
        GroupDockWidget->setWindowTitle(QApplication::translate("GroupDockWidget", "Gruppenverwaltung", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GroupDockWidget", "Elemente", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GroupDockWidget", "Gruppen", 0, QApplication::UnicodeUTF8));
        addGroupButton->setText(QApplication::translate("GroupDockWidget", "+", 0, QApplication::UnicodeUTF8));
        display->setText(QApplication::translate("GroupDockWidget", "anzeigen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GroupDockWidget: public Ui_GroupDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPDOCKWIDGET_H
