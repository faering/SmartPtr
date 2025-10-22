// SmartUniquePtr.hpp
#pragma once
#include <utility>

template <typename T>
class SmartUniquePtr
{
private:
    T *ptr;

public:
    explicit SmartUniquePtr(T *p = nullptr) : ptr(p) {}
    ~SmartUniquePtr() { delete ptr; }

    // Disable copy
    SmartUniquePtr(const SmartUniquePtr &) = delete;
    SmartUniquePtr &operator=(const SmartUniquePtr &) = delete;

    // Move semantics
    SmartUniquePtr(SmartUniquePtr &&other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    SmartUniquePtr &operator=(SmartUniquePtr &&other) noexcept
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
