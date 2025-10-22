// SmartSharedPtr.hpp
#pragma once
#include <iostream>
#include <cstddef>

template <typename T>
struct ControlBlock
{
    T *ptr;
    std::size_t strong_count;
    std::size_t weak_count;
    ControlBlock(T *p) : ptr(p), strong_count(1), weak_count(0) {}
};

template <typename T>
class SmartWeakPtr; // forward declaration

template <typename T>
class SmartSharedPtr
{
private:
    ControlBlock<T> *control;

    void release()
    {
        if (control)
        {
            if (--control->strong_count == 0)
            {
                delete control->ptr;
                control->ptr = nullptr;
                // If no weak references left, delete control block
                if (control->weak_count == 0)
                    delete control;
            }
            control = nullptr;
        }
    }

public:
    explicit SmartSharedPtr(T *p = nullptr)
        : control(p ? new ControlBlock<T>(p) : nullptr) {}

    ~SmartSharedPtr() { release(); }

    // Copy constructor
    SmartSharedPtr(const SmartSharedPtr &other)
        : control(other.control)
    {
        if (control)
            ++control->strong_count;
    }

    // Copy assignment
    SmartSharedPtr &operator=(const SmartSharedPtr &other)
    {
        if (this != &other)
        {
            release();
            control = other.control;
            if (control)
                ++control->strong_count;
        }
        return *this;
    }

    // Move constructor
    SmartSharedPtr(SmartSharedPtr &&other) noexcept
        : control(other.control)
    {
        other.control = nullptr;
    }

    // Move assignment
    SmartSharedPtr &operator=(SmartSharedPtr &&other) noexcept
    {
        if (this != &other)
        {
            release();
            control = other.control;
            other.control = nullptr;
        }
        return *this;
    }

    T *get() const { return control ? control->ptr : nullptr; }
    T &operator*() const { return *(control->ptr); }
    T *operator->() const { return control->ptr; }

    size_t use_count() const { return control ? control->strong_count : 0; }
    bool unique() const { return use_count() == 1; }

    bool expired() const { return !control || control->strong_count == 0; }

    // Grant SmartWeakPtr access
    friend class SmartWeakPtr<T>;

    // Constructor that promotes from SmartWeakPtr
    SmartSharedPtr(const SmartWeakPtr<T> &weak)
        : control(weak.control)
    {
        if (control && control->strong_count > 0)
            ++control->strong_count;
        else
            control = nullptr;
    }
};