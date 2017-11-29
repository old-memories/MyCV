/********************************************************************************
** Form generated from reading UI file 'MyCV.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCV_H
#define UI_MYCV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyCVClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyCVClass)
    {
        if (MyCVClass->objectName().isEmpty())
            MyCVClass->setObjectName(QStringLiteral("MyCVClass"));
        MyCVClass->resize(600, 400);
        menuBar = new QMenuBar(MyCVClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MyCVClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyCVClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyCVClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyCVClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MyCVClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyCVClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyCVClass->setStatusBar(statusBar);

        retranslateUi(MyCVClass);

        QMetaObject::connectSlotsByName(MyCVClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyCVClass)
    {
        MyCVClass->setWindowTitle(QApplication::translate("MyCVClass", "MyCV", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyCVClass: public Ui_MyCVClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCV_H
