#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(bool checked);

    void on_pushButton_5_clicked();

    void on_button_A_clicked();

    void on_Acc_button_clicked();

    void on_break_button_clicked();

    void on_pushButton_6_clicked();

    void on_button_B_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
