#include <iostream>
#include <type_traits>

using namespace std;

class A {
    int x;
};




int main() {
    cout << boolalpha;
    cout << "is_default_constructible: " << is_default_constructible<A>::value << endl;
    cout << "is_copy_constructible: " << is_copy_constructible<A>::value << endl;
    cout << "is_copy_assignable: " << is_copy_assignable<A>::value << endl;
    cout << "is_move_constructible: " << is_move_constructible<A>::value << endl;
    cout << "is_move_assignable: " << is_move_assignable<A>::value << endl;
    cout << "is_destructible: " << is_destructible<A>::value << endl;
}

