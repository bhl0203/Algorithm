#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push_();
void pop_();
void size_();
int empty_();
void front_();
void back_();

typedef struct q* ptr;

typedef struct q {
	int n;
	ptr next;
}q;
ptr head;
ptr tail;

int s = 0;
void push_() {
	int n;
	scanf("%d", &n);
	ptr tmp;
	tmp = (ptr)malloc(sizeof(q));
	tmp->n = n;
	tmp->next = NULL;
	if (head == NULL) {
		head = (ptr)(malloc)(sizeof(q));
		head = tmp;
		tail = tmp;
	}
	else {
		tail->next = tmp;
		tail = tmp;
	}
	s++;
}
void front_() {
	if (empty_() == 1) {
		printf("-1\n");
	}
	else printf("%d\n", head->n);
}
void back_() {
	if (empty_() == 1) {
		printf("-1\n");
	}
	else printf("%d\n", tail->n);
}
void size_() {
	printf("%d\n", s);
}
int empty_() {
	if (s == 0) return 1;
	return 0;
}
void pop_() {
	if (empty_() == 1) {
		printf("-1\n");
		return;
	}
	ptr tmp;
	tmp = head;
	printf("%d\n",tmp->n);
	head = head->next;
	free(tmp);
	s--;
}


int main() {
	char c[10];
	int n;
	scanf("%d", &n);
	tail = head;
	for (int i = 0; i < n; i++) {
		memset(c, '\0', 10);
		scanf("%s", c);
		if (strcmp(c, "push") == 0) push_();
		if (strcmp(c, "pop") == 0) pop_();
		if (strcmp(c, "size") == 0) size_();
		if (strcmp(c, "empty") == 0) printf("%d\n", empty_());
		if (strcmp(c, "front") == 0) front_();
		if (strcmp(c, "back") == 0) back_();
	}

	return 0;
}