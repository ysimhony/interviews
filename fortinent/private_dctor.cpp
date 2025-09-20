class MyClass {
public:
    MyClass() {
        // Constructor code
    }

    void doSomething() {
        // Some method
    }

private:
    ~MyClass() {
        // Private destructor
    }
};

int main() {
    MyClass obj;  // Okay: constructor is public
    obj.doSomething();

    // Destructor will be called automatically when obj goes out of scope,
    // but since destructor is private, this will cause a compilation error
    // if you try to delete or explicitly destroy an object outside the class.

    // MyClass* p = new MyClass();
    // delete p;  // Error: ~MyClass() is private

    return 0;
}

