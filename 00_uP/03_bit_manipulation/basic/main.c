
//#define P0HW_ADDR 0x40000000
//#define POHW (*(unsigned char*)POHW_ADDR) 

int main(){
    char P0;    //char 선언 
   
    // clear
    P0 = 0x95;
    P0 &= ~(0x10);
    
    //POHW_ADDR = 0x4F;
    
	while(1);
}
