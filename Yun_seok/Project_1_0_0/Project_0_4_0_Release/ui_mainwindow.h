/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *Right_button;
    QPushButton *Left_button;
    QPushButton *Acc_button;
    QPushButton *Break_button;
    QProgressBar *progressBar;
    QPushButton *button_A;
    QPushButton *button_B;
    QLineEdit *lineEdit;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(543, 296);
        MainWindow->setWindowOpacity(0);
#ifndef QT_NO_TOOLTIP
        MainWindow->setToolTip(QStringLiteral(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        MainWindow->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
        MainWindow->setAnimated(true);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Right_button = new QPushButton(centralWidget);
        Right_button->setObjectName(QStringLiteral("Right_button"));
        Right_button->setGeometry(QRect(130, 130, 61, 61));
        Right_button->setAcceptDrops(true);
        Right_button->setIconSize(QSize(64, 64));
        Right_button->setCheckable(false);
        Right_button->setChecked(false);
        Right_button->setAutoRepeat(false);
        Right_button->setAutoExclusive(false);
        Right_button->setAutoDefault(false);
        Right_button->setDefault(false);
        Right_button->setFlat(true);
        Left_button = new QPushButton(centralWidget);
        Left_button->setObjectName(QStringLiteral("Left_button"));
        Left_button->setGeometry(QRect(50, 130, 61, 61));
        Left_button->setAcceptDrops(true);
        Left_button->setIconSize(QSize(64, 64));
        Left_button->setCheckable(false);
        Left_button->setChecked(false);
        Left_button->setAutoRepeat(false);
        Left_button->setAutoExclusive(false);
        Left_button->setAutoDefault(false);
        Left_button->setDefault(false);
        Left_button->setFlat(true);
        Acc_button = new QPushButton(centralWidget);
        Acc_button->setObjectName(QStringLiteral("Acc_button"));
        Acc_button->setGeometry(QRect(90, 90, 61, 61));
        Acc_button->setAcceptDrops(true);
        Acc_button->setIconSize(QSize(64, 64));
        Acc_button->setCheckable(false);
        Acc_button->setChecked(false);
        Acc_button->setAutoRepeat(false);
        Acc_button->setAutoExclusive(false);
        Acc_button->setAutoDefault(false);
        Acc_button->setDefault(false);
        Acc_button->setFlat(true);
        Break_button = new QPushButton(centralWidget);
        Break_button->setObjectName(QStringLiteral("Break_button"));
        Break_button->setGeometry(QRect(90, 170, 61, 61));
        Break_button->setAcceptDrops(true);
        Break_button->setIconSize(QSize(64, 64));
        Break_button->setCheckable(false);
        Break_button->setChecked(false);
        Break_button->setAutoRepeat(false);
        Break_button->setAutoExclusive(false);
        Break_button->setAutoDefault(false);
        Break_button->setDefault(false);
        Break_button->setFlat(true);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(120, 10, 331, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        button_A = new QPushButton(centralWidget);
        button_A->setObjectName(QStringLiteral("button_A"));
        button_A->setGeometry(QRect(320, 150, 99, 27));
        button_B = new QPushButton(centralWidget);
        button_B->setObjectName(QStringLiteral("button_B"));
        button_B->setGeometry(QRect(320, 190, 99, 27));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 50, 113, 27));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(290, 90, 161, 41));
        graphicsView->setAutoFillBackground(false);
        graphicsView->setFrameShape(QFrame::StyledPanel);
        graphicsView->setFrameShadow(QFrame::Sunken);
        QBrush brush(QColor(0, 0, 0, 0));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 543, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Right_button->setText(QString());
        Left_button->setText(QString());
        Acc_button->setText(QString());
        Break_button->setText(QString());
        button_A->setText(QApplication::translate("MainWindow", "A", 0));
        button_B->setText(QApplication::translate("MainWindow", "B", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
