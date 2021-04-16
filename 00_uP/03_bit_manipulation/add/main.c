
//#define P0HW_ADDR 0x40000000
//#define POHW (*(unsigned char*)POHW_ADDR) 

int main(){
    char P0;    //char 선언 
    char P1;
    char P2;
    // clear
    P0 = 0x05;
    P1 = 0x15;
    P2 = P0 + P1;
    
    //POHW_ADDR = 0x4F;
    
	while(1);
}
