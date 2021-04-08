
//#define P0HW_ADDR 0x40000000
//#define POHW (*(unsigned char*)POHW_ADDR) 
int sub(int a, int b);

int main(){
    int P0 = 0x10;    //char 선언 
    int P1 = 0x30;
    int i;
    // clear
    
    for (i=0; i<5; i++)
    {
        if (P1 == 0x0) break;
        else P1 = sub(P1, P0);
    }
    //POHW_ADDR = 0x4F;
    
	while(1);
}

int sub(int a, int b) {
    return a-b;
}
