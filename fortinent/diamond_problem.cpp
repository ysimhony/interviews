#include <iostream>

class A {
public:
    int x = 10;
};

class B : public A {};
class C : public A {};

class D : public B, public C {
    // D has two A's: one via B, one via C
};

int main() {
    D d;

    // ERROR: ambiguous - which 'x' should be accessed?
    std::cout << d.x << std::endl;

    // OK: disambiguate manually
    std::cout << "B's A::x: " << d.B::x << std::endl;
    std::cout << "C's A::x: " << d.C::x << std::endl;

    return 0;
}

