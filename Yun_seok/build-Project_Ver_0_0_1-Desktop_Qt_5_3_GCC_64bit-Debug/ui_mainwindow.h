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
    QPushButton *right_button;
    QPushButton *Left_button;
    QPushButton *Acc_button;
    QPushButton *break_button;
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
        MainWindow->resize(604, 300);
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
        right_button = new QPushButton(centralWidget);
        right_button->setObjectName(QStringLiteral("right_button"));
        right_button->setGeometry(QRect(300, 120, 61, 61));
        right_button->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QStringLiteral("../button/next (2).png"), QSize(), QIcon::Normal, QIcon::Off);
        right_button->setIcon(icon);
        right_button->setIconSize(QSize(64, 64));
        right_button->setCheckable(false);
        right_button->setChecked(false);
        right_button->setAutoRepeat(false);
        right_button->setAutoExclusive(false);
        right_button->setAutoDefault(false);
        right_button->setDefault(false);
        right_button->setFlat(true);
        Left_button = new QPushButton(centralWidget);
        Left_button->setObjectName(QStringLiteral("Left_button"));
        Left_button->setGeometry(QRect(220, 120, 61, 61));
        Left_button->setAcceptDrops(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral("../button/next (6).png"), QSize(), QIcon::Normal, QIcon::Off);
        Left_button->setIcon(icon1);
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
        Acc_button->setGeometry(QRect(260, 80, 61, 61));
        Acc_button->setAcceptDrops(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral("../button/next (3).png"), QSize(), QIcon::Normal, QIcon::Off);
        Acc_button->setIcon(icon2);
        Acc_button->setIconSize(QSize(64, 64));
        Acc_button->setCheckable(false);
        Acc_button->setChecked(false);
        Acc_button->setAutoRepeat(false);
        Acc_button->setAutoExclusive(false);
        Acc_button->setAutoDefault(false);
        Acc_button->setDefault(false);
        Acc_button->setFlat(true);
        break_button = new QPushButton(centralWidget);
        break_button->setObjectName(QStringLiteral("break_button"));
        break_button->setGeometry(QRect(260, 160, 61, 61));
        break_button->setAcceptDrops(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral("../button/next (4).png"), QSize(), QIcon::Normal, QIcon::Off);
        break_button->setIcon(icon3);
        break_button->setIconSize(QSize(64, 64));
        break_button->setCheckable(false);
        break_button->setChecked(false);
        break_button->setAutoRepeat(false);
        break_button->setAutoExclusive(false);
        break_button->setAutoDefault(false);
        break_button->setDefault(false);
        break_button->setFlat(true);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(30, 10, 551, 23));
        progressBar->setValue(0);
        button_A = new QPushButton(centralWidget);
        button_A->setObjectName(QStringLiteral("button_A"));
        button_A->setGeometry(QRect(460, 140, 99, 27));
        button_B = new QPushButton(centralWidget);
        button_B->setObjectName(QStringLiteral("button_B"));
        button_B->setGeometry(QRect(460, 180, 99, 27));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(230, 40, 113, 27));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(420, 80, 161, 41));
        graphicsView->setAutoFillBackground(false);
        graphicsView->setFrameShape(QFrame::StyledPanel);
        graphicsView->setFrameShadow(QFrame::Sunken);
        QBrush brush(QColor(0, 0, 0, 0));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 604, 25));
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
        right_button->setText(QString());
        Left_button->setText(QString());
        Acc_button->setText(QString());
        break_button->setText(QString());
        button_A->setText(QApplication::translate("MainWindow", "A", 0));
        button_B->setText(QApplication::translate("MainWindow", "B", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
