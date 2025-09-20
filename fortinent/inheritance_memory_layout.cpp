#include <iostream>

class Base {
public:
    int a = 1;
    int b = 2;

    void baseMethod() {}
    virtual void virtualBaseMethod() {}
};

class Derived : public Base {
public:
    int c = 3;
    int d = 4;

    void derivedMethod() {}
    virtual void virtualDerivedMethod() {}
};

int main() {
    Derived obj;

    std::cout << "Size of Base:    " << sizeof(Base) << " bytes\n";
    std::cout << "Size of Derived: " << sizeof(Derived) << " bytes\n\n";

    std::cout << "Address of object:        " << &obj << "\n";
    std::cout << "Address of Base subobject:" << static_cast<Base*>(&obj) << "\n\n";

    std::cout << "Address of obj.a: " << &(obj.a) << "\n";
    std::cout << "Address of obj.b: " << &(obj.b) << "\n";
    std::cout << "Address of obj.c: " << &(obj.c) << "\n";
    std::cout << "Address of obj.d: " << &(obj.d) << "\n";

    return 0;
}

