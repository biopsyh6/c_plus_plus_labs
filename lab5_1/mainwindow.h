
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Push_clicked();

    void on_ShowFront_clicked();

    void on_Pop_clicked();

    void on_ShowBack_clicked();

    void on_isEmpty_clicked();

    void on_GetSize_clicked();

    void on_Clear_clicked();

    void on_Emplace_clicked();

    void on_Push_2_clicked();

    void on_ShowFront_2_clicked();

    void on_ShowBack_2_clicked();

    void on_Pop_2_clicked();

    void on_isEmpty_2_clicked();

    void on_GetSize_2_clicked();

    void on_Clear_2_clicked();

    void on_Emplace_2_clicked();

    void on_Swap_clicked();

    void on_Task_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
