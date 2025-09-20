#include <iostream>

class Base1 {
public:
    virtual void f1() {
        std::cout << "Base1::f1() called\n";
    }
    virtual void f2() {
        std::cout << "Base1::f2() called\n";
    }
};

class Base2 {
public:
    virtual void g1() {
        std::cout << "Base2::g1() called\n";
    }
    virtual void g2() {
        std::cout << "Base2::g2() called\n";
    }
};

class Derived : public Base1, public Base2 {
    // No override — we use base class virtual functions directly.
};

int main() {
    Derived d;

    std::cout << "Calling through Base1*:\n";
    Base1* b1 = &d;
    b1->f1();  // should call Base1::f1
    b1->f2();  // should call Base1::f2

    std::cout << "\nCalling through Base2*:\n";
    Base2* b2 = &d;
    b2->g1();  // should call Base2::g1
    b2->g2();  // should call Base2::g2

    std::cout << "\nAddresses:\n";
    std::cout << "  &d =        " << &d << '\n';
    std::cout << "  (Base1*) &d = " << static_cast<Base1*>(&d) << '\n';
    std::cout << "  (Base2*) &d = " << static_cast<Base2*>(&d) << '\n';

    return 0;
}

