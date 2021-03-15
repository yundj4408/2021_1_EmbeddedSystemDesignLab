struct Node {
	struct Node *next;
	int data;
};
struct Node* insert(struct Node *target, int data);
void delete(struct Node *target);
int mode_select();

