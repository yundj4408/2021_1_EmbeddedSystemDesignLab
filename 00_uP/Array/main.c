#include "STM32FDiscovery.h"
	
void TIM2_IRQHandler() {

}

int main (void)
{	
    int numArr[3] = {1, 2, 3};
    int sum;


    sum = add(numArr[1], numArr[2]);
}

int add(int i, int j)
{
    int k;
    k = i+j;

    return k;
 }
