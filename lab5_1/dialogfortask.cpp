#include "dialogfortask.h"
#include "ui_dialogfortask.h"
#include <QDialog>
#include "myqueue.h"
#include "task.h"
#include <QMessageBox>
DialogForTask::DialogForTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogForTask)
{
    ui->setupUi(this);
}

DialogForTask::~DialogForTask()
{
    delete ui;
}

void DialogForTask::on_Generate_clicked()
{
    task obj;
    obj.generateRandomNumbers(ui->spinBoxForGenerate->value(), ui->lineEditForNumbers);
}


void DialogForTask::on_SplitElem_clicked()
{
    task obj2;
    obj2.split(ui->lineEditForPositive, ui->lineEditForNegative);
}

