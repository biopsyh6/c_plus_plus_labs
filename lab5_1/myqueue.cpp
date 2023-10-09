
#include "myqueue.h"
#include <iostream>
template <typename T>
MyQueue<T>::Node::Node(const T& data) : data(data), next(nullptr), prev(nullptr){}
template <typename T>
MyQueue<T>::~MyQueue<T>()
{
    clear();
}
template <typename T>
MyQueue<T>::MyQueue() : head(nullptr), tail(nullptr), size(0) {}
template <typename T>
void MyQueue<T>::push(const T& data)
{
    sharedptr<Node> new_node(new Node(data));
    if(empty())
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        if(tail.lock()) //существует ли объект, на который ссылается tail
        {
            tail.lock()->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }
    size++;
}
template <typename T>
void MyQueue<T>::pop()
{
    if(!empty())
    {
        sharedptr<Node> old_head = head; // сохраняем указатель на текущую голову, чтобы можно было удалить узел, на который указывала голова, после того, как голова будет обновлена.
        head = head->next;
        if(head)
        {
            head->prev.reset();
        }
        else
        {
            tail.reset();
        }
        size--;
        old_head.reset(); // удаляем умный указатель на старую голову, что приводит к удалению старой головы
    }
}
template <typename T>
T& MyQueue<T>::front()
{
    return head->data;
}
template <typename T>
T& MyQueue<T>::back()
{
    return tail.lock()->data;
}
template <typename T>
bool MyQueue<T>::empty() const
{
    return size == 0;
}
template <typename T>
size_t MyQueue<T>::getSize() const
{
    return size;
}
template <typename T>
void MyQueue<T>::clear()
{
    head = nullptr;
    tail.reset();
    size = 0;
}
template <typename T>
MyQueue<T> MyQueue<T>::operator=(const MyQueue<T>& other)
{
    if(this != other)
    {
        clear();
        // Копируем содержимое очереди other
        sharedptr<Node> current = other.head;
        while(current!=nullptr)
        {
            push(current->data);
            current = current ->next;
        }
    }
    return *this;
}
template <typename T>
template <typename... Args>
void MyQueue<T>::emplace(Args&&... args) //переменное число аргументов
{
    // Создаем новый узел, используя переданные аргументы
    sharedptr<Node> newNode (std::forward<Args>(args)...); //... - кол-во аргументов не ограничено
        // Если очередь пуста, новый узел становится головой и хвостом
    if(empty())
    {
        head = newNode;
        tail = head;
    }
    // Иначе добавляем новый узел в конец очереди
    else
    {
        tail.lock()->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}
template <typename T>
void MyQueue<T>::swap(MyQueue<T>& other) noexcept
{
    sharedptr<Node> temp_head = head;
    head = other.head;
    other.head = temp_head;

    weakptr<Node> temp_tail = tail;
    tail = other.tail;
    other.tail = temp_tail;

    size_t temp_size = size;
    size = other.size;
    other.size = temp_size;
}
template <typename T>
bool MyQueue<T>::operator==(const MyQueue<T>& other) const
{
    if(size != other.size)
    {
        return false;
    }
    sharedptr<Node> current = head;
    sharedptr<Node> otherCurrent = other.head;
    while (current!= nullptr && otherCurrent != nullptr)
    {
        if(current->data != otherCurrent->data)
        {
            return false;
        }
        current = current->next;
        otherCurrent = otherCurrent->next;
    }
    return true;
}
template <typename T>
bool MyQueue<T>::operator!=(const MyQueue<T>&other) const
{
    return !(*this == other);
}
template <typename T>
bool MyQueue<T>::operator<(const MyQueue<T>& other) const
{
    if(size < other.size)
    {
        return true;
    } else if(size == other.size)
    {
        auto this_node = head;
        auto other_node = other.head;
        while(this_node && other_node)
        {
            if(this_node->data < other_node->data)
            {
                return true;
            }else if(other_node->data < this_node->data)
            {
                return false;
            }
            this_node = this_node->next;
            other_node = other_node->next;
        }
    }
    return false;
}
template <typename T>
bool MyQueue<T>::operator<=(const MyQueue<T>&other) const
{
    return (*this < other) || (*this == other);
}
template <typename T>
bool MyQueue<T>::operator>(const MyQueue<T>&other) const
{
    return !(this->operator<(other)) && !(this->operator==(other));
}
template <typename T>
bool MyQueue<T>::operator>=(const MyQueue<T>&other) const
{
    return (*this > other) || (*this == other);
}


