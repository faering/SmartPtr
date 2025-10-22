#include "uniquePtr.hpp"
#include <iostream>

int main()
{
    uniquePtr<int> p1(new int(42));
    std::cout << *p1 << "\n";

    uniquePtr<int> p2 = std::move(p1); // transfer ownership
    if (!p1.get())
        std::cout << "p1 is now null\n";
    std::cout << *p2 << "\n";
}