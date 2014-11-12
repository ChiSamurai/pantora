/********************************************************************************
** Form generated from reading UI file 'projectproperties.ui'
**
** Created: Thu Oct 10 15:37:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTPROPERTIES_H
#define UI_PROJECTPROPERTIES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProjectProperties
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *flipx;
    QLabel *label;
    QGridLayout *gridLayout;
    QLineEdit *nullZ;
    QLabel *label_9;
    QLineEdit *nullX;
    QLabel *label_8;
    QLineEdit *nullY;
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
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProjectProperties)
    {
        if (ProjectProperties->objectName().isEmpty())
            ProjectProperties->setObjectName(QString::fromUtf8("ProjectProperties"));
        ProjectProperties->resize(283, 367);
        verticalLayout = new QVBoxLayout(ProjectProperties);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        flipx = new QCheckBox(ProjectProperties);
        flipx->setObjectName(QString::fromUtf8("flipx"));

        verticalLayout->addWidget(flipx);

        label = new QLabel(ProjectProperties);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nullZ = new QLineEdit(ProjectProperties);
        nullZ->setObjectName(QString::fromUtf8("nullZ"));

        gridLayout->addWidget(nullZ, 2, 1, 1, 1);

        label_9 = new QLabel(ProjectProperties);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(8);
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 2, 0, 1, 1);

        nullX = new QLineEdit(ProjectProperties);
        nullX->setObjectName(QString::fromUtf8("nullX"));

        gridLayout->addWidget(nullX, 0, 1, 1, 1);

        label_8 = new QLabel(ProjectProperties);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        nullY = new QLineEdit(ProjectProperties);
        nullY->setObjectName(QString::fromUtf8("nullY"));

        gridLayout->addWidget(nullY, 1, 1, 1, 1);

        label_7 = new QLabel(ProjectProperties);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        label_2 = new QLabel(ProjectProperties);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_11 = new QLabel(ProjectProperties);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_11, 1, 0, 1, 1);

        camX = new QLineEdit(ProjectProperties);
        camX->setObjectName(QString::fromUtf8("camX"));

        gridLayout_2->addWidget(camX, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        label_12 = new QLabel(ProjectProperties);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_12, 0, 0, 1, 1);

        camY = new QLineEdit(ProjectProperties);
        camY->setObjectName(QString::fromUtf8("camY"));

        gridLayout_2->addWidget(camY, 1, 1, 1, 1);

        label_10 = new QLabel(ProjectProperties);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 2, 0, 1, 1);

        camZ = new QLineEdit(ProjectProperties);
        camZ->setObjectName(QString::fromUtf8("camZ"));

        gridLayout_2->addWidget(camZ, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(ProjectProperties);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(flipx, nullX);
        QWidget::setTabOrder(nullX, nullY);
        QWidget::setTabOrder(nullY, nullZ);
        QWidget::setTabOrder(nullZ, buttonBox);

        retranslateUi(ProjectProperties);
        QObject::connect(buttonBox, SIGNAL(accepted()), ProjectProperties, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ProjectProperties, SLOT(reject()));

        QMetaObject::connectSlotsByName(ProjectProperties);
    } // setupUi

    void retranslateUi(QDialog *ProjectProperties)
    {
        ProjectProperties->setWindowTitle(QApplication::translate("ProjectProperties", "Projekteinstellungen", 0, QApplication::UnicodeUTF8));
        flipx->setText(QApplication::translate("ProjectProperties", "rechtsh\303\244ndiges Koordiantensystem", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ProjectProperties", "Blickpunkt der Ansicht", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ProjectProperties", "z", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ProjectProperties", "y (H\303\266he)", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ProjectProperties", "x", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ProjectProperties", "Kameraposition", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ProjectProperties", "y (H\303\266he)", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("ProjectProperties", "x", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ProjectProperties", "z", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProjectProperties: public Ui_ProjectProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTPROPERTIES_H
