#ifndef DIALOGFORTASK_H
#define DIALOGFORTASK_H

#include <QDialog>

namespace Ui {
class DialogForTask;
}

class DialogForTask : public QDialog
{
    Q_OBJECT

public:
    explicit DialogForTask(QWidget *parent = nullptr);
    ~DialogForTask();

private slots:
    void on_Generate_clicked();

    void on_SplitElem_clicked();

private:
    Ui::DialogForTask *ui;
};

#endif // DIALOGFORTASK_H
