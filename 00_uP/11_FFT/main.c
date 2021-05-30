#include "STM32FDiscovery.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define F 200       //Sampling Frequency(Speed)
#define T 1/F       //Sampling Period
#define A 1       //Amplitude
#define N 100       //Number of sample Depth
#define H 32        //Number of harmonics
#define PI 3.14

unsigned char adc_val;
unsigned char rec;
unsigned int count = 0;
unsigned int i, j, k, a, b, c;
unsigned int l = 0;
float buf[8];        //Space for ADC string
unsigned int len;   //Space for ADC string len

char polynomial[100];

unsigned int tim2tick;  //Timer Variable:

unsigned int uart_data[423]= {
32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 
32, 95, 95, 95, 95, 95, 32, 32, 32, 32, 
32, 32, 95, 95, 95, 95, 95, 32, 95, 95, 
95, 32, 32, 32, 32, 32, 32, 32, 32, 95, 
95, 95, 95, 95, 32, 32, 32, 95, 32, 32, 
32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 
32, 32, 32, 95, 95, 95, 95, 32, 32, 10, 
32, 32, 32, 32, 32, 47, 92, 32, 32, 32, 
124, 95, 32, 32, 32, 95, 124, 32, 32, 32, 
32, 47, 32, 95, 95, 95, 95, 124, 95, 95, 
32, 92, 32, 32, 32, 32, 32, 32, 47, 32,
95, 95, 95, 95, 124, 32, 124, 32, 124, 32, 
32, 32, 32, 32, 32, 32, 32, 47, 92, 32,
32, 32, 124, 32, 32, 95, 32, 92, 32, 10, 
32, 32, 32, 32, 47, 32, 32, 92, 32, 32,
32, 32, 124, 32, 124, 95, 95, 95, 95, 95,
124, 32, 40, 95, 95, 95, 32, 32, 32, 32,
41, 32, 124, 95, 95, 95, 32, 124, 32, 124, 
32, 32, 32, 32, 32, 32, 124, 32, 124, 32, 
32, 32, 32, 32, 32, 32, 47, 32, 32, 92, 
32, 32, 124, 32, 124, 95, 41, 32, 124, 10, 
32, 32, 32, 47, 32, 47, 92, 32, 92, 32, 
32, 32, 124, 32, 124, 95, 95, 95, 95, 95,
95, 92, 95, 95, 95, 32, 92, 32, 32, 47, 
32, 47, 47, 32, 95, 32, 92, 124, 32, 124, 
32, 32, 32, 32, 32, 32, 124, 32, 124, 32, 
32, 32, 32, 32, 32, 47, 32, 47, 92, 32, 
92, 32, 124, 32, 32, 95, 32, 60, 32, 10, 
32, 32, 47, 32, 95, 95, 95, 95, 32, 92, 
32, 95, 124, 32, 124, 95, 32, 32, 32, 32, 
32, 95, 95, 95, 95, 41, 32, 124, 47, 32, 
47, 124, 32, 40, 95, 41, 32, 124, 32, 124, 
95, 95, 95, 95, 32, 32, 124, 32, 124, 95, 
95, 95, 95, 32, 47, 32, 95, 95, 95, 95, 
32, 92, 124, 32, 124, 95, 41, 32, 124, 10, 
32, 47, 95, 47, 32, 32, 32, 32, 92, 95, 
92, 95, 95, 95, 95, 95, 124, 32, 32, 32, 
124, 95, 95, 95, 95, 95, 47, 124, 95, 95, 
95, 95, 92, 95, 95, 95, 47, 32, 92, 95, 
95, 95, 95, 95, 124, 32, 124, 95, 95, 95, 
95, 95, 95, 47, 95, 47, 32, 32, 32, 32, 
92, 95, 92, 95, 95, 95, 95, 47, 32, 10,
10, 10, 10};                                //to Send data to computer


void sendStr(char buf[], int max);

void clk(void)
{
	RCC_CR = 0;
	RCC_PLLCFGR = 0;
	RCC_CFGR = 0;
		
	RCC_CR |= (1<<16); // HSE set
	while( (RCC_CR & ( 1<<17) ) == 0 ); // wait until HSE ready
	
	RCC_PLLCFGR |= 8;//0x00000008; // set PLLM
	RCC_PLLCFGR |= (336<<6);//|= (336<<6); // 		set PLLN
	RCC_PLLCFGR |= (0<<16); // set PLLP
	RCC_PLLCFGR |= (7<<24);//0x07000000; // set PLLQ

	RCC_PLLCFGR |= (1<<22); // set PLL src HSE
	

	RCC_CR |= (1<<24); // PLL ON
	while( (RCC_CR & (1<<25)) == 0); // wait until PLL ready
	
	FLASH_ACR |= 5;
	RCC_CFGR |= 2; // set PLL to system clock
	
		
	while( (RCC_CFGR & (12) ) != 8); // wait until PLL ready
	
	RCC_CFGR |= (1<<12) | (1<<10); // set APB1 div 4
	RCC_CFGR |= (1<<15); // set APB2 div2	

    SCB_CPACR |= (3<<20) | (3<<22);
}

void set_uart2() {
    //USART GPIO PIN PA2(TX), PA3(RX)
    RCC_AHB1ENR     |= 1<<0;                //Clock Enable
    GPIOA_MODER     |= (1<<5) | (1<<7);     //Alternative Function Mode Set
    GPIOA_AFRL      |= (7<<8) | (7<<12);    //

    //SET USART2
    RCC_APB1ENR     |= (1<<17);             //USART2 CLK ENABLE
    USART2_CR1      |= (0<<12);             //CONTROL REGISTER CHARACTER 1BYTE SO 8 BIT USE
    USART2_CR2      |= (0<<13) | (0<<12);   //STOP BIT SET 1

    USART2_BRR      |= (unsigned int)(42000000/115200);     //0x115200 -> 42000000

    USART2_CR1      |= (1<<3) | (1<<2);     //TX,RX ENABLE
    USART2_CR1      |= (1<<5);              //ALSO USART CAN USE PULL UP, PULL DOWN, TXE(DATA FLAG, IS IT IN?) RXNE(RX NOT EMPTY FLAG) WHEN THE BUFFER GET THE VALUE, RXNE BECOME 1
    USART2_CR1      |= (1<<13);

    //USART INTERRUPT ENABLE
    NVIC_ISER1      |= 1<<6;                //BECAUSE WE ADD NEW NVIC_ISER1 AND IT START AT 32, SO 38-32 = 6
    
}

// ADC, channel 1, PA1
void set_adc1() {
    RCC_AHB1ENR |= 0x00000001;          //RCC clock Enable
    GPIOA_MODER |= 3<<2;                //PA1 analog mode
    RCC_APB2ENR |= 1<<8;                //ADC1 Clock Enable
    RCC_CFGR    |= 1<<15 | 1<<13;       // set APB2 div4 = 42MHz (no need to know)

    ADC1_CR2    |= 1<<0;                //ADC1 enable

    ADC1_SMPR2  |= 3<<0;                // channel 1 sampling cycle 56 cycle
    ADC1_CR1    |= 2<<24 | 1<<5;        //8-bit resolution
                                        // end of-conversion interrupt enable

    ADC1_CCR    |= 1<<16;               // PCLK2 div 4 no need to know
    ADC1_SQR1   |= 0<<20;               // channel 1 : 1 conversion
    ADC1_SQR3   |= 1<<0;                // 1st conversion : channel

    NVIC_ISER0  |= 1<<18;               // enable intterupt

}

void set_timer2() {
    RCC_APB1ENR |= 1<<0;
    TIM2_CR1     = 0;                   //Initialize to 0

    TIM2_PSC     = 84-1;
    TIM2_ARR     = 1000-1;
    TIM2_DIER   |= 1<<0;
    TIM2_EGR    |= 1<<0;
    TIM2_CR1    |= 1<<0;

    NVIC_ISER0  |= 1<<28;
}

void TIM2_IRQHandler() {
    TIM2_SR &= 0x00000000;
    tim2tick++;
    if(tim2tick == 10)            //1000ms = 1s LED Toggle
    {
        GPIOD_ODR ^= 1<<13;         //LED Orange Blink
        ADC1_CR2  |= 1<<30;
        tim2tick = 0;
        
    }
}

void USART2_IRQHandler() {
    if( USART2_SR & (1<<5) ) 
    {
        rec = USART2_DR;                //Data Register 
       //after getting the input, we return the data to dr and print 
        USART2_DR = rec;
        while( !(USART2_SR & (1<<7)) );
        while( !(USART2_SR & (1<<6)) );
        //GPIOD_ODR ^= 1<<12;              //To see the data is in

        USART2_CR1 |= (1<<5);           //After interrupt SR be 0 and we need to turn the interrupt on

    }
}

void ADC1_IRQHandler() {
    if(ADC1_SR & 1<<1){
        adc_val = ADC1_DR & 0xFF;

        polynomial[l] = adc_val;
        l++;

        if (l == 100)
        {
            for(i = 0; i <N; i++)           //time advance 
            {                  
                int hi = 1;     //Harmonics 1 Hz
        
                for(j=0; j<H; j++)     //frequency
                {
                    float signal = (float)(A/hi)*sin(2*PI*hi*T*i);
                    polynomial[i] += signal;
                    hi = hi + 2;                                //1,3,5,7,9
                }
            }
            // fourier analysis
            //int probe_freq = 2;
            for (j=0; j<H; j++)     //fourier analysis H time (H frequency)
            {
                float freq_component = 0;
                int probe_freq = j;
                for (i=0; i<N; i++) //fourier analysis one time{ 
                {
                    float probe = (float)(A)*sin(2*PI*probe_freq*T*i);
                    freq_component += probe * polynomial[i];    //polynomial get ADCvalue 
                    len = sprintf(buf, "%6f\n", freq_component);
                    sendStr(buf, len); 
                }
            }
            l = 0;
        } 

        //len = sprintf(buf, "%3d\n", adc_val);
        //sendStr(buf, len); 
    }
    //ADC1_CR2    |= 1<<30;                   //IRQ Start again
}

void EXTI0_IRQHandler() {

    GPIOD_ODR ^= 1 << 13;
    GPIOD_ODR ^= 1 << 14;
    GPIOD_ODR ^= 1 << 15;
    EXTI_PR |= 1<<0;    // clear pending bit for EXTI}

}

int main (void)
{
	
	clk();
	
	RCC_CFGR |= 0x04600000;

    /* PORT A */
	RCC_AHB1ENR  |= 1<<0; //RCC clock enable register	
    GPIOA_MODER  |= 0<<0; // input mode
    GPIOA_OTYPER |= 0<<0; // output push-pull
    GPIOA_PUPDR  |= 0<<0; // no pull-up, pull-down

    /* button intr set */
    SYSCFG_EXTICR1 |= 0<<0; //EXTI0 connect to PA0
    EXTI_IMR       |= 1<<0; //Mask EXTI0
    EXTI_RTSR      |= 1<<0; //risign edge trigger enable
    EXTI_FTSR      |= 0<<0; //falling edge trigger disable
    NVIC_ISER0     |= 1<<6; // enable EXTI0 interrupt
	
	/* PORT D */
	RCC_AHB1ENR  |= 1<<3;		// PORTD enable
	GPIOD_MODER  |= 1<<24;		// PORTD 12 general output mode
	GPIOD_MODER  |= 1<<26;		// PORTD 13 general output mode
	GPIOD_MODER  |= 1<<28;		// PORTD 14 general output mode
	GPIOD_MODER  |= 1<<30;		// PORTD 15 general output mode
	GPIOD_OTYPER |= 0x00000000;
	GPIOD_PUPDR	 |= 0x00000000;
	
	GPIOD_ODR |= 1<<12;
    
    set_timer2();
    set_adc1();
    set_uart2();
    while(count < 423)
    {
        USART2_DR = uart_data[count++];
        while( !(USART2_SR & (1<<7)) );
        while( !(USART2_SR & (1<<6)) );
    }                                   //1byte send, when i

    ADC1_CR2    |= 1<<30;   //conversion start, because after usart run, we start the ad conversion

	while(1) 
    {
//        if( GPIOA_IDR & 0x00000001 ) {
//            GPIOD_ODR ^= 1 << 13;
//           GPIOD_ODR ^= 1 << 14;
//            GPIOD_ODR ^= 1 << 15;
//        }
	}
}

void sendStr(char buf[], int max) {                        //1byte send
    int cnt = 0;
    while (cnt < max) 
    {
        USART2_DR = buf[cnt++];
        while( !(USART2_SR & (1<<7)) );
        while( !(USART2_SR & (1<<6)) );
    }
}
