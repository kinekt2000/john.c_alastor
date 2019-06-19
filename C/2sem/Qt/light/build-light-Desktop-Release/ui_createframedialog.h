/********************************************************************************
** Form generated from reading UI file 'createframedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEFRAMEDIALOG_H
#define UI_CREATEFRAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateFrameDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *change_layoout;
    QVBoxLayout *settings_layout;
    QPushButton *branches;
    QSlider *angle_value;
    QFrame *line;
    QPushButton *line_frame;
    QSlider *density_value;
    QFrame *line_2;
    QPushButton *kelt_cross;
    QSlider *radius_value;
    QSpacerItem *settings_spacer;
    QFrame *display;
    QGridLayout *Field;
    QHBoxLayout *answer_layout;
    QSpacerItem *answer_spacer;
    QPushButton *reject;
    QPushButton *apply;

    void setupUi(QDialog *CreateFrameDialog)
    {
        if (CreateFrameDialog->objectName().isEmpty())
            CreateFrameDialog->setObjectName(QStringLiteral("CreateFrameDialog"));
        CreateFrameDialog->resize(312, 269);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateFrameDialog->sizePolicy().hasHeightForWidth());
        CreateFrameDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(CreateFrameDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        change_layoout = new QHBoxLayout();
        change_layoout->setObjectName(QStringLiteral("change_layoout"));
        settings_layout = new QVBoxLayout();
        settings_layout->setObjectName(QStringLiteral("settings_layout"));
        branches = new QPushButton(CreateFrameDialog);
        branches->setObjectName(QStringLiteral("branches"));

        settings_layout->addWidget(branches);

        angle_value = new QSlider(CreateFrameDialog);
        angle_value->setObjectName(QStringLiteral("angle_value"));
        angle_value->setMinimum(30);
        angle_value->setMaximum(60);
        angle_value->setPageStep(1);
        angle_value->setOrientation(Qt::Horizontal);
        angle_value->setInvertedAppearance(false);
        angle_value->setInvertedControls(true);

        settings_layout->addWidget(angle_value);

        line = new QFrame(CreateFrameDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        settings_layout->addWidget(line);

        line_frame = new QPushButton(CreateFrameDialog);
        line_frame->setObjectName(QStringLiteral("line_frame"));

        settings_layout->addWidget(line_frame);

        density_value = new QSlider(CreateFrameDialog);
        density_value->setObjectName(QStringLiteral("density_value"));
        density_value->setMinimum(1);
        density_value->setMaximum(5);
        density_value->setPageStep(1);
        density_value->setOrientation(Qt::Horizontal);

        settings_layout->addWidget(density_value);

        line_2 = new QFrame(CreateFrameDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        settings_layout->addWidget(line_2);

        kelt_cross = new QPushButton(CreateFrameDialog);
        kelt_cross->setObjectName(QStringLiteral("kelt_cross"));

        settings_layout->addWidget(kelt_cross);

        radius_value = new QSlider(CreateFrameDialog);
        radius_value->setObjectName(QStringLiteral("radius_value"));
        radius_value->setMaximum(100);
        radius_value->setOrientation(Qt::Horizontal);

        settings_layout->addWidget(radius_value);

        settings_spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        settings_layout->addItem(settings_spacer);


        change_layoout->addLayout(settings_layout);

        display = new QFrame(CreateFrameDialog);
        display->setObjectName(QStringLiteral("display"));
        display->setFrameShape(QFrame::Panel);
        display->setFrameShadow(QFrame::Sunken);
        display->setLineWidth(3);
        Field = new QGridLayout(display);
        Field->setObjectName(QStringLiteral("Field"));

        change_layoout->addWidget(display);

        change_layoout->setStretch(1, 1);

        verticalLayout->addLayout(change_layoout);

        answer_layout = new QHBoxLayout();
        answer_layout->setObjectName(QStringLiteral("answer_layout"));
        answer_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        answer_layout->addItem(answer_spacer);

        reject = new QPushButton(CreateFrameDialog);
        reject->setObjectName(QStringLiteral("reject"));

        answer_layout->addWidget(reject);

        apply = new QPushButton(CreateFrameDialog);
        apply->setObjectName(QStringLiteral("apply"));

        answer_layout->addWidget(apply);


        verticalLayout->addLayout(answer_layout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(CreateFrameDialog);

        QMetaObject::connectSlotsByName(CreateFrameDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateFrameDialog)
    {
        CreateFrameDialog->setWindowTitle(QApplication::translate("CreateFrameDialog", "Dialog", Q_NULLPTR));
        branches->setText(QApplication::translate("CreateFrameDialog", "\320\222\320\265\321\202\320\262\320\270", Q_NULLPTR));
        line_frame->setText(QApplication::translate("CreateFrameDialog", "\320\236\320\261\320\276\320\264", Q_NULLPTR));
        kelt_cross->setText(QApplication::translate("CreateFrameDialog", "\320\232\321\200\320\265\321\201\321\202", Q_NULLPTR));
        reject->setText(QApplication::translate("CreateFrameDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", Q_NULLPTR));
        apply->setText(QApplication::translate("CreateFrameDialog", "\320\236\320\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CreateFrameDialog: public Ui_CreateFrameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEFRAMEDIALOG_H
