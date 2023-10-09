
#include "uniqueptr.h"
#include <iostream>
template <typename T>
uniqueptr<T>::uniqueptr() : m_ptr(nullptr) {} //конструктор по умолчанию
template <typename T>
uniqueptr<T>::uniqueptr(T *ptr) : m_ptr(ptr){} //конструктор, который создает умный указатель, указывающий на объект типа Т
template <typename T>
uniqueptr<T>::~uniqueptr() //деструктор
{
    delete m_ptr;
}
template <typename T>
uniqueptr<T>::uniqueptr(uniqueptr<T> &&other) : m_ptr(other.m_ptr) //конструктор перемещения - перемещает владение объектом на др указатель
{
    other.m_ptr = nullptr;
}
template <typename T>
uniqueptr<T> &uniqueptr<T>::operator=(uniqueptr<T> &&other) //оператор перемещения - перемещает владение объектом на другой указатель
{
    if(this != &other)
    {
        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }
    return *this;
}
template <typename T>
T& uniqueptr<T>::operator*() const
{
    return *m_ptr;
}
template <typename T>
T* uniqueptr<T>::operator->() const
{
    return m_ptr;
}
template <typename T>
T* uniqueptr<T>::get() const
{
    return m_ptr;
}
template <typename T>
uniqueptr<T>::operator bool() const
{
    return m_ptr != nullptr;
}
template <typename T>
bool uniqueptr<T>::inNull() const
{
    return m_ptr == nullptr;
}
template <typename T>
T& uniqueptr<T>::operator[](int index) const
{
    return m_ptr[index];
}
template <typename T>
uniqueptr<T> &uniqueptr<T>::operator++()
{
    ++m_ptr;
    return *this;
}
template <typename T>
uniqueptr<T> uniqueptr<T>::operator++(int)
{
    uniqueptr old(std::move(*this));
    ++m_ptr;
    return old;
}
template<typename T>
void uniqueptr<T>::reset()
{
    if(m_ptr != nullptr)
    {
        delete m_ptr;
    }
    m_ptr = nullptr;
}
template <typename T>
void uniqueptr<T>::reset(char *ptr)
{
    if(m_ptr != nullptr)
    {
        delete[]m_ptr;
    }
    m_ptr = ptr;
}
template <typename T>
char* uniqueptr<T>::release()
{
    char* ptr = m_ptr;
    m_ptr = nullptr;
    return ptr;
}


