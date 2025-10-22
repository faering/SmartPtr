// uniquePtr.hpp
#pragma once
#include <utility>

template <typename T>
class uniquePtr
{
private:
    T *ptr;

public:
    explicit uniquePtr(T *p = nullptr) : ptr(p) {}
    ~uniquePtr() { delete ptr; }

    // Disable copy
    uniquePtr(const uniquePtr &) = delete;
    uniquePtr &operator=(const uniquePtr &) = delete;

    // Move semantics
    uniquePtr(uniquePtr &&other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    uniquePtr &operator=(uniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Access
    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }
    T *get() const { return ptr; }

    void reset(T *p = nullptr)
    {
        delete ptr;
        ptr = p;
    }

    T *release()
    {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }
};
