
#ifndef TASK_H
#define TASK_H
#include <random>
#include <ctime>
#include "myqueue.h"
#include <QLineEdit>


class task
{
private:

public:
    task(){}
    void generateRandomNumbers(int n, QLineEdit* a);
    void split(QLineEdit* positive, QLineEdit* negative);
};

#endif // TASK_H
