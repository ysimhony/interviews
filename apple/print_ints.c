#include <stdarg.h>
#include <stdio.h>

void print_ints(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);
        printf("%d\n", value);
    }

    va_end(args);
}

int main() {
    print_ints(3, 10, 20, 30);
    return 0;
}

