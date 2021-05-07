# WEEK7

Computer로 Processor가 동작하는 것을 확인하기 위해선 다음과 같은 순서를 따라야 한다. 

![Debugging](./Pictures/Debugging.png)

1. Cross Compilation
   - Code Memory에 넣어야 하는 object file를 Compile를 통해 만들어 준다. 
   - 코드에서 int a[100]를 선언하면 Code memory 공간에 자리를 잡는 것이 아닌 Stack, 즉 Data Memory에 100개 정도의 word자리를 만들어 주는 것이다.
2. Programming
   - object file을 첫번째 단계를 통해 만든 후 Processor의 Code Space에 적재
3. Debugging
4. Communication