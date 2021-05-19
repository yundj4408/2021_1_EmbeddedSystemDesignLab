#include <stdio.h>

int main(void) {
    
    char buf[100];
    int n = 10000;
    int i,a,b,c;
    int val = n& 0xff;

    printf("val = %d", val);

    a = n/100;
    n %= 100;
    b = n/10;
    n %= 10;
    c = n;

    buf[0] = a+'0';
    buf[1] = b+'0';
    buf[2] = c+'0';

    printf("buf[0] = %c, buf[1] = %c, buf[2] = %c\n", buf[0], buf[1], buf[2]);

    //buf[4] = (char)mod - '0';
    //printf("%d\n", buf[4]);
    //printf("div = %d, mod = %d\n", div, mod);
    //for(i=0; i<3; i++)
    //{
    //    buf[i] = (char)((num%10) - '0');
        //printf("%c\n", buf[i]);
    //}

    return 0;
}
