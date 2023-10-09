
#include "sharedptr.h"

template <typename T>
sharedptr<T>::sharedptr(): ptr(nullptr), counter(nullptr){} //конструктор по умолчанию, который создает shared_ptr с пустым указателем и счетчиком = 0
template <typename T>
sharedptr<T>::sharedptr(T *p) : ptr(p), counter(p ? new int(1) : nullptr)
{
    //    if(!p)
    //    {
    //        throw std::invalid_argument("Invalid pointer");
    //    }
} //конструктор, который принимает указатель на объект типа T и создает shared_ptr с этим указателем
template <typename T>
sharedptr<T>::sharedptr(const sharedptr<T> &other) : ptr(other.ptr), counter(other.counter) //конструктор копирования, который создает копию shared_ptr из другого shared_ptr
{
    if(counter)
        ++(*counter);
    else
        ptr = nullptr;
}
template <typename T>
sharedptr<T>::sharedptr(sharedptr<T> &&other) : ptr(other.ptr), counter(other.counter) //конструктор перемещения, который создает новый shared_ptr из временного объекта other
{
    other.ptr = nullptr;
    other.counter = nullptr;
}
template <typename T>
sharedptr<T>::~sharedptr() //деструктор
{
    if(ptr != nullptr && counter && --(*counter) == 0) //уменьшаем счетчик. Если  = 0, то объект T удаляется
    {
        delete ptr;
        delete counter;
    }
}
template <typename T>
sharedptr<T> &sharedptr<T>::operator=(const sharedptr<T> &other) //оператор присваивания копирования, который копирует указатель и счетчик из other в текущий объект shared_ptr
{
    if(this != &other) //если текущий объект уже указывает на другой объект
    {
        if(ptr != nullptr && counter && --(*counter) == 0) //то счетчик уменьшаем и проверяем на = 0
        {
            delete ptr;
            delete counter;
        }
        ptr = other.ptr;
        counter = other.counter;
        if(counter) ++(*counter);
        else
            ptr = nullptr;
    }
    return *this;
}
template <typename T>
sharedptr<T> &sharedptr<T>::operator=(sharedptr<T> &&other) //оператор присваивания перемещения, который перемещает указатель и счетчик из временного объекта other в текущий shared_ptr
{
    if(this != &other)
    {
        if(ptr != nullptr && counter && --(*counter) == 0)
        {
            delete ptr;
            delete counter;
        }
        ptr = other.ptr;
        counter = other.counter;
        other.ptr = nullptr;
        other.counter = nullptr;
    }
    return *this;
}
template <typename T>
T* sharedptr<T>::operator->() const //оператор доступа к члену, который возвращает указатель на объект T
{
    return ptr;
}
template <typename T>
T& sharedptr<T>::operator*() const //оператор разыменования, который возвращает ссылку на объект T
{
    return *ptr;
}
template <typename T>
sharedptr<T>::operator bool() const
{
    return ptr != nullptr;
}


template <typename T>
weakptr<T>::weakptr() : ptr(nullptr), counter(nullptr){} //конструктор для создания пустой ссылки
template <typename T>
weakptr<T>::weakptr(const sharedptr<T> &ptr_) : ptr(ptr_.ptr), counter(ptr_.counter)
{
    //    if(!ptr)
    //    {
    //        throw std::invalid_argument("Invalid pointer");
    //    }
} //конструктор для создания объекта слабой ссылки из объекта sharedptr
template <typename T>
weakptr<T>::weakptr(const weakptr<T> &other) : ptr(other.ptr), counter(other.counter) //конструктор копирования
{
    if(counter)
        ++(*counter);
}
template <typename T>
weakptr<T>::weakptr(weakptr<T> &&other) noexcept : ptr(other.ptr), counter(other.counter) //конструктор перемещения
{
    other.ptr = nullptr;
    other.counter = nullptr;
}
template <typename T>
weakptr<T>::~weakptr() //деструктор
{
    if(counter && --(*counter) == 0)
    {
        delete counter;
    }
}
template <typename T>
weakptr<T> &weakptr<T>::operator=(const weakptr<T> &other) //оператор копирующего присваивания
{
    if(this != &other)
    {
        if(counter && --(*counter) == 0)
        {
            delete counter;
        }
        ptr = other.ptr;
        counter = other.counter;
        if(counter)
            ++(*counter);
    }
    return *this;
}
template <typename T>
weakptr<T> &weakptr<T>::operator=(weakptr<T> &&other) noexcept //конструктор перемещ присваивания
{
    if(this != &other)
    {
        if(counter && --(*counter) == 0)
        {
            delete counter;
        }
        ptr = other.ptr;
        counter = other.counter;
        other.ptr = nullptr;
        other.counter = nullptr;
    }
    return *this;
}
template <typename T>
bool weakptr<T>::expired() const //проверяет, действительна ли слабая ссылка
{
    return !counter || *counter == 0; //имеется ли счетчик и равен ли он нулю
}
template <typename T>
sharedptr<T> weakptr<T>::lock() const
{
    return expired() ? sharedptr<T>() : sharedptr<T>(*this); //возвращает объект sharedptr, если слабая ссылка действительна или пустой sharedptr в противном случае
}
template <typename T>
bool weakptr<T>::equals(weakptr<T> ptr_) //сравнивает две слабые ссылки, указывают ли они на один и тот же объект
{
    return ptr == ptr_.ptr;
}
template <typename T>
sharedptr<T>::sharedptr(const weakptr<T> &x) //конструктор копирования, принимающий в кач аргумента своего друга
{
    ptr = x.ptr;
    counter = x.counter;
    if(counter && *counter > 0)
    {
        ++(*counter);
    }
}
template <typename T>
sharedptr<T> &sharedptr<T>::operator=(weakptr<T> &x) //оператор присваивания копирования, принимающий в кач аргумента своего друга
{
    ptr = x.ptr;
    counter = x.counter;
    if(counter && *counter > 0)
    {
        (*counter)++;
    }
    return *this;
}
template <typename T>
bool sharedptr<T>::expired() const
{
    return counter == nullptr || *counter == 0;
}
template <typename T>
weakptr<T>& weakptr<T>::operator=(sharedptr<T> &x) //оператор присваивания копирования, принимающий в кач аргумента своего друга
{
    ptr = x.ptr;
    counter = x.counter;
    return *this;
}
template <typename T>
void sharedptr<T>::reset(sharedptr<T> &ptrr, T *newPtr)
{
    reset();
    if(newPtr)
    {
        ptr = newPtr;
        counter = ptrr.counter;
        (*counter)++;
    }
}
template <typename T>
void weakptr<T>::reset(weakptr<T> &ptrr, sharedptr<T> &newPtr) //weakptr может ссылаться только на sharedptr
{
    reset();
    if(!newPtr.expired())
    {
        ptr = newPtr.ptr;
        counter = newPtr.counter;
    }
}
template<typename T>
void sharedptr<T>::reset()
{
    if(ptr)
    {
        (*counter)--;
        if(*counter == 0)
        {
            delete ptr;
            delete counter;
        }
        ptr = nullptr;
        counter = nullptr;
    }
}
template <typename T>
void weakptr<T>::reset()
{
    ptr = nullptr;
    counter = nullptr;
}
template <typename T>
T* sharedptr<T>::get() const
{
    return ptr;
}


