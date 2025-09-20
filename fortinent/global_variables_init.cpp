#include <iostream>
#include <string>

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructor\n";
    }
    ~MyClass() {
        std::cout << "MyClass destructor\n";
    }
};

MyClass globalObj;  // Global variable — constructor will run before main()

int main() {
    std::cout << "In main()\n";
    return 0;
}

