/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *new_file;
    QAction *open_file;
    QAction *save_file;
    QAction *quit;
    QAction *about;
    QAction *about_image;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *processing_layout;
    QVBoxLayout *functions_layout;
    QPushButton *Hexagon;
    QPushButton *Copy;
    QPushButton *Recolor;
    QPushButton *Frame;
    QPushButton *Pen;
    QFormLayout *parameters_layout;
    QHBoxLayout *palette_layout;
    QPushButton *foreground;
    QPushButton *background;
    QCheckBox *Fill;
    QLabel *Fill_Label;
    QSpinBox *Width;
    QLabel *Width_Label;
    QSpacerItem *verticalSpacer;
    QFrame *Pic;
    QGridLayout *Field;
    QMenuBar *menuBar;
    QMenu *File;
    QMenu *Reference;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(830, 582);
        new_file = new QAction(MainWindow);
        new_file->setObjectName(QStringLiteral("new_file"));
        open_file = new QAction(MainWindow);
        open_file->setObjectName(QStringLiteral("open_file"));
        save_file = new QAction(MainWindow);
        save_file->setObjectName(QStringLiteral("save_file"));
        quit = new QAction(MainWindow);
        quit->setObjectName(QStringLiteral("quit"));
        about = new QAction(MainWindow);
        about->setObjectName(QStringLiteral("about"));
        about_image = new QAction(MainWindow);
        about_image->setObjectName(QStringLiteral("about_image"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(9, 9, 9, -1);
        processing_layout = new QVBoxLayout();
        processing_layout->setSpacing(6);
        processing_layout->setObjectName(QStringLiteral("processing_layout"));
        processing_layout->setSizeConstraint(QLayout::SetFixedSize);
        processing_layout->setContentsMargins(-1, -1, 0, -1);
        functions_layout = new QVBoxLayout();
        functions_layout->setSpacing(6);
        functions_layout->setObjectName(QStringLiteral("functions_layout"));
        functions_layout->setSizeConstraint(QLayout::SetFixedSize);
        Hexagon = new QPushButton(centralWidget);
        Hexagon->setObjectName(QStringLiteral("Hexagon"));
        sizePolicy.setHeightForWidth(Hexagon->sizePolicy().hasHeightForWidth());
        Hexagon->setSizePolicy(sizePolicy);
        Hexagon->setMinimumSize(QSize(150, 0));
        Hexagon->setSizeIncrement(QSize(0, 0));
        Hexagon->setBaseSize(QSize(0, 0));
        Hexagon->setIconSize(QSize(16, 16));
        Hexagon->setFlat(false);

        functions_layout->addWidget(Hexagon);

        Copy = new QPushButton(centralWidget);
        Copy->setObjectName(QStringLiteral("Copy"));
        sizePolicy.setHeightForWidth(Copy->sizePolicy().hasHeightForWidth());
        Copy->setSizePolicy(sizePolicy);
        Copy->setMinimumSize(QSize(150, 0));

        functions_layout->addWidget(Copy);

        Recolor = new QPushButton(centralWidget);
        Recolor->setObjectName(QStringLiteral("Recolor"));
        sizePolicy.setHeightForWidth(Recolor->sizePolicy().hasHeightForWidth());
        Recolor->setSizePolicy(sizePolicy);
        Recolor->setMinimumSize(QSize(150, 0));

        functions_layout->addWidget(Recolor);

        Frame = new QPushButton(centralWidget);
        Frame->setObjectName(QStringLiteral("Frame"));
        sizePolicy.setHeightForWidth(Frame->sizePolicy().hasHeightForWidth());
        Frame->setSizePolicy(sizePolicy);
        Frame->setMinimumSize(QSize(150, 0));

        functions_layout->addWidget(Frame);

        Pen = new QPushButton(centralWidget);
        Pen->setObjectName(QStringLiteral("Pen"));
        sizePolicy.setHeightForWidth(Pen->sizePolicy().hasHeightForWidth());
        Pen->setSizePolicy(sizePolicy);
        Pen->setMinimumSize(QSize(150, 0));

        functions_layout->addWidget(Pen);


        processing_layout->addLayout(functions_layout);

        parameters_layout = new QFormLayout();
        parameters_layout->setSpacing(6);
        parameters_layout->setObjectName(QStringLiteral("parameters_layout"));
        parameters_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        parameters_layout->setContentsMargins(10, -1, -1, -1);
        palette_layout = new QHBoxLayout();
        palette_layout->setSpacing(6);
        palette_layout->setObjectName(QStringLiteral("palette_layout"));
        foreground = new QPushButton(centralWidget);
        foreground->setObjectName(QStringLiteral("foreground"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(20);
        sizePolicy1.setVerticalStretch(20);
        sizePolicy1.setHeightForWidth(foreground->sizePolicy().hasHeightForWidth());
        foreground->setSizePolicy(sizePolicy1);
        foreground->setMinimumSize(QSize(20, 20));
        foreground->setMaximumSize(QSize(20, 20));
        foreground->setFocusPolicy(Qt::NoFocus);
        foreground->setContextMenuPolicy(Qt::DefaultContextMenu);
        foreground->setAutoFillBackground(true);
        foreground->setFlat(true);

        palette_layout->addWidget(foreground);

        background = new QPushButton(centralWidget);
        background->setObjectName(QStringLiteral("background"));
        sizePolicy1.setHeightForWidth(background->sizePolicy().hasHeightForWidth());
        background->setSizePolicy(sizePolicy1);
        background->setMinimumSize(QSize(20, 20));
        background->setMaximumSize(QSize(20, 20));
        background->setFocusPolicy(Qt::NoFocus);
        background->setContextMenuPolicy(Qt::DefaultContextMenu);
        background->setAutoFillBackground(true);
        background->setFlat(true);

        palette_layout->addWidget(background);


        parameters_layout->setLayout(0, QFormLayout::LabelRole, palette_layout);

        Fill = new QCheckBox(centralWidget);
        Fill->setObjectName(QStringLiteral("Fill"));

        parameters_layout->setWidget(1, QFormLayout::LabelRole, Fill);

        Fill_Label = new QLabel(centralWidget);
        Fill_Label->setObjectName(QStringLiteral("Fill_Label"));

        parameters_layout->setWidget(1, QFormLayout::FieldRole, Fill_Label);

        Width = new QSpinBox(centralWidget);
        Width->setObjectName(QStringLiteral("Width"));
        Width->setMinimumSize(QSize(50, 0));
        Width->setMinimum(1);
        Width->setMaximum(50);
        Width->setValue(10);

        parameters_layout->setWidget(2, QFormLayout::LabelRole, Width);

        Width_Label = new QLabel(centralWidget);
        Width_Label->setObjectName(QStringLiteral("Width_Label"));

        parameters_layout->setWidget(2, QFormLayout::FieldRole, Width_Label);


        processing_layout->addLayout(parameters_layout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        processing_layout->addItem(verticalSpacer);

        processing_layout->setStretch(2, 1);

        horizontalLayout->addLayout(processing_layout);

        Pic = new QFrame(centralWidget);
        Pic->setObjectName(QStringLiteral("Pic"));
        Pic->setCursor(QCursor(Qt::CrossCursor));
        Pic->setMouseTracking(false);
        Pic->setAutoFillBackground(true);
        Pic->setFrameShape(QFrame::Panel);
        Pic->setFrameShadow(QFrame::Sunken);
        Pic->setLineWidth(3);
        Pic->setMidLineWidth(0);
        Field = new QGridLayout(Pic);
        Field->setSpacing(6);
        Field->setContentsMargins(11, 11, 11, 11);
        Field->setObjectName(QStringLiteral("Field"));

        horizontalLayout->addWidget(Pic);

        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 830, 22));
        File = new QMenu(menuBar);
        File->setObjectName(QStringLiteral("File"));
        Reference = new QMenu(menuBar);
        Reference->setObjectName(QStringLiteral("Reference"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(File->menuAction());
        menuBar->addAction(Reference->menuAction());
        File->addAction(new_file);
        File->addAction(open_file);
        File->addAction(save_file);
        File->addSeparator();
        File->addAction(quit);
        Reference->addAction(about);
        Reference->addAction(about_image);

        retranslateUi(MainWindow);

        Hexagon->setDefault(false);
        foreground->setDefault(false);
        background->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Painter", Q_NULLPTR));
        new_file->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        new_file->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        open_file->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        open_file->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        save_file->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        save_file->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        quit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        about->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", Q_NULLPTR));
        about_image->setText(QApplication::translate("MainWindow", "\320\236\320\261 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\270", Q_NULLPTR));
        Hexagon->setText(QApplication::translate("MainWindow", "\320\250\320\265\321\201\321\202\320\270\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272", Q_NULLPTR));
        Copy->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", Q_NULLPTR));
        Recolor->setText(QApplication::translate("MainWindow", "\320\241\320\274\320\265\320\275\320\260 \321\206\320\262\320\265\321\202\320\260", Q_NULLPTR));
        Frame->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\274\320\272\320\260", Q_NULLPTR));
        Pen->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\276", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        foreground->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>\320\236\321\201\320\275\320\276\320\262\320\275\320\276\320\271 \321\206\320\262\320\265\321\202</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        foreground->setText(QString());
#ifndef QT_NO_TOOLTIP
        background->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\271 \321\206\320\262\320\265\321\202</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        background->setText(QString());
        Fill->setText(QString());
        Fill_Label->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\273\320\270\320\262\320\272\320\260", Q_NULLPTR));
        Width_Label->setText(QApplication::translate("MainWindow", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260", Q_NULLPTR));
        File->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", Q_NULLPTR));
        Reference->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
