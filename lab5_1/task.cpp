#include <QMessageBox>
#include "task.h"
MyQueue<int> queue_task;
MyQueue<int> negative_queue;
MyQueue<int> positive_queue;
void task::generateRandomNumbers(int n, QLineEdit *a)
{
    a->clear();
    queue_task.clear();
    std::default_random_engine generator(std::time(nullptr));
    std::uniform_int_distribution<int> distribution(-100, 100);
    for(int i = 0; i < n; i++)
    {
        int num = distribution(generator);
        queue_task.push(num);
        a->insert(QString::number(num) + " ");
    }
}
void task::split(QLineEdit* positive, QLineEdit* negative)
{
    positive->clear();
    negative->clear();
    while (!queue_task.empty())
    {
        int num = queue_task.front();
        if(num < 0)
        {
            negative_queue.push(num);
            negative->insert(QString::number(num) + " ");
        }
        else
        {
            positive_queue.push(num);
            positive->insert(QString::number(num) + " ");
        }
        queue_task.pop();
    }
}

