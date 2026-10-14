#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>

template <typename T>
class Stack
{
    public:
    void push(const T& value);
    T& pop();
    bool empty() const;
    T& top() const;
    size_t size() const;

    Stack();
    ~Stack();

    private:
    T* data;
    size_t capacity_;
    size_t count_;
};

template <typename T>
Stack<T>::Stack()
{
    capacity_ = 10;
    count_ = 0;
    data = new T[capacity_];
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] data;
}

template <typename T>
void Stack<T>::push(const T& value)
{
    if (count_ == capacity_)
    {
        size_t newCapacity = capacity_ * 2;
        T* newData = new T[newCapacity];

        for (size_t i = 0; i < count_; i++)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity_ = newCapacity;
    }

    data[count_] = value;
    count_++;
}

template <typename T>
T& Stack<T>::pop()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }

    return data[--count_];
}

template <typename T>
bool Stack<T>::empty() const
{
    return count_ == 0;
}

template <typename T>
T& Stack<T>::top() const
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }

    return data[count_ - 1];
}

template <typename T>
size_t Stack<T>::size() const
{
    return count_;
}

#endif
