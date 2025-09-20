#include <iostream>

using namespace std;
class A
{
public:
    A() {

        cout << "A::A" << endl;
        bla();
    }

    virtual ~A() { cout << "A::~A" << endl; }
   
    virtual void bla() { cout << "A" << endl; }

};

class B : public A
{
public:
    B() {cout << "B::B" << endl; }
    ~B() {cout << "B::~B" << endl; }
    virtual void bla() {cout << "B" << endl; }
};



int main() {

#ifdef CASE1
    A a;
    a.bla();
#endif // CASE1

#ifdef CASE2
    B b;
    b.bla();
#endif // CASE2

#ifdef CASE3
    A *a = new A;
    delete a;
#endif //CASE3

#ifdef CASE4
    A *b = new B;
    delete b;
#endif //CASE4
}
