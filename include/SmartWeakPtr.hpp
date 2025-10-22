// SmartWeakPtr.hpp
#pragma once
#include "SmartSharedPtr.hpp"

template <typename T>
class SmartWeakPtr
{
private:
    ControlBlock<T> *control;

public:
    SmartWeakPtr() : control(nullptr) {}

    // Construct from SmartSharedPtr
    SmartWeakPtr(const SmartSharedPtr<T> &shared)
        : control(shared.control)
    {
        if (control)
            ++control->weak_count;
    }

    // Copy constructor
    SmartWeakPtr(const SmartWeakPtr &other)
        : control(other.control)
    {
        if (control)
            ++control->weak_count;
    }

    // Move constructor
    SmartWeakPtr(SmartWeakPtr &&other) noexcept
        : control(other.control)
    {
        other.control = nullptr;
    }

    // Destructor
    ~SmartWeakPtr()
    {
        if (control && --control->weak_count == 0 && control->strong_count == 0)
            delete control;
    }

    // Copy assignment
    SmartWeakPtr &operator=(const SmartWeakPtr &other)
    {
        if (this != &other)
        {
            if (control && --control->weak_count == 0 && control->strong_count == 0)
                delete control;
            control = other.control;
            if (control)
                ++control->weak_count;
        }
        return *this;
    }

    // Move assignment
    SmartWeakPtr &operator=(SmartWeakPtr &&other) noexcept
    {
        if (this != &other)
        {
            if (control && --control->weak_count == 0 && control->strong_count == 0)
                delete control;
            control = other.control;
            other.control = nullptr;
        }
        return *this;
    }

    // Check if resource still exists
    bool expired() const
    {
        return !control || control->strong_count == 0;
    }

    // Try to create a SmartSharedPtr (if object still alive)
    SmartSharedPtr<T> lock() const
    {
        if (expired())
            return SmartSharedPtr<T>(); // return empty shared ptr
        ++control->strong_count;
        return SmartSharedPtr<T>(*this); // construct from weak ptr
    }

    friend class SmartSharedPtr<T>;
};
