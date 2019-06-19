/********************************************************************************
** Form generated from reading UI file 'connectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDIALOG_H
#define UI_CONNECTDIALOG_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConnectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QPushButton *first;
    QPushButton *second;
    QLabel *first_path;
    QLabel *second_path;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *reject;
    QPushButton *accept;

    void setupUi(QDialog *ConnectDialog)
    {
        if (ConnectDialog->objectName().isEmpty())
            ConnectDialog->setObjectName(QStringLiteral("ConnectDialog"));
        ConnectDialog->resize(472, 109);
        verticalLayout = new QVBoxLayout(ConnectDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        first = new QPushButton(ConnectDialog);
        first->setObjectName(QStringLiteral("first"));

        formLayout->setWidget(0, QFormLayout::LabelRole, first);

        second = new QPushButton(ConnectDialog);
        second->setObjectName(QStringLiteral("second"));

        formLayout->setWidget(1, QFormLayout::LabelRole, second);

        first_path = new QLabel(ConnectDialog);
        first_path->setObjectName(QStringLiteral("first_path"));

        formLayout->setWidget(0, QFormLayout::FieldRole, first_path);

        second_path = new QLabel(ConnectDialog);
        second_path->setObjectName(QStringLiteral("second_path"));

        formLayout->setWidget(1, QFormLayout::FieldRole, second_path);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        reject = new QPushButton(ConnectDialog);
        reject->setObjectName(QStringLiteral("reject"));

        horizontalLayout->addWidget(reject);

        accept = new QPushButton(ConnectDialog);
        accept->setObjectName(QStringLiteral("accept"));

        horizontalLayout->addWidget(accept);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(ConnectDialog);

        QMetaObject::connectSlotsByName(ConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectDialog)
    {
        ConnectDialog->setWindowTitle(QApplication::translate("ConnectDialog", "Dialog", Q_NULLPTR));
        first->setText(QApplication::translate("ConnectDialog", "\320\237\320\265\321\200\320\262\321\213\320\271", Q_NULLPTR));
        second->setText(QApplication::translate("ConnectDialog", "\320\222\321\202\320\276\321\200\320\276\320\271", Q_NULLPTR));
        first_path->setText(QString());
        second_path->setText(QString());
        reject->setText(QApplication::translate("ConnectDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", Q_NULLPTR));
        accept->setText(QApplication::translate("ConnectDialog", "\320\236\320\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConnectDialog: public Ui_ConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDIALOG_H
