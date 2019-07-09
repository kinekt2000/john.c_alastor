/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *Field;
    QHBoxLayout *ButtonsLayout;
    QPushButton *Quit;
    QPushButton *Load;
    QSpacerItem *horizontalSpacer;
    QPushButton *Stop;
    QPushButton *Start;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(423, 411);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Field = new QGridLayout();
        Field->setSpacing(6);
        Field->setObjectName(QStringLiteral("Field"));

        verticalLayout->addLayout(Field);

        ButtonsLayout = new QHBoxLayout();
        ButtonsLayout->setSpacing(6);
        ButtonsLayout->setObjectName(QStringLiteral("ButtonsLayout"));
        Quit = new QPushButton(Widget);
        Quit->setObjectName(QStringLiteral("Quit"));

        ButtonsLayout->addWidget(Quit);

        Load = new QPushButton(Widget);
        Load->setObjectName(QStringLiteral("Load"));

        ButtonsLayout->addWidget(Load);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        ButtonsLayout->addItem(horizontalSpacer);

        Stop = new QPushButton(Widget);
        Stop->setObjectName(QStringLiteral("Stop"));
        Stop->setEnabled(false);

        ButtonsLayout->addWidget(Stop);

        Start = new QPushButton(Widget);
        Start->setObjectName(QStringLiteral("Start"));

        ButtonsLayout->addWidget(Start);


        verticalLayout->addLayout(ButtonsLayout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        Quit->setText(QApplication::translate("Widget", "Quit", Q_NULLPTR));
        Load->setText(QApplication::translate("Widget", "Load", Q_NULLPTR));
        Stop->setText(QApplication::translate("Widget", "Stop", Q_NULLPTR));
        Start->setText(QApplication::translate("Widget", "Start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
