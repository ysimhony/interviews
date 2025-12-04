#include <stddef.h>
#include <stdio.h>

int atoi(char *s) {

    if (s==NULL) return 0;

    char *p = s;
    int sign = 1;
    int num = 0;

    // skip space
    while (*p == ' ') {        
        p++;
    }    

    // read sign if any
    if (*p == '+') {
        sign = 1;
        p++;
    }
    else if (*p == '-') {
        sign = -1;
        p++;
    }
   
    // read digits
    while (*p <= '9' && *p >= '0') {
        num = 10*num+(*p-'0');
        p++;
    }

    return num*sign; 
    
}

int main(){
    
    char *s = " + 123";
    int res = atoi(s);
    printf("string is: '%s', int is: '%d'\n", s, res);
    return 0;
}
