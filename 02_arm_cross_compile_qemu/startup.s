	.syntax unified
	.cpu cortex-m4
	.thumb

.global g_vectors		// g_vectors ��� ������ ������Ÿ��, ���� ���� �ʵ���
.global Reset_Handler

	.section	.isr_vector, "a", %progbits
	.type		g_vectors, %object
	.size		g_vectors, .-g_vectors

g_vectors:				// ��ŷ�� �� ���Ǵ� ���̺�
	.word	_estack		// Stack pointer , ���ͷ�Ʈ ���� �ƴ�
	.word	Reset_Handler	// HW ���ͷ�Ʈ
	.word	0			// NMI_Handler
	.word	0			// HardFault_Handler
	.word	0			// MemManage_Handler
	.word	0			// BusFault_Handler
	.word	0			// UsageFault_Handler
	.word	0			
	.word	0			
	.word	0			
	.word	0			
	.word	0			// SVC_Handler
	.word	0			// DebugMon_Handler
	.word	0
	.word	0			// PendSV_Handler
	.word	SysTick_Handler                 //TickTime
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0



Reset_Handler:			// ����� ���� �ּ� ���� ���ͷ�Ʈ ���� ��ƾ
	bl main				// Reset ���ͷ�Ʈ�� �ɷ����� main ����

	
SysTick_Handler:


/*
NMI_Handler:
subroutines here
*/
