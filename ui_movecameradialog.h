/********************************************************************************
** Form generated from reading UI file 'movecameradialog.ui'
**
** Created: Thu Oct 10 15:37:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVECAMERADIALOG_H
#define UI_MOVECAMERADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MoveCameraDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QLineEdit *lookAtZ;
    QLabel *label_9;
    QLineEdit *lookAtX;
    QLabel *label_8;
    QLineEdit *lookAtY;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QGridLayout *gridLayout_2;
    QLabel *label_11;
    QLineEdit *camX;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_12;
    QLineEdit *camY;
    QLabel *label_10;
    QLineEdit *camZ;
    QPushButton *doButton;

    void setupUi(QDialog *MoveCameraDialog)
    {
        if (MoveCameraDialog->objectName().isEmpty())
            MoveCameraDialog->setObjectName(QString::fromUtf8("MoveCameraDialog"));
        MoveCameraDialog->resize(248, 293);
        verticalLayout = new QVBoxLayout(MoveCameraDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(MoveCameraDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lookAtZ = new QLineEdit(MoveCameraDialog);
        lookAtZ->setObjectName(QString::fromUtf8("lookAtZ"));

        gridLayout->addWidget(lookAtZ, 2, 1, 1, 1);

        label_9 = new QLabel(MoveCameraDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(8);
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 2, 0, 1, 1);

        lookAtX = new QLineEdit(MoveCameraDialog);
        lookAtX->setObjectName(QString::fromUtf8("lookAtX"));

        gridLayout->addWidget(lookAtX, 0, 1, 1, 1);

        label_8 = new QLabel(MoveCameraDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        lookAtY = new QLineEdit(MoveCameraDialog);
        lookAtY->setObjectName(QString::fromUtf8("lookAtY"));

        gridLayout->addWidget(lookAtY, 1, 1, 1, 1);

        label_7 = new QLabel(MoveCameraDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        label_2 = new QLabel(MoveCameraDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_11 = new QLabel(MoveCameraDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_11, 1, 0, 1, 1);

        camX = new QLineEdit(MoveCameraDialog);
        camX->setObjectName(QString::fromUtf8("camX"));

        gridLayout_2->addWidget(camX, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        label_12 = new QLabel(MoveCameraDialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_12, 0, 0, 1, 1);

        camY = new QLineEdit(MoveCameraDialog);
        camY->setObjectName(QString::fromUtf8("camY"));

        gridLayout_2->addWidget(camY, 1, 1, 1, 1);

        label_10 = new QLabel(MoveCameraDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 2, 0, 1, 1);

        camZ = new QLineEdit(MoveCameraDialog);
        camZ->setObjectName(QString::fromUtf8("camZ"));

        gridLayout_2->addWidget(camZ, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        doButton = new QPushButton(MoveCameraDialog);
        doButton->setObjectName(QString::fromUtf8("doButton"));

        verticalLayout->addWidget(doButton);


        retranslateUi(MoveCameraDialog);

        QMetaObject::connectSlotsByName(MoveCameraDialog);
    } // setupUi

    void retranslateUi(QDialog *MoveCameraDialog)
    {
        MoveCameraDialog->setWindowTitle(QApplication::translate("MoveCameraDialog", "Kameraposition setzten", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MoveCameraDialog", "Look-At", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MoveCameraDialog", "z", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MoveCameraDialog", "y (H\303\266he)", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MoveCameraDialog", "x", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MoveCameraDialog", "Kameraposition", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MoveCameraDialog", "y (H\303\266he)", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MoveCameraDialog", "x", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MoveCameraDialog", "z", 0, QApplication::UnicodeUTF8));
        doButton->setText(QApplication::translate("MoveCameraDialog", "Durchf\303\274hren", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MoveCameraDialog: public Ui_MoveCameraDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVECAMERADIALOG_H
