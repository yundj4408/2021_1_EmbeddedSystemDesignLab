## WEEK5

![store](/home/dongjun/Pictures/store.png)

movs r3, #149 레지스터에 올려주고

strb r3, [r7, #7] 현재 스택포인터와 같다.  r3의 값을 r7레지스터 주소값의 7번지 밑에 내려가서 넣어줘라. 그러면 [,]

현재 c코드 한줄 -> Instruction 2개 

n를 누르면 그래서 Instruction 2개로 넘어가버리니

si를 누르면 Instruction 1개 넘어간다. (step instruction)



![image-20210401150758568](/home/dongjun/.config/Typora/typora-user-images/image-20210401150758568.png)

db memory watch 0x ffff ffff 0![95in7](/home/dongjun/Pictures/95in7.png)

7번지에 95가 들어갔는걸 확인 할 수 있다. ![85changed](/home/dongjun/Pictures/85changed.png)

코드가 끝났을 때 메모리 7번지에 잇던 0x95 -> 0x85로 바뀐거 알 수 있다. 