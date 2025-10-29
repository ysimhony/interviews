/*

This example demonstrate that in multiple inheritance the pointer of the 
object is changed according to the parent class pointer.

The reason for that is that is the layout of the object:
+-------------------------+
|  Base1 vptr → Base1 vtbl|
|  Base1 data (none)      |
+-------------------------+
|  Base2 vptr → Base2 vtbl|
|  Base2 data (none)      |
+-------------------------+
|  Derived data (none)    |
+-------------------------+

Thus, having two vtables and two vptr for each parent class.

yacovs@MOE-KT-6565923:~/interviews/fortinent$ g++ -ggdb -o multiple_inherirance2 multiple_inherirance2.cpp
yacovs@MOE-KT-6565923:~/interviews/fortinent$ ./multiple_inherirance2
Calling through Base1*:
Base1::f1() called
Base1::f2() called

Calling through Base2*:
Base2::g1() called
Base2::g2() called

Addresses:
  &d =        0x7fffd42ad000
  (Base1*) &d = 0x7fffd42ad000
  (Base2*) &d = 0x7fffd42ad008

*/

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

