#include <iostream>

class A {
public:
    int a = 1;
    virtual void foo() { std::cout << "A::foo\n"; }
};

class B : public A {
public:
    int b = 2;
    void foo() override { std::cout << "B::foo\n"; }
};

class C : public A {
public:
    int c = 3;
    void foo() override { std::cout << "C::foo\n"; }
};

class D : public B, public C {
public:
    int d = 4;
    void foo() override { std::cout << "D::foo\n"; }
};

int main() {
    D d;

    //A* aPtr = &d;       // ❌ ERROR: ambiguous conversion!
    A* aPtr1 = static_cast<B*>(&d);  // ✅ Valid: goes through B → A
    A* aPtr2 = static_cast<C*>(&d);  // ✅ Valid: goes through C → A

    aPtr1->foo();  // Will call D::foo via B::A path
    aPtr2->foo();  // Will call D::foo via C::A path
}

