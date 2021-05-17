STM32f4.h 헤더파일에 ADC 구조체 선언했다.



main문에서 set adc

1. clock enable
2. PA1를 analog mode로 설정한 후 
3. ADC1 Clock enable
4. 자세하게 알 필요는 없다 이런게 있다. RCC_CFGR
5. ADC1_CR2 -> ADC1 Enable, 사용할 수 있게
6. ADC1_SMPR2 -> 자세하게 알필요없다 이런ㄱ ㅔ있다 데이터시트
7. ADC1_CR1 8비트 resolution은 양자화에서 y값이 [7:0] 표현, 더 디테일하게 보기 위해선 비트를 올리면 더 정밀
   정밀해질 수록 하드웨어 더 일한다.
   ADC도 interrupt가 있다. 변환이 완료 되었을 때 Interrupt 발생, 데이터가 변환 완료된 것을 확인하기 위해 사용
8. ADC1_CR1 자세히 알필요 X
9. ADC_SQR1 |= 0<<20 를 통해 ADC1에도 여러가지 채널이 있다. 이번 예제에서는 하나의 채널만 사용한다.
10. ADC_SQR3 변환 순서를 설정해주는 건데 우리는 한 채널만 사용하니 중요하지 않다.
11. 최종적으로 interrupt 사용할 수 잇게 하기 위해 인터럽트 셋업 



메인문에 가서 

set_adc1(); 호출하고 `ADC1_CR2	|= 1<<30`이것을 통해 conversion start



ADC_IRQHandler 세팅

1. ADC1_SR의 1번이 1이면 (EOC) 비트를 확인하여 1이면 인터럽트 발생

2. 0x800~~ stack메모리에 변수를 가져와야하니 변환이 완료된 데이터를 받을 걸 만든다. 
   unsigned char adc_val; 선언

3. 읽은 데이터는 숫자로 받았는데 usart로 보낼라면 문자로 보내야 한다. 8bit로 나타낼수 있는 큰 수가 255.
   이 수를 문자로 바꿔줘야 한다. usart에서는 문자밖에 안되서.
   `len = sprintf(buf, "%3d\n", adc_val)` sprintf는 문자 길이 반환
   adcval = 177이면 -> buf = '1', '7', '7' 이런식으로 문자로 저장이 된다.

4. 문자열, USART22_DR = rec 1바이트 보내는 건데, 우리는 문자가 3개가 있고 \n도 있으니 총 4개가 필요하다. 
   

5. 함수를 만들었다. 인자로는 문자열과 문자열 길이 (반복 횟수)
   문자열 인자로 받아온 길이 만큼 받아오고 while (cnt < max), 그만큼 usart에 보내준다. 

6. 다시 IRQHandler로 돌아가서 받은다음 바로 함수 호출

7. adc중에서도 계속 도는것과 한번 변화하고 끝나는 것이 있다. 우리는 한번 변화하고 끝나는것이니 다시 스타트 해준다. main함수 끝에 있던 ADC1_CR2 |= 1<<30; ADC변환 다시하라는거 넣어준다 IRQ에

8. 임베디드에서 stdio.h사용한다면 binary가 너무 커져서 되도록이면 안 쓰는 방향으로 해야한다. 

9. ADC_Interrupt사용한다 했는데 ISR추가 안해줫음. 추가. NVIC_ISER0 1<<6 6번. 다시보기

10. 에러가 떴는데 stdio.h arm에서 추가하는데 문제가 있따. 그래서 make파일 19줄에 링킹할때
    `-specs=nano.specs -specs=nosys.specs` 추가해야 한다. $(LD) 와 $(LFLAGS) 사이에 추가

11. 추가해도에러 뜬다. linkerscript파일도 추가해줘야한다. sprintf도 힙과 stack 용량 줘야한다. sprintf가 malloc처럼 공간을 차지하는 것 같다. 그래서 추가.

    ```c
    _Min_Heap_Size = 0x200;     /* required amount of heap for sprintf */
    _Min_Stack_Size = 0x400;    /* required amount of stack for sprintf */
    
    ```

    shift+g 맨끝으로 가서 메모리 공간 할당. .user_heap.stack

    

12. make flash해서 보면 adc 전압 측정중 

13. 그래프를 보기 위해 아두이노 설치 -> 아두이노 PORT ttyUSB0 세팅

14. Tools에 SerialPlotter (아두이노에서 폰트 깨짐을 sudo apt-get install nanum 명령어를 통해 해결)

15. 과제는  stdio.h사용하지않고 구현하기 똑같이 sprintf없이