#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"


int main(void){

	//QUEUE
	Queue();
	//Stack
	Stack();
	

	//LinkedList
		
	printf("---------------------This is Linkedlist Operation-------------------------\n\n");
	int i = 0;
	int mode[2];

	struct Node *head = malloc(sizeof(struct Node));

	struct Node *node1 = malloc(sizeof(struct Node));
	head->next = node1;

	node1->data = 10;

	struct Node *node2 = malloc(sizeof(struct Node));
	node1->next = node2;

	node2->data = 20;

	struct Node *node3 = malloc(sizeof(struct Node));
	node2->next = node3;

	node3->data = 30;
	node3->next = NULL;
	
	mode[1] = mode_select();
	
	if (mode[1] == 1)
	{
		insert(head, 100);
	}

	if (mode[2] == 1)
	{
		delete(node1);
	}
	//Debug whether insertNode is done correctly
	//printf("%d\n", insertNode->data);
	
	struct Node *curr = head->next;
	while (curr != NULL)
	{
		i++;
		printf("node%d data = %d\n",i, curr->data);
		curr = curr->next;
	}
	
	free(node2);
	free(node1);
	free(head);
	return 0;
}
