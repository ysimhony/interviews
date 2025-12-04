#include <stddef.h>
#include <stdio.h>

int atoi(char *s) {

    if (s==NULL) return 0;

    int result; //chatGpt: you did not initialize to 0
    int sign = 2; //chatGpt: would be better to have 0 as not set
    char *p = s;
    
    while (*p != '\0') {
        if (*p <= '9' && *p >= '0') {
            int tmp = *p - '0';
            result = result*10 + tmp;
            if (sign == 2) sign = 1;
        }
        else {
            if (sign!=2) {
                break;
            } 
            else {
                if (*p=='+') sign = 1;
                else if (*p=='-') sign = -1;
                else if (*p != ' ') break;
            }
        }

        p++;
    }

    return result*sign; 
    
}

int main(){
    
    char *s = " + 123";
    int res = atoi(s);
    printf("string is: '%s', int is: '%d'\n", s, res);
    return 0;
}
