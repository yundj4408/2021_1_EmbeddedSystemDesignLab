# WEEK5 : gdb를 이용하여 step instruction 추적을 통해 실행과정 분석



### 1. ARM(Advanced RISC Machine)

- #### Thumb 모드 / ARM 모드

  ARM과 x86의 가장 큰 차이점은 Thumb 모드라는 것이 있다는 것이다. ARM 자체가 모바일/임베디드 등 PC와는 다른 환경에 맞춰서 설계했기 때문에 저전력이 핵심 기술 중 한가지였고, 또 한가지로 처음 설계될 당시 임베디드 계열에서는 32bit가 아닌 16bit가 대세였다고 한다. 이러한 여러가지 상황에 맞추기 위해 2가지 모드를 지원하게 되었고, 리버싱을 할 때에도 이 부분을 고려해야 한다. 쉘 코드를 작성할 때에도 당연히 바이트 수를 줄이기 위해 Thumb모드로 작성하는 것이 좋다.

- #### ARM 모드

  **레지스터 :**  R0 ~ R15 (16개)
  **기계어코드 길이 :** 32bits (4 bytes)

  

- #### Thumb 모드

  **레지스터 :** R0 ~ R7 (8개)
  **기계어코드 길이 :** 16bits (2 bytes)

  

- #### Thumb <--> ARM 모드 전환

  BL**X**/B**X**등 **X**로 끝나는 분기문 명령으로 모드 전환

  

- #### ARM에선 스택을 위한 명령어가 따로 존재하지 않음 (ex. push, pop X)

  - **장점 :** CALL을 연속적으로 사용하는 경우가 아닌, 한번만 CALL 했을 때, 스택을 사용하지 않고, 레지스터를 사용함으로써 속도면에서 큰 이득.
  - **단점** : CALL이 연속적인 즉, 어떤 서브 루틴에서 또 다른 서브 루틴을 콜 했을 때, lr에 복귀할 주소가 또 들어가게 되면서, lr값을 덮어쓰게 한게 된다. 이럴 땐 수동으로 sp(r13)을 이용해 스택에 r14값들을 넣어줘야 한다. 

- #### ARM Core 로드맵

  ![ARMCore](./Pictures/ARMCore.png)

  - 클래식 ARMCore
  - Cortex 암코어 : 응용 프로세스용, 임베디드용
  - 각 프로세서 군의 특성을 파악 -> 설계 목표에 부합하는 프로세서 선정
  - 최신 프로세서 구조의 발전 흐름을 알아볼 수 있음
  - VFP 부동소수점 고속 연산
  - Jazelie 자바 명령어 가속
  - 응용프로세서 : 임베디드 프로세서보다 더 큰 의미로 OS를 올릴 수 있다. 



### 2. ARM의 구조와 명령어 실행 

https://studylib.net/doc/18252726/arm%C2%AE-and-thumb%C2%AE-2-instruction-set-quick-reference-card (quick reference card)

https://web.eecs.umich.edu/~prabal/teaching/eecs373-f10/readings/ARMv7-M_ARM.pdf 가 armv7-m Architecture 레퍼런스 메뉴얼

### 2. ARM Instruction Set Format

- #### 레지스터

  레지스터는 임시로 데이터를 보관하고, 연산에 사용되고, 프로그램 제어에 사용되는 접근 속도가 가장 빠른 임시 기억 장치이다. 

  x86과 상당한 차이점이 있다. 일단 범용 레지스터의 수가 더 많으며, x86에는 존재하지 않는 Link Register가 존재한다. 왜 레지스터가 많이 안 쓰는가? 가격 때문인거지 암암. 근데 더 쓸려면 더 쓸 수 잇다. 설계할 때 32개 쓰면 1비트 더 추가하면 된다 원래 2^4니 4비트인데.

  - **R0~R12 :** 범용 레지스터, 인자값 및 임시 계산 저장소 등

    - **r0 : **Return value, first function argument

  - **R13(SP)** : Stack Pointer, x86의 ESP와 비슷한 역할 수행, ARM 동작 모드별로 스택 포인터를 가르키고 있다. 

  - **R14(LR) : **Link Register, 함수 호출 전 LR에 리턴 주소를 저장하고 점프함 (함수 호출 시 리턴주소 스택 활용 X)

    - 함수 호출 시 복귀할 주소를 저장하기 위해서 레지스터까지 1개를 할당했는데 여러번 분기 (BL)하는 경우가 아닌 한번만 분기(BL)하는 경우라면, 함수에서 원래의 주소로 복귀할 때 스택을 사용하지 않고 R14 레지스터를 사용함으로써, 그 속도에서 이익을 얻게 되는 것입니다. 

      **스택 접근 = 메인 메모리 접근 = 느림**

  - **R15(PC)** : 

  - **PC : ** x86에서의 EIP 레지스터와 동일한 역할 수행. 다음에 실행할 코드의 주소 저장

  

  - ARM의 32bit 레지스터 (16개의 integer register, 각 레지스터는 32bit)

    | Register | ABI Name | Description                           | Volatile     |
    | -------- | -------- | ------------------------------------- | ------------ |
    | r0       |          | Parameter, result, scratch register 1 | Volatile     |
    | r1       |          | Parameter, result, scratch register 2 | Volatile     |
    | r2       |          | Parameter, scratch register 3         | Volatile     |
    | r3       |          | Parameter, scratch register 4         | Volatile     |
    | r4-10    |          | -                                     | Non-volatile |
    | r11      |          | Frame pointer                         | Non-volatile |
    | r12      | IP       | Intra-procedure-call scratch register | Volatile     |
    | r13      | SP       | Stack pointer                         | Non-volatile |
    | r14      | LR       | Link register                         | Non-volatile |
    | r15      | PC       | Program counter                       | Non-volatile |

    

  - ARM의 64bit 레지스터 (32개의 integer register, x31은 특수 인코딩 레지스터)

    | Register | ABI Name | Description                                   | Volatile     |
    | -------- | -------- | --------------------------------------------- | ------------ |
    | X0       |          | Parameter/scratch register 1, result register | Volatile     |
    | X1-7     |          | Parameter/scratch register 2-8                | Volatile     |
    | X8-15    |          | Scratch registers                             | Volatile     |
    | X16-17   |          | Intra-procedure-call scratch registers        | Volatile     |
    | X18      |          | Platform registe                              | Non-volatile |
    | X19-28   |          | Scratch registers                             | Non-volatile |
    | X29      | FP       | Frame pointer                                 | Non-volatile |
    | X30      | LR       | Link registers                                | Non-volatile |

    가장 중요한 점은 **Stack pointer가 General purpose register에서 제외**되고 x31레지스터에 인코딩 됐다.

    

- #### Calling Convention (함수 호출 규약)

  x86에서는 cdecl, fastcall, stdcall 등의 다양한 함수 호출 규약이 존재했으나,

  - **R0~R12 : **범용 레지스터, 인자값 및 임시 계산 저장소 등
  - **R13(SP) : **Stack Pointer, x86의 ESP와 비슷한 역할 수행

  

- #### ARM Instruction Set

  - ARM 32bit의 Instruction Set
    ![32bitARMISA](./Pictures/32bitARMISA.png)

  - ARM 64bit의 Instruction Set

    ![64bitARMISA](./Pictures/64bitARMISA.png)
    기존 T32와 A32를 이용하는 방식이다. 

  

- #### 연산 순서 (보통 <-)

  ex) **ADD R0, R1, #0x2 :** R1에 0x2를 ADD한 결과값을 R0에 저장
  	  **MOV R0, R1 :** R0 레지스터에 R1 레지스터 값을 대입

  

- #### 메모리 연산 - STR, LDR

  **STR :** 메모리 주소에 레지스터 값을 저장 (연산방향 : ->)

  ex) **MOV R0, #0x100 :** R0 레지스터에 0x100 저장

  ​      **MOV R1, #0xFF  :** R1 레지스터에 0xFF 저장

  ​      **STR R1, [R0]     :** 0x100번지에 0xFF 저장

  - [레지스터] : 해당 레지스터의 값에 있는 메모리 주소 (C언어의 포인터와 유사)  

  

  ex) **STR R1, [R0, #4] :** R0+4번지에 R1 레지스터 값을 저장 

  - []안에서 콤마(,)와 숫자상수 #을 이용해 해당 R0에서 상대적인 offset 위치의 메모리 주소 access 가능

  - offset 범위 -4095~4096

  ex) **STR R1, [R0], #4** : R0번지에 R1 레지스터 값을 저장하고, R0의 주소값을 +4

  - []밖에서 콤마(,)와 숫자상수 #는 Post Index 기능

  - 즉 R1값을 R0에 저장하고 R0 주소값을 상수값으로 변화시키는 것

  

  ex) **STR R1, [R0, #4]! :** R0+4번지에 R1 레지스터 값을 저장하고, **R0의 주소값 +4** 

  - ! 는 auto-update 옵션, offset이 +된 값이 해당 레지스터에 저장됨단순히 [R0,#4]는 R0+4번지만 가르키는 것으로 끝나지만, 

  - [R0,#4]!은 R0+4번지를 가르키고, R0=R0+4까지 실행됨(+와 +=차이)

     

  **LDR :** 해당 메모리 주소의 값을 레지스터에 저장 (연산방향 : <-)

  ex) **LDR R1, [R1, #4] :** R1에 4byte 더한 주소에 저장되어 있는 값을 R1에 저장



https://kyuhyuk.kr/article/simple-arm-operating-system/2019/03/04/Simple-ARM-Operating-System-Chapter-2 참고해서 다른 md파일에 더 정리 할 예정이다. 



## GDB

### 1. gdb란?

gdb라고 부르는 **GNU Debuggeer**는 GNU 소프트웨어 시스템을 위한 기본 디버거이다. GDB는 다양한 유닉스 기반의 시스템에서 동작하는 이식성있는 디버거로, 에이다, C, C++, 포트란 등의 여러 프로그래밍 언어를 지원한다.

GDB는 임베디드 시스템을 디버깅할 때 사용되는 '원격' 모드를 지원하는데, 우리가 사용할 디버깅 방식은 **원격 디버깅 방식**이다. **원격 디버깅 방식은** GDB가 한 머신 상에서 동작하고, 디버그할 프로그램은 다른 머신 상에서 동작하는 것을 말한다. GDB는 GDB 프로토콜을 알고 있는 원격자의 'stub'과 직렬 포트 혹은 TCP/IP를 통해 통신 할 수 있다. 



### 2. gdb 명령어 

**01. 정보보기**

|         명령어         |                            Action                            |
| :--------------------: | :----------------------------------------------------------: |
|     info [명령어]      | 명령어에 대한 정보를 보여준다.<br />ex) info functions -> 현재 실행 파일의 함수들을 보여준다.<br />ex) info break -> 현재 설치된 브레이크 포인트를 보여준다. |
|       p [변수명]       |                   해당 변수의 value를 출력                   |
|    p $[레지스터명]     |                 레지스터에 들어있는 값 출력                  |
| p /[출력형식] [변수명] |                 출력형식에 맞게 변수값 출력                  |
|        출력형식        | t : 2진수<br />o: 8진수<br />d : 부호없는 10진수<br />u: 부호없는 10진수<br />x: 16진수<br />c: 최초 1바이트 값을 문자형으로 출력<br />f: 부동소수점<br />a: 가장 가까운 심볼의 오프셋 출력 |

**02. 소스보기** (l or list)

|         명령어         |                            Action                            |
| :--------------------: | :----------------------------------------------------------: |
|          list          |            main 함수를 기준으로 소스를 출력한다.             |
|      list [정수]       | 정수행을 기준으로 출력한다. ex) list 10 -> 10행을 기준으로 출력 |
|      list 함수명       |                  함수명의 소스를 출력한다.                   |
|         list -         |                 현재 출력된 행의 이전행 출력                 |
| list 파일명.c : 함수명 |               파일명의 함수명 부분을 출력한다.               |

**03. 브레이크 포인트**

|            명령어            |                            Action                            |
| :--------------------------: | :----------------------------------------------------------: |
|         break 함수명         |                함수명에 브레이크 포인트 설치                 |
|         break [정수]         |                정수행에 브레이크 포인트 설치                 |
|    break 파일명.c: 함수명    |         파일명의 함수명 부분에 브레이크 포인트 설치          |
|     break + or - [정수]      |  현재행에서 정수만큼 + 혹은 - 한 곳에 브레이크 포인트 설치   |
|        break *주소값         |                주소값에 브레이크 포인트 설치                 |
|   break [정수] if var == 0   | 정수행에 브레이크 포인트를 설치하는데 var 값이 0일 때 작동한다 |
|              tb              |         break 와 동일, 하지만 1회용 브레이크 포인트          |
| info break -> d [break 번호] |                     브레이크 포인트 해제                     |

**04. 진행 명령어**

|   명령어    |                            Action                            |
| :---------: | :----------------------------------------------------------: |
|   r(run)    |                        프로그램 실행                         |
|   k(kill)   |                        프로그램 종료                         |
|   s(step)   |  하나의 행 수행 후 정지, 함수 호출 시 함수 안으로 들어간다.  |
|  s [정수]   |                       s를 정수번 수행                        |
|     si      | 어셈블리 명령어 단위 수행, s와 동일하게 하나 행 수행 후 정지하지만 어셈블리 명령어 단위에서 한다. |
|      n      | 하나의 행 수행 후 정지, 함수 호출 시 무시하고 다음 행으로 넘어간다. |
|  n [정수]   |                       n을 정수번 수행                        |
|     ni      | 위와 마찬가지, n과 동일하게 하나 행 수행 후 정지하지만 어셈블리 명령어 단위에서 수행 |
| c(continue) |    다음 브레이크 포인트까지 진행한다.(없을경우 r과 동일)     |
|      u      |                      현재 루프 빠져나감                      |
|   finish    |                 현재 함수 수행 후 빠져 나감                  |
|   return    |               현재 함수 수행하지않고 빠져나감                |
| return 123  |              return과 동일, 하지만 리턴 값 지정              |

**05. 스택 상태 검사**

|        명령어        |              Action               |
| :------------------: | :-------------------------------: |
| info f [프레임 번호] |       스택 프레임 내용 출력       |
|      info args       |      함수 호출시 인자를 출력      |
|     info locals      |       함수의 지역변수 출력        |
|      info catch      |       함수 예외 핸들러 출력       |
|          bt          |       전체 스택 프레임 출력       |
|   frame [스택번호]   |   스택번호 스택 프레임으로 이동   |
|          up          |     상위 스택프레임으로 이동      |
|      up [숫자]       | 숫자만큼 상위 스택프레임으로 이동 |
|         down         |     하위 스택프레임으로 이동      |
|     down [숫자]      | 숫자만큼 하위 스택프레임으로 이동 |

**06. 메모리 상태 검사**

\- x/[범위] [출력형식] [범위의단위]	[메모리주소나 함수명]

 - 범위 : 기본 4바이트
 - 출력 형식
   - t : 2진수
   - o : 8진수
   - d : 부호없는 10진수
   - u : 부호없는 10진수
   - x : 16진수
   - c : 최초 1바이트 문자형 출력
   - f : 부동소수점
   - a : 가장 가까운 심볼 오프셋 출력
   - s : 문자열 출력
   - i : 어셈블리 형식 출력범위의 단위
 - 범위의 단위
    - b : 1 byte 단위
    - h : 2 byte 단위
    - w : 4 byte 단위
    - g : 8 byte 단위
 - Example
    - x/10i main :  main 함수로부터 40byte를 어셈블리로 출력
    - x/10 main : main 함수로부터 40byte를 출력
    - x/10b 0x8048200: 주소로부터 10byte를 출력

**07. 기타**

|         명령어          |                       Action                       |
| :---------------------: | :------------------------------------------------: |
|    directory [경로]     |  소스 파일을 탐색하기 위해 경로에 directory 추가   |
|    objectdir [경로]     |                 오브젝트 경로 등록                 |
|     disas [함수명]      |          특정함수의 어셈블리 코드를 출력           |
|   disas [주소] [주소]   |          주소사이의 어셈블리 코드를 출력           |
|   call [함수명(인자)]   |            특정 함수를 인자값으로 호출             |
|      jump *[주소]       |               주소로 강제적으로 분기               |
|      jump [행번호]      |               특정 행으로 강제 분기                |
|      jump [함수명]      |               특정 함수로 강제 분기                |
|      info signals       |                  signal 종류 출력                  |
|    signal [시그널명]    | 디버깅중인 프로세스에 시그널 전달 (signal SIGKILL) |
| set {타입}(주소) = [값] | 특정 메모리에 값을 지정 (set {int}0x8048300 = 100) |
|        info 탭키        |          info 로 확인 가능한 명령어 출력           |
|        info set         |               설정 가능한 내용 출력                |



## ARM Assembly 



우리는 원격 디버깅을 2개의 커멘드 창을 통해 할 예정이다. gdb는 대부분의 Linux 시스템에 사용되는 텍스트 기반의 디버거이다. 리모트 디버깅을 하려면 타켓에는 gdbserver를 실행하고 호스트에는 Cross Debugger gdb를 실행해야 한다. 

그래서 qemu를 target 서버로 만들었고, 다른 1개의 커멘드 창을 gdb-multiarch로 만들어서 확인하였다. 
<img src="./Pictures/gdbsetting.png" alt="gdbsetting" style="zoom:70%;" />

**기본 절차**

1. 2개의 커멘드 창을 연다.

2. 1개의 커멘드 창에는 make gdb(host), 1개의 커멘드 창에는 make qemu(target)를 통해 가상 STM32F4 보드를 연다.

3. gdb 창에서 밑에 코드와 같이 입력한다.

   ```gdb
   >>>target remote :1234 or target remote 127.0.0.1:1234
   
   >>>file out.elf
   
   >>>load
   
   >>>b main
   
   >>>c
   
   >>>n or si			<- n은 code 한 줄 debug, si(step)
   ```

   

#### 1. Add

**main.c**

```c
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
```

<img src="./Pictures/add1.png" alt="add1" style="zoom: 50%;" />

```
sub sp,#12		<- stack pointer - 12를 한 이유는 원래 저장되어 있던 메모리 값에서 그대로 사용하면 이전
				<- 에 사용되던 메모리 안에 있는 값들이 사라질 수 있기 때문이다. 
add r7, sp, #0	<- sp - 12 한 공간의 주소를 r7에 저장한다. 
movs r3, #5		<- movs는 immediate value를 해당 destination register r3에 쓰는 것이다. 
```

arm에는 32,64bit architecture가 있다. 32bit 아키텍쳐는 legacy와 cortex로 나뉘는데 우리가 쓰는 아키텍처 버전은 ARMv7E-M, 즉 코어가 Cortex-M4이다. 현재 Thumb모드를 사용 중이다. 

![movs](/home/dongjun/mygit/2021_1_EmbeddedSystemDesignLab/WEEK5/Pictures/movs.png)



movs r3, #5 -> 0010 0 011 0000 0101(0x2305) 메모리에 적재 될땐, ARM은 little-endian 방식으로 저장되니  LSB부터 저장된다. 1바이트씩 적재 되니 05 23으로 적재된다. 그림과 같다는 걸 볼 수 있다.  그래서 register r3에 5가 저장되었다. 

<img src="./Pictures/movs21.png" alt="movs21" style="zoom:50%;" />

```
strb r3, [r7, #7]	<- 이 명령어를 통해 r3의 값을 r7가 가지고 있는 주소값 +7
movs r3, #21		<- 이 명령어를 통해 r3의 레지스터 값 15로 변경, r3의 값을 메모리에 올렸으니 P1의 값						 을 저장하기 위해 movs r3, #21
```

Stack은 Thumb Mode 16 bit이기 때문에  어셈블리어 한 줄당 2바이트라고 생각하면 된다. 

pc는 실행할 어셈블리어의 주소를 가르킨다. 



<img src="./Pictures/ldrbop.png" alt="ldrbop" style="zoom:50%;" />

```
strb r3, [r7, #6]		<- r7 + 6 주소에 현재 r3에 있는 값 0x21를 넣는다. 
```

![STRB(immediate)](./Pictures/STRB(immediate).png)

0111 0001 1011 1011 -> 0x 71bb, Little Endian 방식으로 저장되니 bb 71



<img src="./Pictures/ldrbr2r3.png" alt="ldrbr2r3" style="zoom:50%;" />

메모리에 적재되어 있던 값을 레지스터에 옮겨주었다.

<img src="./Pictures/strbr3.png" alt="strbr3" style="zoom:50%;" />

```
add r3, r2
strb r3, [r7, #5]			<- add r3 r2한 것을 메모리 0xffffffc5번지에 저장해줬다.
```

![addregister](./Pictures/addregister.png)

0100 0100 0001 0101 -> 0x 4413 -> 13 44 형태로 저장된다. 여기서 DN은 0이다. floating Number가 아니기 때문에. (DN 질문하기)



#### 2. Sub, if else, for, call

**main.c**

```
int sub(int a, int b);

int main(){
    int P0 = 0x10;    //char 선언 
    int P1 = 0x30;
    int i;
    // clear
    
    for (i=0; i<5; i++)
    {
        if (P1 == 0x0) break;
        else P1 = sub(P1, P0);
    }
    //POHW_ADDR = 0x4F;
    
	while(1);
}

int sub(int a, int b) {
    return a-b;
}
```



<img src="./Pictures/Total1.png" alt="Total1" style="zoom:50%;" />

**R14** : Link Register**(LR)**은 함수 호출하고 돌아올 주소를 저장해 놓은 레지스터이다. 

**MSP(Main Stack Pointer)** : 뭔지 모르겠다. 

**CPSR(Current Program Status Register)** : 연산결과, IRQ, FIQ금지, 동작모드 등을 저장	

**LR(Link Register) : ** 함수 호출시 되돌아갈 함수의 주소 저장 

**FAULTMASK :** ??

```
push {r7, lr}
sub sp, #16				<- sp = sp -16
add r7, sp, #0			<- r7 = sp
```



<img src="./Pictures/movandstr.png" alt="movandstr" style="zoom:50%;" />

```
0x0800019a 10 23 main+6  movs	r3, #16
0x0800019c bb 60 main+8  str	r3, [r7, #8]
0x0800019e 30 23 main+10 movs	r3, #48	; 0x30
0x080001a0 7b 60 main+12 str	r3, [r7, #4]
```

movs와 str를 통해 메모리에 적재하였다. 



<img src="./Pictures/beforeif.png" alt="beforeif" style="zoom:50%;" />

```
   0x080001a2 <+14>:	movs	r3, #0			<-movs 명령어를 통해 r3에 0을 저장해놨고
   0x080001a4 <+16>:	str	r3, [r7, #12]		<-store 명령어를 통해 저장을 하고,
=> 0x080001a6 <+18>:	b.n	0x80001be <main+42> <- branch문을 통해 ldr 명령어로 이동
   0x080001be <+42>:	ldr	r3, [r7, #12]
```



<img src="./Pictures/branch ldrr3.png" alt="branch ldrr3" style="zoom: 50%;" />

pc값이 jump한 주소로 바꼈다는 것을 확인 할 수 있고 ldr를 통해 메모리에 있는 값을 r3에 들고 왔다. 

<img src="./Pictures/cmpr3,4.png" alt="cmpr3,4" style="zoom:50%;" />

```
cmp r3, #4 <- 0 - 4 = -4 0보다 작으니 flag가 -1?로 setting된다. 
```

![cmp immediate opcode](./Pictures/cmp immediate opcode.png)

0010 1011 0000 0100 -> 0x2b04  -> little endian 방식이니 04 2b

cmp 부분에서 i<5보다 작기 때문이고 flag값으로 인해 ble.n 0x80001a8<main+20>로 이동하여 if문을 실행한다.



<img src="./Pictures/next.png" alt="next" style="zoom:50%;" />

 if문이 돌아가는 초입부이다. 일단 r3에 r7 #12에 있는 0x30을 들고 온다. 



<img src="./Pictures/beq.png" alt="beq" style="zoom:50%;" />

```
cmp r3, #0					<- r3과 0이랑 같은지 확인
beq.n 0x80001c6 <main+50>	<- r3와 0이 같지 않기 때문에 다음 명령어로 이동.
```



<img src="./Pictures/bl.png" alt="bl" style="zoom:50%;" />

else 부분에 있는 sub함수로 branch한다.  

![bl opcode](./Pictures/bl opcode.png)

이 명령어에 대해서는 opcode를 어떻게 해석해야 할지 모르겠다. Indirect 인지 direct address jump인지 모르겠다. 

금요일에 물어봐야 겠다. 

<img src="./Pictures/subfunction.png" alt="subfunction" style="zoom:50%;" />

sub함수로 들어왔다. push r7을 통해 원래 r7에 있는 값을 stack에 미리 옮겨 놓았다. 

lr 0x080001b7로 저장이 되었는데 다시 돌아가야 하는 주소는 0x080001b6인데 왜 7로 된건지 이해가 가지 않는다. (질문 해야함!)



<img src="./Pictures/SPandMSP.png" alt="SPandMSP" style="zoom:50%;" />

 sp와 MSP가 변경된 것을 알 수 있다. 왜냐하면 sp - 12 하였기 때문이다. 

근데 원래 스택 포인터가 0xffffffe8이였는데 0xffffffd8, 0xe8-0xd8 = 0x10인데 왜??



<img src="./Pictures/subregisterstore.png" alt="subregisterstore" style="zoom:50%;" />

```
0x080001d0 78 60 sub+6  str	r0, [r7, #4]
0x080001d2 39 60 sub+8  str	r1, [r7, #0]

0xffffffd8 10 00 00 00 30 00 00 00 00 00 00 00 e8 ff ff ff ....0...........
```



<img src="./Pictures/subregisterload.png" alt="subregisterload" style="zoom:50%;" />

```
0x080001d4 7a 68 sub+10 ldr	r2, [r7, #4]
0x080001d6 3b 68 sub+12 ldr	r3, [r7, #0]

r2 0x00000030         r3 0x00000010 
```



<img src="./Pictures/returna.png" alt="returna" style="zoom:50%;" />

```
0x080001da 18 46       sub+16 mov	r0, r3		<- r3값을 r0으로 옮겨준다. 왜냐하면 앞에서 a값을 필요로 하기 때문이다. 
0x080001dc 0c 37       sub+18 adds	r7, #12		<- sp+12를 통해 sp 복구하기 위해 r7 + 12
0x080001de bd 46       sub+20 mov	sp, r7		<- mov sp r7를 통해 원래 sp로 복구
					

```



<img src="./Pictures/movsp.png" alt="movsp" style="zoom:50%;" />

sp를 원래 있던 곳으로 복구하기 위해 +12해줬다. 근데 왜 0xffffffe4인가? e8이 아니라???

-조교님께 물어봐야될 것.



<img src="./Pictures/stackpointer+4.png" alt="stackpointer+4" style="zoom:50%;" />

```
ldr.w r7, [sp], #4										opcode :f85d 7b04
bx lr <-이것을 통해 lr주소로 다시 돌아간다. b6으로 돌아간다. 	 opcode : 4770 
```

![ldrb opcode](./Pictures/ldrb opcode.png)

![BX opcode](./Pictures/BX opcode.png)위의 명령어를 통해 sp값을 e8로 복구하였다. 근데 왜 add로 e8까지 안 올리고 ldr.w(w는 word로 32bit)로 하였는지 모르겠다. (조교님께 물어볼 것.)



<img src="./Pictures/strsubfunctionresult.png" alt="strsubfunctionresult" style="zoom:50%;" />

```
str r0, [r7, #0]		<- 명령어를 통해 return a-b된 값을 메모리에 적재한다. 
						<- 그리고 다시 for문을 진행 한다. 
```



<img src="./Pictures/endofdebugging.png" alt="endofdebugging" style="zoom:50%;" />

```
0x080001aa <+22>:	cmp	r3, #0						<- r3번에 값이 0이 되어서 
0x080001ac <+24>:	beq.n	0x80001c6 <main+50>		<- beq 실행되면서 main+50번으로 이동.
0x080001c6 <+50>:	nop							   <- 짧은 딜레이를 주기 위해 no operation 넣음
=> 0x080001c8 <+52>:	b.n	0x80001c8 <main+52>		<- 메인문의 끝.

```

여기서 beq.n, beq뒤에 붙은 .n은 mnemonic(연상 기호)이다. 

```
.n = 16-bit Thumb ("narrow") encoding
.w = 32-bit Thumb-2 ("wide") encoding
```







교수님 Tip

```
cpu에 있는 cpsr, MSP 이런거는 그냥 한번 봐주고 넘어가는거지 cpu 내부는 너무 디테일 하게 보지 마라. 어느정도 눈에만 익혀놔라. cpu가 이렇게 해석하라는거. branch하고 jump call를 중점적으로 봐야한다. array도 해봐라. pointer 연산 피지컬하게 볼 수 있다. array할 때 메모리 보기. 왜 function call 할때 pointer만 넘기는가? 

function call 되면 새로운 new local 변수가 생긴다. 독자적인 세상이라. CPU에는 그런 개념이 없다. 어떻게 돌아가는지 확인 해라. 몰라도 되지만 한번은 알고 가야한다. 기계가 해석하는 관점에서 보면 최적화를 할 수 있기 때문에. 기계 코드로 생각할 수 있게 해야 한다. 

for (~ i<100; i++) cmp branch clock수가 제일 많다. for문 진짜 오래 걸리긴 하더라.
pipeline이 stoll된다. cmp만나게 되면 느려진다. 
그럼 for (i<25로 줄이고)
 a[0]
 a[4]
 
안에 있는 명령어 수를 늘리면 된다. branch를 100번 했던걸 25로 줄이고 내부 코드를 늘리면 된다. 
단점은 코드가 길어진다. 장점은 branch cmp 

loop unrolling , 
code
	spill 
	flush - 15개 레지스터 17개 레지스터사용해야하면
?
struct도 짜보기 <- align 맞추는것도 알아야하고 width를 다 맞춰놓으면 빨라진다. 


c코드 짤 때 잘 생각 하면서 짜야한다. 그래서 이런 과제를 냈구나.

ram에 있는거 레지스터올리고 (시간 좀 씀), 


```












