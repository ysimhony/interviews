#include <iostream>

class MyClass {
public:
    MyClass() {
        std::cout << "Constructor called.\n";
    }

    void doSomething() {
        std::cout << "Doing something...\n";
    }

    // Static function to safely delete a MyClass object
    static void destroy(MyClass* obj) {
        delete obj;  // Allowed because `destroy` is a member of the class
    }

private:
    ~MyClass() {
        std::cout << "Destructor called.\n";
    }
};

int main() {
    // Create on heap
    MyClass* obj = new MyClass();
    obj->doSomething();

    // Can't call delete obj; directly because destructor is private
    // But we can call the static destroy function
    MyClass::destroy(obj);

    return 0;
}

