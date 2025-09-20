#include <iostream>

class Base1 {
public:
    int x;  // add a member variable
    void printThis() {
        std::cout << "Base1::this = " << this << std::endl;
    }
};

class Base2 {
public:
    int y;  // add a member variable
    void printThis() {
        std::cout << "Base2::this = " << this << std::endl;
    }
};

class Derived : public Base1, public Base2 {
public:
    void printThis() {
        std::cout << "Derived::this = " << this << std::endl;
    }
};

int main() {
    Derived d;

    d.printThis();

    Base1* b1 = &d;
    Base2* b2 = &d;

    b1->printThis();
    b2->printThis();

    std::cout << "Address of Derived object: " << &d << std::endl;
    std::cout << "Base1 pointer points to: " << b1 << std::endl;
    std::cout << "Base2 pointer points to: " << b2 << std::endl;

    return 0;
}

