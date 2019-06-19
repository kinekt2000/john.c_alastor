/********************************************************************************
** Form generated from reading UI file 'newimagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWIMAGEDIALOG_H
#define UI_NEWIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewImageDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QSpinBox *width;
    QLabel *width_label;
    QLabel *height_label;
    QSpinBox *height;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *Cancel;
    QPushButton *Apply;

    void setupUi(QDialog *NewImageDialog)
    {
        if (NewImageDialog->objectName().isEmpty())
            NewImageDialog->setObjectName(QStringLiteral("NewImageDialog"));
        NewImageDialog->resize(284, 132);
        verticalLayout = new QVBoxLayout(NewImageDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        width = new QSpinBox(NewImageDialog);
        width->setObjectName(QStringLiteral("width"));
        width->setMinimumSize(QSize(140, 0));
        width->setMinimum(320);
        width->setMaximum(1280);
        width->setSingleStep(64);

        formLayout->setWidget(0, QFormLayout::LabelRole, width);

        width_label = new QLabel(NewImageDialog);
        width_label->setObjectName(QStringLiteral("width_label"));

        formLayout->setWidget(0, QFormLayout::FieldRole, width_label);

        height_label = new QLabel(NewImageDialog);
        height_label->setObjectName(QStringLiteral("height_label"));

        formLayout->setWidget(1, QFormLayout::FieldRole, height_label);

        height = new QSpinBox(NewImageDialog);
        height->setObjectName(QStringLiteral("height"));
        height->setMinimumSize(QSize(140, 0));
        height->setMinimum(254);
        height->setMaximum(1024);
        height->setSingleStep(64);

        formLayout->setWidget(1, QFormLayout::LabelRole, height);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Cancel = new QPushButton(NewImageDialog);
        Cancel->setObjectName(QStringLiteral("Cancel"));

        horizontalLayout->addWidget(Cancel);

        Apply = new QPushButton(NewImageDialog);
        Apply->setObjectName(QStringLiteral("Apply"));

        horizontalLayout->addWidget(Apply);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);
        QWidget::setTabOrder(width, height);
        QWidget::setTabOrder(height, Apply);
        QWidget::setTabOrder(Apply, Cancel);

        retranslateUi(NewImageDialog);

        Apply->setDefault(false);


        QMetaObject::connectSlotsByName(NewImageDialog);
    } // setupUi

    void retranslateUi(QDialog *NewImageDialog)
    {
        NewImageDialog->setWindowTitle(QApplication::translate("NewImageDialog", "Dialog", Q_NULLPTR));
        width_label->setText(QApplication::translate("NewImageDialog", "\320\250\320\270\321\200\320\270\320\275\320\260", Q_NULLPTR));
        height_label->setText(QApplication::translate("NewImageDialog", "\320\222\321\213\321\201\320\276\321\202\320\260", Q_NULLPTR));
        Cancel->setText(QApplication::translate("NewImageDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", Q_NULLPTR));
        Apply->setText(QApplication::translate("NewImageDialog", "\320\236\320\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewImageDialog: public Ui_NewImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWIMAGEDIALOG_H
