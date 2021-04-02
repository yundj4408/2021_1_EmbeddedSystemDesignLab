#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"



struct Node* insert(struct Node *target, int data){
	struct Node *newNode = malloc(sizeof(struct Node));
	newNode->next = target->next;
	newNode->data = data;

	target->next = newNode;

	//Debug
	//printf("%d", newNode->data);

	return newNode;
}

void delete(struct Node *target) {
	struct Node *removeNode = target->next;
	target->next = removeNode->next;


}

int mode_select() {
	int mode[2];
	printf("Select your mode, insert(0), delete(1) : ");
	scanf("%d", &mode[0]);

	if (mode[0] == 0) {
		printf("Selection Insertion Mode (1. On the Head 2. After normal Node, 3. At the Last) : ");
		scanf("%d", &mode[1]);	//mode[1] is Insertion Mode
	}

	if (mode[0] == 1) {
		printf("Selection Delete Mode (1. On t:he Head 2. After normal Node, 3. At the Last) : ");
		scanf("%d", &mode[2]);
	}

	return mode[1];

}




