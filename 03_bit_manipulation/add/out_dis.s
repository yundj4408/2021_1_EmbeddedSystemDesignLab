
out.elf:     file format elf32-littlearm


Disassembly of section .init:

0800018c <_init>:
 800018c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 800018e:	bf00      	nop

Disassembly of section .fini:

08000190 <_fini>:
 8000190:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 8000192:	bf00      	nop

Disassembly of section .text.main:

08000194 <main>:

//#define P0HW_ADDR 0x40000000
//#define POHW (*(unsigned char*)POHW_ADDR) 

int main(){
 8000194:	b480      	push	{r7}
 8000196:	b083      	sub	sp, #12
 8000198:	af00      	add	r7, sp, #0
    char P0;    //char 선언 
    char P1;
    char P2;
    // clear
    P0 = 0x05;
 800019a:	2305      	movs	r3, #5
 800019c:	71fb      	strb	r3, [r7, #7]
    P1 = 0x15;
 800019e:	2315      	movs	r3, #21
 80001a0:	71bb      	strb	r3, [r7, #6]
    P2 = P0 + P1;
 80001a2:	79fa      	ldrb	r2, [r7, #7]
 80001a4:	79bb      	ldrb	r3, [r7, #6]
 80001a6:	4413      	add	r3, r2
 80001a8:	717b      	strb	r3, [r7, #5]
    
    //POHW_ADDR = 0x4F;
    
	while(1);
 80001aa:	e7fe      	b.n	80001aa <main+0x16>
