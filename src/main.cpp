#include "../include/SmartUniquePtr.hpp"
#include "../include/SmartSharedPtr.hpp"
#include "../include/SmartWeakPtr.hpp"
#include <iostream>

using namespace std;

int main()
{
    // SmartUniquePtr usage
    cout << "SmartUniquePtr Demo:" << endl;
    SmartUniquePtr<int> p11{new int(23)};
    cout << "p11 is: " << *p11 << endl;

    SmartUniquePtr<int> p12 = move(p11); // transfer ownership
    if (!p11.get())
        cout << "p11 is now null\n";
    cout << "p12 is: " << *p12 << endl;

    // SmartSharedPtr usage
    cout << "\n\nSmartSharedPtr Demo:" << endl;
    SmartSharedPtr<int> p21{new int(23)};
    cout << "p21 is: " << *p21 << "\n";
    {
        SmartSharedPtr<int> p22 = p21;
        cout << "use_count: " << p21.use_count() << "\n";
    }
    cout << "use_count after scope: " << p21.use_count() << "\n";

    // SmartWeakPtr usage
    cout << "\n\nSmartWeakPtr Demo:" << endl;
    SmartSharedPtr<int> shared1(new int(42));
    SmartWeakPtr<int> weak1(shared1);

    cout << "Initial use_count: " << shared1.use_count() << "\n";

    {
        auto shared2 = weak1.lock();
        if (shared2.get())
            cout << "Locked value: " << *shared2 << "\n";
        cout << "use_count after lock: " << shared1.use_count() << "\n";
    }

    shared1 = SmartSharedPtr<int>(); // destroy managed object

    if (weak1.expired())
        cout << "The object has expired.\n";

    auto shared3 = weak1.lock();
    if (!shared3.get())
        cout << "Lock failed because object no longer exists.\n";
}