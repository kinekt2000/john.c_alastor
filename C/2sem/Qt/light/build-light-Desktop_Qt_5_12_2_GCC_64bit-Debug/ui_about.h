/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *about_layout;
    QTextBrowser *textBrowser;
    QHBoxLayout *accept_layout;
    QSpacerItem *horizontalSpacer;
    QPushButton *accept;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(614, 417);
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        about_layout = new QGridLayout();
        about_layout->setObjectName(QString::fromUtf8("about_layout"));
        textBrowser = new QTextBrowser(About);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        about_layout->addWidget(textBrowser, 0, 0, 1, 1);


        verticalLayout->addLayout(about_layout);

        accept_layout = new QHBoxLayout();
        accept_layout->setObjectName(QString::fromUtf8("accept_layout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        accept_layout->addItem(horizontalSpacer);

        accept = new QPushButton(About);
        accept->setObjectName(QString::fromUtf8("accept"));

        accept_layout->addWidget(accept);


        verticalLayout->addLayout(accept_layout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(About);
        QObject::connect(accept, SIGNAL(clicked()), About, SLOT(accept()));

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        textBrowser->setHtml(QApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Painter</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1) <span style=\" text-decoration: underline;\">\320\250\320\265\321\201\321\202\320\270\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272</span> - \320\235\320\260\320\266\320\260\321\202\320\270\320\265\320\274 \320\262 \320\273\321\216\320\261\320\276\320\274 \320\274\320\265\321\201\321\202\320\265 \321\205\320\276\320\273\321\201\321\202\320\260 \320\262\321\213 \320\276"
                        "\320\277\321\200\320\265\320\264\320\265\320\273\321\217\320\265\321\202\320\265 \321\206\320\265\320\275\321\202\321\200, \320\264\320\262\320\270\320\266\320\265\320\275\320\270\320\265\320\274 \320\272\321\203\321\200\321\201\320\276\321\200\320\260 \320\276\320\277\321\200\320\265\320\264\320\265\320\273\321\217\320\265\321\202\321\201\321\217 \321\200\320\260\320\264\320\270\321\203\321\201 \320\270 \321\203\320\263\320\276\320\273 \320\277\320\276\320\262\320\276\321\200\320\276\321\202\320\260 \321\210\320\265\321\201\321\202\320\270\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\260.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2) <span style=\" text-decoration: underline;\">\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265</span> - \320\235\320\260\320\266\320\260\321\202\320\270\320\265\320\274 \320\270 \320\276\321\202\320\277\321\203\321\201\320\272\320\260"
                        "\320\275\320\270\320\265\320\274 \320\272\321\203\321\200\321\201\320\276\321\200\320\260 \320\276\320\277\321\200\320\265\320\264\320\265\320\273\321\217\321\216\321\202\321\201\321\217 \320\264\320\262\320\260 \320\277\321\200\320\276\321\202\320\270\320\262\320\276\320\277\320\276\320\273\320\266\320\275\321\213\321\205 \321\203\320\263\320\273\320\260 \320\277\321\200\321\217\320\274\320\276\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\260, \320\267\320\260\321\202\320\265\320\274 \320\275\320\260\320\266\320\260\321\202\320\270\320\265\320\274 \320\262 \320\273\321\216\320\261\320\276\320\274 \320\274\320\265\321\201\321\202\320\265 \320\262\321\201\321\202\320\260\320\262\320\273\321\217\320\265\321\202\321\201\321\217 \321\200\320\260\320\275\320\265\320\265 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 (\320\276\321\202\320\275\320\276\321\201\320\270\321\202"
                        "\320\265\320\273\321\214\320\275\320\276 \320\273\320\265\320\262\320\276\320\263\320\276 \320\262\320\265\321\200\321\205\320\275\320\265\320\263\320\276 \321\203\320\263\320\273\320\260).</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3) <span style=\" text-decoration: underline;\">\320\241\320\274\320\265\320\275\320\260 \321\206\320\262\320\265\321\202\320\260</span> - \320\235\320\260\320\266\320\260\321\202\320\270\320\265\320\274 \320\270 \320\276\321\202\320\277\321\203\321\201\320\272\320\260\320\275\320\270\320\265\320\274 \320\272\321\203\321\200\321\201\320\276\321\200\320\260 \320\276\320\277\321\200\320\265\320\264\320\265\320\273\321\217\321\216\321\202\321\201\321\217 \320\264\320\262\320\260 \320\277\321\200\320\276\321\202\320\270\320\262\320\276\320\277\320\276\320\273\320\276\320\266\320\275\321\213\321\205 \321\203\320\263\320\273\320\260 \320\277\321\200\321\217\320\274\320\276\321\203\320\263\320\276\320\273"
                        "\321\214\320\275\320\270\320\272\320\260, \320\267\320\260\321\202\320\265\320\274 \320\262\321\201\320\265 \320\277\320\270\320\272\321\201\320\265\320\273\320\270 \320\276\321\201\320\275\320\276\320\262\320\275\320\276\320\263\320\276 \321\206\320\262\320\265\321\202\320\260 \320\267\320\260\320\274\320\265\320\275\321\217\321\216\321\202\321\201\321\217 \320\264\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\274.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4) <span style=\" text-decoration: underline;\">\320\240\320\260\320\274\320\272\320\260</span> - \320\236\320\277\321\206\320\270\321\217 \320\262\321\213\320\262\320\276\320\264\320\270\321\202 \320\275\320\260 \321\215\320\272\321\200\320\260\320\275 \320\276\320\272\320\275\320\276 \320\262\321\213\320\261\320\276\321\200\320\260 \321\200\320\260\320\274\320\272\320\270, \320\263\320\264\320\265 \320\262\320\265\321"
                        "\202\320\262\320\270 -  \320\267\320\260\320\274\320\276\321\211\320\265\320\275\320\270\320\265 \321\203\320\267\320\276\321\200\320\276\320\274 \320\276\321\202 \320\272\320\260\320\266\320\264\320\276\320\263\320\276 \321\203\320\263\320\273\320\260 \320\272 \321\206\320\265\320\275\321\202\321\200\321\203 \321\201\321\202\320\276\321\200\320\276\320\275\321\213; \320\236\320\261\320\276\320\264 - \321\200\320\270\321\201\320\276\320\262\320\260\320\275\320\270\320\265 \320\277\321\200\321\217\320\274\320\276\321\203\320\263\320\276\320\273\321\214\320\275\321\213\321\205 \320\276\320\261\320\276\320\264\320\276\320\262 \320\262\320\276\320\272\321\200\321\203\320\263 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217; \320\232\321\200\320\265\321\201\321\202 - \320\267\320\260\320\274\320\276\321\211\320\265\320\275\320\270\320\265 \320\263\321\200\320\260\320\275\320\270\321\206 \321\203\320\267\320\276\321\200\320\276\320\274 &quot;\320\276\320\272\321\200\321\203\320"
                        "\266\320\275\320\276\321\201\321\202\321\214, \320\275\320\260\320\273\320\276\320\266\320\265\320\275\320\275\320\260\321\217 \320\275\320\260 \320\272\321\200\320\265\321\201\321\202&quot;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">5) <span style=\" text-decoration: underline;\">\320\237\320\265\321\200\320\276</span> - \321\201\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\320\276\320\265 \320\277\320\265\321\200\320\276 \321\201 \320\275\320\260\321\201\321\202\321\200\320\260\320\270\320\262\320\260\320\265\320\274\320\276\320\271 \321\202\320\276\320\273\321\211\320\270\320\275\320\276\320\271 \320\270 \321\206\320\262\320\265\321\202\320\276\320\274</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-b"
                        "lock-indent:0; text-indent:0px;\">\320\224\320\262\321\203\321\205\321\206\320\262\320\265\321\202\320\276\320\262\320\260\321\217 \320\277\320\260\320\273\320\270\321\202\321\200\320\260, \320\263\320\264\320\265 \320\273\320\265\320\262\321\213\320\271 \320\272\320\262\320\260\320\264\321\200\320\260\321\202 - \320\276\321\201\320\275\320\276\320\262\320\275\320\276\320\271 \321\206\320\262\320\265\321\202, \320\277\321\200\320\260\320\262\320\271 - \320\264\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\271. \320\236\321\201\320\275\320\276\320\262\320\275\320\276\320\271 \321\206\320\262\320\265\321\202 \320\276\321\202\320\262\320\265\321\207\320\260\320\265\321\202 \320\267\320\260 <span style=\" font-style:italic;\">\320\272\320\276\320\275\321\202\321\203\321\200</span> \320\262 <span style=\" font-style:italic;\">\321\210\320\265\321\201\321\202\320\270\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\265</span>, \320\267\320\260\320"
                        "\274\320\265\320\275\321\217\320\265\320\274\321\213\320\271 \321\206\320\262\320\265\321\202 \320\262 <span style=\" font-style:italic;\">\321\201\320\274\320\265\320\275\320\265 \321\206\320\262\320\265\321\202\320\260</span>, \321\206\320\262\320\265\321\202 <span style=\" font-style:italic;\">\320\277\320\265\321\200\320\260 </span>\320\270 \321\206\320\262\320\265\321\202 <span style=\" font-style:italic;\">\321\200\320\260\320\274\320\272\320\270</span>. \320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\321\213\320\275\320\271 \321\206\320\262\320\265\321\202 - \320\267\320\260 <span style=\" font-style:italic;\">\321\204\320\276\320\275 \321\210\320\265\321\201\321\202\320\270\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\260</span> \320\270 \320\275\320\276\320\262\321\213\320\271 \321\206\320\262\320\265\321\202 \320\262 <span style=\" font-style:italic;\">\321\201\320\274\320\265\320\275\320\265 \321\206\320\262\320\265\321\202\320\260.</sp"
                        "an></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\227\320\260\320\273\320\270\320\262\320\272\320\260 - \320\276\320\277\321\206\320\270\321\217 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\320\274\320\260\321\217 \320\262 \321\204\321\203\320\275\320\272\321\206\320\270\320\270 \321\200\320\270\321\201\320\276\320\262\320\260\320\275\320\270\321\217 \321\210\320\265\321\201\321\202\320\270\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\260, \320\276\320\277\321\200\320\265\320\264\320\273\321\217\320\265\321\202 \321\202\321\200\320\265\320\261\321\203\320\265\321\202\321\201\321\217 \320\273\320\270 \320\267\320\260\320\273\320\270\321\202\321\214 \320\276\320\277\321\200\320\265\320\264\320\265\320"
                        "\273\320\265\320\275\320\275\321\213\320\274 \321\206\320\262\320\265\321\202\320\276\320\274 \320\277\321\200\320\276\321\201\321\202\321\200\320\260\320\275\321\201\321\202\320\262\320\276 \320\262\320\275\321\203\321\202\321\200\320\270 \320\272\320\276\320\275\321\202\321\203\321\200\320\260.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\242\320\276\320\273\321\211\320\270\320\275\320\260 - \320\276\320\277\321\200\320\265\320\264\320\265\320\273\321\217\320\265\321\202 \321\202\320\276\320\273\321\211\320\270\320\275\321\203 \320\272\320\276\320\275\321\202\321\203\321\200\320\260 \321\210\320\265\321\201\321\202\320\270\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\260 \320\270 \321\202\320\276\320\273\321\211\320\270\320\275\321\203 \320"
                        "\277\320\265\321\200\320\260.</p></body></html>", nullptr));
        accept->setText(QApplication::translate("About", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
