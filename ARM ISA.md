## ARM ISA

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

  ![ARMCore](/home/dongjun/mygit/2021_1_EmbeddedSystemDesignLab/WEEK5/Pictures/ARMCore.png)

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
    ![32bitARMISA](/home/dongjun/mygit/2021_1_EmbeddedSystemDesignLab/WEEK5/Pictures/32bitARMISA.png)

  - ARM 64bit의 Instruction Set

    ![64bitARMISA](/home/dongjun/mygit/2021_1_EmbeddedSystemDesignLab/WEEK5/Pictures/64bitARMISA.png)
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











https://kyuhyuk.kr/article/simple-arm-operating-system/2019/03/04/Simple-ARM-Operating-System-Chapter-2 참고해서 정리











