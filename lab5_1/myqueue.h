
#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "sharedptr.h"
#include "uniqueptr.h"
#include <stddef.h>


template <typename T>
class MyQueue
{
private:

public:
    struct Node
    {
        T data;
        sharedptr <Node> next;
        weakptr<Node> prev;
        Node(const T& data);
    };
    sharedptr<Node> head;
    weakptr<Node> tail;
    size_t size;
    MyQueue();
    ~MyQueue();
    MyQueue operator=(const MyQueue<T>& other);
    void push(const T& data);
    void pop();
    T& front();
    T& back();
    bool empty() const;
    size_t getSize() const;
    void clear();
    template<typename...Args>
    void emplace(Args&&... args);
    void swap(MyQueue<T>&other) noexcept;
    bool operator==(const MyQueue<T>&other) const;
    bool operator!=(const MyQueue<T>& other) const;
    bool operator<(const MyQueue<T>& other) const;
    bool operator <=(const MyQueue<T>&other) const;
    bool operator >(const MyQueue<T>&other) const;
    bool operator >=(const MyQueue<T>&other) const;
};

#endif // MYQUEUE_H
