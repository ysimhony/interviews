/*
This example show the memory layout of cpp object.
which is:
+--------------------+
| vptr (8 bytes)     |
+--------------------+
| other members...   |
+--------------------+

in our case:
+--------------------+
| vptr (8 bytes)     |
+--------------------+
| a (4 bytes)        |
| b (4 bytes)        |
| c (4 bytes)        |
| d (4 bytes)        |
+--------------------+

so the total size of the Derived class is 24 bytes as seen below.

yacovs@MOE-KT-6565923:~/projects/interviews/fortinent$ ./inheritance_memory_layout
Size of Base:    16 bytes
Size of Derived: 24 bytes

Address of object:        0x7ffcb1727160
Address of Base subobject:0x7ffcb1727160

Address of obj.a: 0x7ffcb1727168
Address of obj.b: 0x7ffcb172716c
Address of obj.c: 0x7ffcb1727170
Address of obj.d: 0x7ffcb1727174

*/

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

