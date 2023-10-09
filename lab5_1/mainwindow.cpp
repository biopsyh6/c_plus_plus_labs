
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "myqueue.h"
#include "myqueue.cpp"
#include "sharedptr.h"
#include "sharedptr.cpp"
#include "uniqueptr.h"
#include "uniqueptr.cpp"
#include <QMessageBox>
#include "task.h"
#include <QDialog>
#include <QDialogButtonBox>
#include "dialogfortask.h"
MyQueue<int> queue;
MyQueue<int> secondqueue;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Push_clicked()
{
    queue.push(ui->spinBoxForPush->value());
}



void MainWindow::on_ShowFront_clicked()
{
    if(queue.getSize())
    {
        int fro = queue.front();
        QString sfro = QString::number(fro);
        ui->listWidgetMain->addItem(sfro);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Your queue is clear.");
        return;
    }
}


void MainWindow::on_Pop_clicked()
{
    if(queue.getSize())
    {
        queue.pop();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Your queue is clear.");
        return;
    }
}


void MainWindow::on_ShowBack_clicked()
{
    if(queue.getSize())
    {
        int bac = queue.back();
        QString cbac = QString::number(bac);
        ui->listWidgetMain->addItem(cbac);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Your queue is clear.");
        return;
    }
}



void MainWindow::on_isEmpty_clicked()
{
    int empt = queue.empty();
    QString sempt = QString::number(empt);
    ui->listWidgetMain->addItem(sempt);
}



void MainWindow::on_GetSize_clicked()
{
    int sz = queue.getSize();
    QString ssz = QString::number(sz);
    ui->listWidgetMain->addItem(ssz);
}


void MainWindow::on_Clear_clicked()
{
    if(queue.getSize())
    {
    queue.clear();
    }
    else
    {
    QMessageBox::warning(this, "Error", "Your queue is clear.");
    return;
    }
}



void MainWindow::on_Emplace_clicked()
{
    queue.emplace(new MyQueue<int>::Node(ui->spinBoxForEmplace->value()));
}


void MainWindow::on_Push_2_clicked()
{
    secondqueue.push(ui->spinBoxForPush_2->value());
}


void MainWindow::on_ShowFront_2_clicked()
{
    if(secondqueue.getSize())
    {
    int fro = secondqueue.front();
    QString sfro = QString::number(fro);
    ui->listWidgetMain_2->addItem(sfro);
    }
    else
    {
    QMessageBox::warning(this, "Error", "Your queue is clear.");
    return;
    }
}


void MainWindow::on_ShowBack_2_clicked()
{
    if(secondqueue.getSize())
    {
    int bac = secondqueue.back();
    QString cbac = QString::number(bac);
    ui->listWidgetMain_2->addItem(cbac);
    }
    else
    {
    QMessageBox::warning(this, "Error", "Your queue is clear.");
    return;
    }
}


void MainWindow::on_Pop_2_clicked()
{
    if(secondqueue.getSize())
    {
    secondqueue.pop();
    }
    else
    {
    QMessageBox::warning(this, "Error", "Your queue is clear.");
    return;
    }
}



void MainWindow::on_isEmpty_2_clicked()
{
    int empt = secondqueue.empty();
    QString sempt = QString::number(empt);
    ui->listWidgetMain_2->addItem(sempt);
}


void MainWindow::on_GetSize_2_clicked()
{
    int sz = secondqueue.getSize();
    QString ssz = QString::number(sz);
    ui->listWidgetMain_2->addItem(ssz);
}


void MainWindow::on_Clear_2_clicked()
{
    if(secondqueue.getSize())
    {
    secondqueue.clear();
    }
    else
    {
    QMessageBox::warning(this, "Error", "Your queue is clear.");
    return;
    }
}


void MainWindow::on_Emplace_2_clicked()
{
    secondqueue.emplace(new MyQueue<int>::Node(ui->spinBoxForEmplace_2->value()));
}


void MainWindow::on_Swap_clicked()
{
    queue.swap(secondqueue);
}


void MainWindow::on_Task_clicked()
{
    DialogForTask window;
    window.setModal(true);
    window.exec();
}

