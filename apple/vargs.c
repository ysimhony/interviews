#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...) {
    va_list args;
    va_start(args, count);
	
    int tmp;
    int total = 0;
    for (int i = 0; i < count; i++) {
        tmp = va_arg(args, int); // get next argument as int
	printf("i: %d arg: %d\n", i, tmp);
        total += tmp;
    }

    va_end(args);
    return total;
}

int main(void) {
    int result = sum(3, 10, 20, 30);  // returns 60
}
