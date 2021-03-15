#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

#define MAX_STACK_SIZE 100
//stack LIFO Structure

int stack[MAX_STACK_SIZE];
int top = -1;

int Empty(){
	if(top<0)
		return true;
	else
		return false;
}

int Full(){
	if(top>=MAX_STACK_SIZE-1)
		return true;
	else
		return false;
}

void push(int value){
	if(Full()==true)
		printf("Stack is Full");
	else
		stack[++top] = value;
}

int pop(){
	if(Empty()==true)
		printf("Stack is Empty.\n");
	else
		return stack[top--];
}

void Stack(){

	printf("---------------------This is Stack Operation-------------------------\n");
	push(3);
	push(5);
	push(12);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	pop();
}

