#include <stdio.h>
#include <stdlib.h>

typedef struct ll {
	int element;
	struct ll* next;
}ll;

ll* ll_reorder(ll* head, int size) {
	ll** arr;
	ll* cur = head;
	int i;
	int front = 0;
	int rear = size - 1;

	arr = (ll**)malloc(sizeof(ll*) * size);
	for(i = 0; i < size; i++) {
		arr[i] = cur;
		cur = cur->next;
	}

	while(front < rear) {
		arr[front]->next = arr[rear];
		arr[rear]->next = arr[front+1];

		front++;
		rear--;
	}
	arr[front]->next = NULL;

	return head;
}

int main(int argc, char* argv[]) {
	int size = 0;
	int elmt;
	ll *prev, *cur, *head;
	FILE *ifp, *ofp;

	if(argc < 2) return -1;
	ifp = fopen(argv[1], "r");
	ofp = fopen("result", "w");

	fscanf(ifp, "%d", &elmt);
	cur = (ll*)malloc(sizeof(ll));
	cur->element = elmt;
	prev = cur;
	head = cur;
	size++;
	while(fscanf(ifp, "%d", &elmt) != EOF) {
		cur = (ll*)malloc(sizeof(ll));
		cur->element = elmt;
		cur->next = NULL;
		prev->next = cur;
		prev = cur;
		size++;
	}

	cur = ll_reorder(head, size);

	while(cur != NULL) {
		fprintf(ofp, "%d ", cur->element);
		cur = cur->next;
	}
	fprintf(ofp, "\n");

	fclose(ifp);
	fclose(ofp);

	return 0;
}
