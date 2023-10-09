
#ifndef SHAREDPTR_H
#define SHAREDPTR_H




template <typename T>
class weakptr;
template <typename T>
class sharedptr
{
public:
    void reset();
    void reset(sharedptr<T>& ptrr, T* newPtr);
    sharedptr();
    sharedptr(T* p);
    sharedptr(const sharedptr<T>& other);
    sharedptr(sharedptr<T>&& other);
    sharedptr(const weakptr<T>& x);
    sharedptr&operator=(weakptr<T>& x);
    ~sharedptr();
    sharedptr<T>&operator=(const sharedptr <T>&other);
    sharedptr<T>&operator=(sharedptr<T>&& other);
    T* operator->() const;
    T& operator*() const;
    operator bool() const;
    bool expired() const;
    T* get() const;
    friend class weakptr<T>;
    T*ptr;
    int* counter;
private:
    //    T*ptr;
    //    int* counter;
};
template <typename T>
class sharedptr;
template <typename T>
class weakptr
{
public:
    void reset();
    void reset(weakptr<T>& ptrr, sharedptr<T>& newPtr);
    weakptr();
    weakptr(const sharedptr<T>& ptr);
    weakptr& operator=(sharedptr<T>& x);
    weakptr(const weakptr& other);
    weakptr(weakptr&& other) noexcept;
    ~weakptr();
    weakptr& operator=(const weakptr& other);
    weakptr& operator=(weakptr&& other) noexcept;
    bool expired() const;
    sharedptr<T> lock() const;
    bool equals(weakptr ptr_);

    friend  class sharedptr<T>;
    T* ptr;
    int* counter;
private:
    //    T* ptr;
    //    int* counter;
};

#endif // SHAREDPTR_H
