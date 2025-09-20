#include <stdio.h>

void zoo() {
    int a = 10;                  // local variable
    printf("Inside zoo()\n");
}

void foo() {
    int b = 20;                  // local variable
    printf("Inside foo()\n");
    zoo();
}

int main() {
    int c = 30;                  // local variable
    printf("Inside main()\n");
    foo();
    return 0;
}

