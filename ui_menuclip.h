/********************************************************************************
** Form generated from reading UI file 'menuclip.ui'
**
** Created: Sat Oct 12 11:59:49 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUCLIP_H
#define UI_MENUCLIP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuClip
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *name;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *showScanPic;
    QLabel *label_4;
    QLabel *label_12;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *pixelAx;
    QLineEdit *pixelBx;
    QLineEdit *pixelAy;
    QLineEdit *pixelBy;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *pixelLoeschen;
    QLabel *label_6;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *BGlobx;
    QLineEdit *AGlobx;
    QLineEdit *AGloby;
    QLineEdit *BGloby;
    QLineEdit *AGlobz;
    QLineEdit *BGlobz;
    QPushButton *globLoeschen;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QRadioButton *planum;
    QRadioButton *profil;
    QSpacerItem *verticalSpacer;
    QButtonGroup *typ;

    void setupUi(QWidget *MenuClip)
    {
        if (MenuClip->objectName().isEmpty())
            MenuClip->setObjectName(QString::fromUtf8("MenuClip"));
        MenuClip->resize(332, 485);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MenuClip->sizePolicy().hasHeightForWidth());
        MenuClip->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(MenuClip);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(MenuClip);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        name = new QLineEdit(MenuClip);
        name->setObjectName(QString::fromUtf8("name"));

        horizontalLayout->addWidget(name);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        showScanPic = new QPushButton(MenuClip);
        showScanPic->setObjectName(QString::fromUtf8("showScanPic"));

        horizontalLayout_2->addWidget(showScanPic);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label_4 = new QLabel(MenuClip);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        label_12 = new QLabel(MenuClip);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_12);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(MenuClip);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(MenuClip);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        pixelAx = new QLineEdit(MenuClip);
        pixelAx->setObjectName(QString::fromUtf8("pixelAx"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pixelAx->sizePolicy().hasHeightForWidth());
        pixelAx->setSizePolicy(sizePolicy1);
        pixelAx->setMaximumSize(QSize(150, 16777215));
        pixelAx->setReadOnly(true);

        gridLayout_2->addWidget(pixelAx, 1, 1, 1, 1);

        pixelBx = new QLineEdit(MenuClip);
        pixelBx->setObjectName(QString::fromUtf8("pixelBx"));
        sizePolicy1.setHeightForWidth(pixelBx->sizePolicy().hasHeightForWidth());
        pixelBx->setSizePolicy(sizePolicy1);
        pixelBx->setMaximumSize(QSize(150, 16777215));
        pixelBx->setReadOnly(true);

        gridLayout_2->addWidget(pixelBx, 2, 1, 1, 1);

        pixelAy = new QLineEdit(MenuClip);
        pixelAy->setObjectName(QString::fromUtf8("pixelAy"));
        sizePolicy1.setHeightForWidth(pixelAy->sizePolicy().hasHeightForWidth());
        pixelAy->setSizePolicy(sizePolicy1);
        pixelAy->setMaximumSize(QSize(150, 16777215));
        pixelAy->setReadOnly(true);

        gridLayout_2->addWidget(pixelAy, 1, 2, 1, 1);

        pixelBy = new QLineEdit(MenuClip);
        pixelBy->setObjectName(QString::fromUtf8("pixelBy"));
        sizePolicy1.setHeightForWidth(pixelBy->sizePolicy().hasHeightForWidth());
        pixelBy->setSizePolicy(sizePolicy1);
        pixelBy->setMaximumSize(QSize(150, 16777215));
        pixelBy->setReadOnly(true);

        gridLayout_2->addWidget(pixelBy, 2, 2, 1, 1);

        label_10 = new QLabel(MenuClip);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Sans Serif"));
        font2.setPointSize(8);
        label_10->setFont(font2);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 0, 1, 1, 1);

        label_11 = new QLabel(MenuClip);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font2);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_11, 0, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        pixelLoeschen = new QPushButton(MenuClip);
        pixelLoeschen->setObjectName(QString::fromUtf8("pixelLoeschen"));

        verticalLayout_2->addWidget(pixelLoeschen);

        label_6 = new QLabel(MenuClip);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_6);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_7 = new QLabel(MenuClip);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(MenuClip);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 0, 1, 1, 1);

        label_9 = new QLabel(MenuClip);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font2);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 0, 2, 1, 1);

        BGlobx = new QLineEdit(MenuClip);
        BGlobx->setObjectName(QString::fromUtf8("BGlobx"));
        BGlobx->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(BGlobx, 2, 0, 1, 1);

        AGlobx = new QLineEdit(MenuClip);
        AGlobx->setObjectName(QString::fromUtf8("AGlobx"));
        AGlobx->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(AGlobx, 1, 0, 1, 1);

        AGloby = new QLineEdit(MenuClip);
        AGloby->setObjectName(QString::fromUtf8("AGloby"));
        AGloby->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(AGloby, 1, 1, 1, 1);

        BGloby = new QLineEdit(MenuClip);
        BGloby->setObjectName(QString::fromUtf8("BGloby"));
        BGloby->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(BGloby, 2, 1, 1, 1);

        AGlobz = new QLineEdit(MenuClip);
        AGlobz->setObjectName(QString::fromUtf8("AGlobz"));
        AGlobz->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(AGlobz, 1, 2, 1, 1);

        BGlobz = new QLineEdit(MenuClip);
        BGlobz->setObjectName(QString::fromUtf8("BGlobz"));
        BGlobz->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(BGlobz, 2, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        globLoeschen = new QPushButton(MenuClip);
        globLoeschen->setObjectName(QString::fromUtf8("globLoeschen"));

        verticalLayout_2->addWidget(globLoeschen);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(MenuClip);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        planum = new QRadioButton(MenuClip);
        typ = new QButtonGroup(MenuClip);
        typ->setObjectName(QString::fromUtf8("typ"));
        typ->addButton(planum);
        planum->setObjectName(QString::fromUtf8("planum"));
        planum->setChecked(true);

        verticalLayout->addWidget(planum);

        profil = new QRadioButton(MenuClip);
        typ->addButton(profil);
        profil->setObjectName(QString::fromUtf8("profil"));

        verticalLayout->addWidget(profil);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(MenuClip);

        QMetaObject::connectSlotsByName(MenuClip);
    } // setupUi

    void retranslateUi(QWidget *MenuClip)
    {
        MenuClip->setWindowTitle(QApplication::translate("MenuClip", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MenuClip", "Name", 0, QApplication::UnicodeUTF8));
        showScanPic->setText(QApplication::translate("MenuClip", "Zeige Scan", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MenuClip", "Einh\303\244ngepunkte", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MenuClip", "Pixel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MenuClip", "A", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MenuClip", "B", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MenuClip", "x", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MenuClip", "y", 0, QApplication::UnicodeUTF8));
        pixelLoeschen->setText(QApplication::translate("MenuClip", "l\303\266schen", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MenuClip", "Glob. Koordinaten", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MenuClip", "x", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MenuClip", "y", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MenuClip", "z", 0, QApplication::UnicodeUTF8));
        globLoeschen->setText(QApplication::translate("MenuClip", "l\303\266schen", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MenuClip", "Typ", 0, QApplication::UnicodeUTF8));
        planum->setText(QApplication::translate("MenuClip", "Planum", "0", QApplication::UnicodeUTF8));
        profil->setText(QApplication::translate("MenuClip", "Profil", "1", QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MenuClip: public Ui_MenuClip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUCLIP_H
