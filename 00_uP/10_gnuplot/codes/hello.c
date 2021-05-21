#include <stdio.h>

int main(void){
    
    FILE* file_out;
    file_out = fopen("out.txt", "w");
    
    int y;

    for(int i = 0; i < 100; i++) {                  //x = i y = y
        y= 5 * i + 10;
        fprintf(file_out, "%d \t %d \n", i, y);
    }

    return 0;
}
