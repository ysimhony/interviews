// file: main.cpp
#include <iostream>

class Base {
public:
    virtual void foo() { std::cout << "Base::foo\n"; }
    virtual void bar() { std::cout << "Base::bar\n"; }
};

class Derived : public Base {
public:
    void foo() override { std::cout << "Derived::foo\n"; }
    void bar() override { std::cout << "Derived::bar\n"; }
};

int main() {
    Base* obj1 = new Base();
    Derived * obj2 = new Derived();
    obj1->foo();
    obj2->bar();
    return 0;
}

