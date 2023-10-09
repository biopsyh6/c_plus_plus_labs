
#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H




template <typename T>
class uniqueptr
{
public:
    uniqueptr();
    uniqueptr(T* ptr);
    ~uniqueptr();
    uniqueptr(const uniqueptr&) = delete;
    uniqueptr& operator=(const uniqueptr&) = delete;
    uniqueptr(uniqueptr&& other);
    uniqueptr& operator=(uniqueptr&& other);
    T& operator*() const;
    T* operator->() const;
    T* get() const;
    T& operator[](int index) const;
    operator bool() const;
    bool inNull() const;
    uniqueptr& operator++(); //префиксный
    uniqueptr operator++(int); //постфиксный
    void reset();
    void reset(char* ptr);
    char* release();

private:
    T* m_ptr;
};

#endif // UNIQUEPTR_H
