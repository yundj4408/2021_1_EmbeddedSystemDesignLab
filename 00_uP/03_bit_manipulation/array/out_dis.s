
out.elf:     file format elf32-littlearm


Disassembly of section .init:

080001b4 <_init>:
 80001b4:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 80001b6:	bf00      	nop

Disassembly of section .fini:

080001b8 <_fini>:
 80001b8:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 80001ba:	bf00      	nop

Disassembly of section .text.main:

080001bc <main>:
int main()
{
 80001bc:	b4b0      	push	{r4, r5, r7}
 80001be:	b08f      	sub	sp, #60	; 0x3c
 80001c0:	af00      	add	r7, sp, #0
    int numArr[10] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 110};
 80001c2:	4b0f      	ldr	r3, [pc, #60]	; (8000200 <main+0x44>)
 80001c4:	1d3c      	adds	r4, r7, #4
 80001c6:	461d      	mov	r5, r3
 80001c8:	cd0f      	ldmia	r5!, {r0, r1, r2, r3}
 80001ca:	c40f      	stmia	r4!, {r0, r1, r2, r3}
 80001cc:	cd0f      	ldmia	r5!, {r0, r1, r2, r3}
 80001ce:	c40f      	stmia	r4!, {r0, r1, r2, r3}
 80001d0:	e895 0003 	ldmia.w	r5, {r0, r1}
 80001d4:	e884 0003 	stmia.w	r4, {r0, r1}
    int add;
    int sub;
    int multiply;


    add = numArr[0] + numArr[1];
 80001d8:	687a      	ldr	r2, [r7, #4]
 80001da:	68bb      	ldr	r3, [r7, #8]
 80001dc:	4413      	add	r3, r2
 80001de:	637b      	str	r3, [r7, #52]	; 0x34
    sub = numArr[3] - numArr[2];
 80001e0:	693a      	ldr	r2, [r7, #16]
 80001e2:	68fb      	ldr	r3, [r7, #12]
 80001e4:	1ad3      	subs	r3, r2, r3
 80001e6:	633b      	str	r3, [r7, #48]	; 0x30
    multiply = numArr[4] * numArr[5];
 80001e8:	697b      	ldr	r3, [r7, #20]
 80001ea:	69ba      	ldr	r2, [r7, #24]
 80001ec:	fb02 f303 	mul.w	r3, r2, r3
 80001f0:	62fb      	str	r3, [r7, #44]	; 0x2c
 80001f2:	2300      	movs	r3, #0
}
 80001f4:	4618      	mov	r0, r3
 80001f6:	373c      	adds	r7, #60	; 0x3c
 80001f8:	46bd      	mov	sp, r7
 80001fa:	bcb0      	pop	{r4, r5, r7}
 80001fc:	4770      	bx	lr
 80001fe:	bf00      	nop
 8000200:	0800018c 	.word	0x0800018c
