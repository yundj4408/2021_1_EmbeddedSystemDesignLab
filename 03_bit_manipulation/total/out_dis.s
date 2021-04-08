
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
int sub(int a, int b);

int main(){
 8000194:	b580      	push	{r7, lr}
 8000196:	b084      	sub	sp, #16
 8000198:	af00      	add	r7, sp, #0
    int P0 = 0x10;    //char 선언 
 800019a:	2310      	movs	r3, #16
 800019c:	607b      	str	r3, [r7, #4]
    int P1 = 0x30;
 800019e:	2330      	movs	r3, #48	; 0x30
 80001a0:	60fb      	str	r3, [r7, #12]
    int i;
    // clear
    
    for (i=0; i<5; i++)
 80001a2:	2300      	movs	r3, #0
 80001a4:	60bb      	str	r3, [r7, #8]
 80001a6:	e00a      	b.n	80001be <main+0x2a>
    {
        if (P1 == 0x0) break;
 80001a8:	68fb      	ldr	r3, [r7, #12]
 80001aa:	2b00      	cmp	r3, #0
 80001ac:	d00b      	beq.n	80001c6 <main+0x32>
        else P1 = sub(P1, P0);
 80001ae:	6879      	ldr	r1, [r7, #4]
 80001b0:	68f8      	ldr	r0, [r7, #12]
 80001b2:	f000 f80a 	bl	80001ca <sub>
 80001b6:	60f8      	str	r0, [r7, #12]
    for (i=0; i<5; i++)
 80001b8:	68bb      	ldr	r3, [r7, #8]
 80001ba:	3301      	adds	r3, #1
 80001bc:	60bb      	str	r3, [r7, #8]
 80001be:	68bb      	ldr	r3, [r7, #8]
 80001c0:	2b04      	cmp	r3, #4
 80001c2:	ddf1      	ble.n	80001a8 <main+0x14>
 80001c4:	e000      	b.n	80001c8 <main+0x34>
        if (P1 == 0x0) break;
 80001c6:	bf00      	nop
    }
    //POHW_ADDR = 0x4F;
    
	while(1);
 80001c8:	e7fe      	b.n	80001c8 <main+0x34>

Disassembly of section .text.sub:

080001ca <sub>:
}

int sub(int a, int b) {
 80001ca:	b480      	push	{r7}
 80001cc:	b083      	sub	sp, #12
 80001ce:	af00      	add	r7, sp, #0
 80001d0:	6078      	str	r0, [r7, #4]
 80001d2:	6039      	str	r1, [r7, #0]
    return a-b;
 80001d4:	687a      	ldr	r2, [r7, #4]
 80001d6:	683b      	ldr	r3, [r7, #0]
 80001d8:	1ad3      	subs	r3, r2, r3
}
 80001da:	4618      	mov	r0, r3
 80001dc:	370c      	adds	r7, #12
 80001de:	46bd      	mov	sp, r7
 80001e0:	f85d 7b04 	ldr.w	r7, [sp], #4
 80001e4:	4770      	bx	lr
