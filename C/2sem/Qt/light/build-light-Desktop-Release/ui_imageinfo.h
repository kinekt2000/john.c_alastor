/********************************************************************************
** Form generated from reading UI file 'imageinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEINFO_H
#define UI_IMAGEINFO_H

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

class Ui_ImageInfo
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *info_layout;
    QLabel *label_width;
    QLabel *width;
    QLabel *label_height;
    QLabel *height;
    QLabel *label_size;
    QLabel *size;
    QHBoxLayout *accept_layout;
    QSpacerItem *horizontalSpacer;
    QPushButton *accept;

    void setupUi(QDialog *ImageInfo)
    {
        if (ImageInfo->objectName().isEmpty())
            ImageInfo->setObjectName(QStringLiteral("ImageInfo"));
        ImageInfo->resize(355, 141);
        verticalLayout = new QVBoxLayout(ImageInfo);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        info_layout = new QFormLayout();
        info_layout->setObjectName(QStringLiteral("info_layout"));
        info_layout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_width = new QLabel(ImageInfo);
        label_width->setObjectName(QStringLiteral("label_width"));
        label_width->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_width->setMargin(2);

        info_layout->setWidget(0, QFormLayout::LabelRole, label_width);

        width = new QLabel(ImageInfo);
        width->setObjectName(QStringLiteral("width"));
        width->setAutoFillBackground(true);

        info_layout->setWidget(0, QFormLayout::FieldRole, width);

        label_height = new QLabel(ImageInfo);
        label_height->setObjectName(QStringLiteral("label_height"));
        label_height->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_height->setMargin(2);

        info_layout->setWidget(1, QFormLayout::LabelRole, label_height);

        height = new QLabel(ImageInfo);
        height->setObjectName(QStringLiteral("height"));
        height->setAutoFillBackground(true);

        info_layout->setWidget(1, QFormLayout::FieldRole, height);

        label_size = new QLabel(ImageInfo);
        label_size->setObjectName(QStringLiteral("label_size"));
        label_size->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_size->setMargin(5);

        info_layout->setWidget(2, QFormLayout::LabelRole, label_size);

        size = new QLabel(ImageInfo);
        size->setObjectName(QStringLiteral("size"));
        size->setAutoFillBackground(true);

        info_layout->setWidget(2, QFormLayout::FieldRole, size);


        verticalLayout->addLayout(info_layout);

        accept_layout = new QHBoxLayout();
        accept_layout->setObjectName(QStringLiteral("accept_layout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        accept_layout->addItem(horizontalSpacer);

        accept = new QPushButton(ImageInfo);
        accept->setObjectName(QStringLiteral("accept"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(accept->sizePolicy().hasHeightForWidth());
        accept->setSizePolicy(sizePolicy);

        accept_layout->addWidget(accept);


        verticalLayout->addLayout(accept_layout);

        verticalLayout->setStretch(0, 9);
        verticalLayout->setStretch(1, 1);

        retranslateUi(ImageInfo);
        QObject::connect(accept, SIGNAL(clicked()), ImageInfo, SLOT(accept()));

        QMetaObject::connectSlotsByName(ImageInfo);
    } // setupUi

    void retranslateUi(QDialog *ImageInfo)
    {
        ImageInfo->setWindowTitle(QApplication::translate("ImageInfo", "\320\236\320\261 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\270", Q_NULLPTR));
        label_width->setText(QApplication::translate("ImageInfo", "\320\250\320\270\321\200\320\270\320\275\320\260", Q_NULLPTR));
        width->setText(QString());
        label_height->setText(QApplication::translate("ImageInfo", "\320\222\321\213\321\201\320\276\321\202\320\260", Q_NULLPTR));
        height->setText(QString());
        label_size->setText(QApplication::translate("ImageInfo", "\320\227\320\260\320\275\320\270\320\274\320\260\320\265\320\274\320\276\320\265 \320\274\320\265\321\201\321\202\320\276", Q_NULLPTR));
        size->setText(QString());
        accept->setText(QApplication::translate("ImageInfo", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageInfo: public Ui_ImageInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEINFO_H
