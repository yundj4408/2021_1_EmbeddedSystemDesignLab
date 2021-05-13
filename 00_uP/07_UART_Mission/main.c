#include "STM32FDiscovery.h"

unsigned char rec;
unsigned int i = 0;
unsigned int j = 0;
unsigned int k = 0;
unsigned int loop;
unsigned int loop_in;


unsigned int count = 0;
unsigned int temp[12] = {0};
unsigned int temp_count = 0;
unsigned count_two = 0;
unsigned count_third = 0;

unsigned int uart_data[111]= {
47, 42, 42, 42, 42, 42, 42, 42, 42, 42, 
42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 
42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 
42, 42, 42, 42, 47, 10, 47, 42, 32, 76,
69, 68, 32, 67, 79, 78, 84, 82, 79, 76,
32, 83, 72, 69, 76, 76, 32, 70, 79, 82, 
32, 83, 84, 77, 51, 50, 70, 52, 32, 42, 
47, 10, 47, 42, 42, 42, 42, 42, 42, 42, 
42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 
42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 
42, 42, 42, 42, 42, 42, 47, 10, 62, 62,
32};

unsigned int help[178] = {
42, 32, 67, 111, 109, 109, 97, 110, 100, 32,
76, 105, 115, 116, 32, 10, 32, 32, 32, 45, 
32, 76, 69, 68, 79, 78, 10, 32, 32, 32, 
32, 32, 32, 32, 32, 32, 32, 32, 43, 32, 
32, 32, 97, 114, 103, 117, 109, 101, 110, 116,
32, 91, 49, 44, 32, 50, 44, 32, 51, 44, 
32, 52, 93, 10, 32, 32, 32, 45, 32, 76,
69, 68, 79, 70, 70, 10, 32, 32, 32, 32, 
32, 32, 32, 32, 32, 32, 32, 43, 32, 32, 
32, 97, 114, 103, 117, 109, 101, 110, 116, 32, 
91, 49, 44, 32, 50, 44, 32, 51, 44, 32, 
52, 93, 10, 32, 32, 32, 45, 32, 76, 69, 
68, 79, 78, 32, 65, 76, 76, 10, 32, 
32, 32, 45, 32, 76, 69, 68, 79, 70, 70, 
32, 65, 76, 76, 10, 32, 32, 32, 45, 32, 76, 
69, 68, 79, 78, 32, 83, 69, 81, 10, 
32, 32, 32, 45, 32, 76, 69, 68, 79, 70, 70, 
32, 83, 69, 81, 10, 62, 62, 32};

unsigned int bash[4] = {10, 62, 62, 32};


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

void USART2_IRQHandler() {
    if( USART2_SR & (1<<5) ) 
    {
        rec = USART2_DR;                //Data Register 
       //after getting the input, we return the data to dr and print 
        USART2_DR = rec;
        
        temp[temp_count] = rec;          //save data to global variable
        temp_count++;
        while( !(USART2_SR & (1<<7)) );
        while( !(USART2_SR & (1<<6)) );
        //GPIOD_ODR ^= 1<<12;            //To see the data is in

        USART2_CR1 |= (1<<5);           //After interrupt SR be 0 and we need to turn the interrupt on

    }
}

void EXTI0_IRQHandler() {

    GPIOD_ODR ^= 1 << 13;
    GPIOD_ODR ^= 1 << 14;
    GPIOD_ODR ^= 1 << 15;
    EXTI_PR |= 1<<0;    // clear pending bit for EXTI0
}

void Delay() {
    for(loop=0; loop<1000000; loop++)
    {
        while(loop_in < 1000000) {loop_in++;}
    }
}

void Receive(void){

    for (i=0; i<12; i++) 
    {
        if((temp[i] == 104) && (temp[i+1] == 101) && (temp[i+2] == 108) && (temp[i+3] == 112))
        {                                       //HELP function
            for (j=0; j<5; j++)         
            {
                if(temp[j] == 13)               // /r = ascii code 13 
                {
                    while (count_two < 178)
                    {
                        USART2_DR = help[count_two++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) );
                    }
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    temp_count = 0;                   //to reset the temp_count 
                }
            }
        }




        else if((temp[i] == 76) && (temp[i+1] == 69) && (temp[i+2] == 68) && (temp[i+3] == 79) && (temp[i+4] == 78) && temp[i+5] == 32)                                     //LEDON Function
        {
            if (temp[i+7] == 13)
            {
            
                if(temp[i+6] == 49)
                {
                    GPIOD_ODR |= 1 << 12;
                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count 
                }

                else if (temp[i+6] == 50)
                {
                    GPIOD_ODR |= 1 << 13;

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count 
                }

                else if (temp[i+6] == 51)
                {
                    GPIOD_ODR |= 1 << 14;

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count 
                }
                else if (temp[i+6] == 52)
                {
                    GPIOD_ODR |= 1 << 15;

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count 
                }
            }

            else if (temp[i+9] == 13)
            {
                if ((temp[i+6] == 65) && (temp[i+7] == 76) && (temp[i+8] == 76))
                { 
                    GPIOD_ODR |= 1 << 12;
                    GPIOD_ODR |= 1 << 13;
                    GPIOD_ODR |= 1 << 14;
                    GPIOD_ODR |= 1 << 15;

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count  
                }

                else if ((temp[i+6] == 83) && (temp[i+7] == 69) && (temp[i+8] == 81))   //LEDON SEQ
                {

                    GPIOD_ODR |= 1 << 12;
                    Delay();
                    GPIOD_ODR |= 1 << 13;
                    Delay();
                    GPIOD_ODR |= 1 << 14;
                    Delay();
                    GPIOD_ODR |= 1 << 15;
                    Delay();

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count  
                }
            }
        }    

        else if((temp[i] == 76) && (temp[i+1] == 69) && (temp[i+2] == 68) && (temp[i+3] == 79) && (temp[i+4] == 70) && temp[i+5] == 70 && temp[i+6] == 32)                                     //LEDOFF Function
        {
            if (temp[i+8] == 13)
            {
            
                if(temp[i+7] == 49)
                {
                    GPIOD_ODR &= ~(1 << 12);
                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count 
                }

                else if (temp[i+7] == 50)
                {
                    GPIOD_ODR &= ~(1 << 13);

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count 
                }

                else if (temp[i+7] == 51)
                {
                    GPIOD_ODR &= ~(1 << 14);

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count 
                }
                else if (temp[i+7] == 52)
                {
                    GPIOD_ODR &= ~(1 << 15);

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count 
                }
            }
        
      
            else if (temp[i+10] == 13)                //LEDOFF ALL
            {
                GPIOD_ODR |= 1<<12;
                if ((temp[i+7] == 65) && (temp[i+8] == 76) && (temp[i+9] == 76))
                {
                    GPIOD_ODR &= ~(1 << 12);
                    GPIOD_ODR &= ~(1 << 13);
                    GPIOD_ODR &= ~(1 << 14);
                    GPIOD_ODR &= ~(1 << 15);

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count  
                }

                else if ((temp[i+7] == 83) && (temp[i+8] == 69) && (temp[i+9] == 81))   //LEDOFF SEQ
                {

                    GPIOD_ODR &= ~(1 << 12);
                    Delay();
                    GPIOD_ODR &= ~(1 << 13);
                    Delay();
                    GPIOD_ODR &= ~(1 << 14);
                    Delay();
                    GPIOD_ODR &= ~(1 << 15);
                    Delay();

                    while (count_third < 4)
                    {
                        USART2_DR = bash[count_third++];
                        while(!(USART2_SR & (1<<7)) );
                        while(!(USART2_SR & (1<<6)) ); 
                    } 
                    for (k=0; k<12; k++)
                    {
                        temp[k] = 0;                  //After printing help guide, empty temp
                    }
                    count_third = 0;
                    temp_count = 0;                   //to reset the temp_count  
                }
                
           }    
        }
    }
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
	
	//GPIOD_ODR |= 1<<12;

    set_uart2();
    while(count < 111)
    {
        USART2_DR = uart_data[count++];
        while( !(USART2_SR & (1<<7)) );
        while( !(USART2_SR & (1<<6)) );
    }                                   //1byte send, when 

	while(1) 
    {
        Receive();
	}
}

