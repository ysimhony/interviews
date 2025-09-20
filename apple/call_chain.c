#include <stdio.h>

void zoo() {
    printf("Inside zoo()\n");
}

void foo() {
    printf("Inside foo()\n");
    zoo();
}

int main() {
    printf("Inside main()\n");
    foo();
    return 0;
}

