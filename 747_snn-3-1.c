#include <stdio.h>
#include<stdlib.h>

struct TaskNode {
	int TmpValue;
	struct TaskNode* next;
} TaskNode;

struct queue {
	struct TaskNode* one;
} queue;

int isEmpty(struct queue* struc)
{
	return struc->one == NULL;
}

struct TaskNode* find(struct queue* struc, int TmpValue)
{
	struct TaskNode* q = struc->one;
	while (q->TmpValue != TmpValue) {
		if (q->next != NULL)
			q = q->next;
		else
			return 0;
	}
	return q;
}

void init(struct queue* struc, int value)
{
	struct TaskNode* x;
	x = (struct TaskNode*)malloc(sizeof(struct TaskNode));
	x->TmpValue = value;
	x->next = NULL;
	struc->one = x;
}

int push_back(struct queue* struc, int x)
{
	if (isEmpty(struc) == 1)
		init(struc, x);
	else
	{
		struct TaskNode* TempStruct = (struct TaskNode*)malloc(sizeof(struct TaskNode));
		TempStruct->TmpValue = x;
		TempStruct->next = NULL;
		struct TaskNode* temp = struc->one;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = TempStruct;
	}
	return 0;
}

int push_front(struct queue* struc, int x)
{
	if (isEmpty(struc) == 1)
		init(struc, x);
	else
	{
		struct TaskNode* tmp = (struct TaskNode*)malloc(sizeof(struct TaskNode));
		tmp->TmpValue = x;
		tmp->next = struc->one;
		struc->one = tmp;
	}
	return 0;
}

int clear(struct queue* struc)
{
	if (isEmpty(struc) == 1)
	{
		struct TaskNode* tmp = struc->one;
		struct TaskNode* temp = NULL;
		while (tmp != NULL)
		{
			temp = tmp->next;
			free(tmp);
			tmp = temp;
		}
		struc->one = NULL;
	}
}

void _remove(struct queue* struc, struct TaskNode* tmp) {
	if (tmp != NULL) {
		if (tmp == struc->one)
			struc->one = tmp->next;
		else
		{
			struct TaskNode* temp = (struct TaskNode*)malloc(sizeof(struct TaskNode));
			temp = struc->one;
			while (temp->next != tmp)
				temp = temp->next;
			temp->next = tmp->next;
		}
		free(tmp);
	}
}

int removeFirst(struct queue* struc, int x)
{
	struct TaskNode* tmp = find(struc, x);
	if (tmp != NULL) {
		_remove(struc, tmp);
		return 0;
	}
	return -1;
}

int insertAfter(struct queue* struc, int num, int value)
{
	struct TaskNode* temp = malloc(sizeof(TaskNode));
	temp->TmpValue = value;

	struct TaskNode* tmp = struc->one;
	struct TaskNode* prev_tmp = struc->one;

	for (int i = 1; i < num + 1; i++)
	{
		prev_tmp = tmp;
		tmp = tmp->next;
		if (tmp == NULL)
			return -1;
	}
	prev_tmp->next = temp;
	temp->next = tmp;
	return 0;
}

void print(struct queue* struc)
{
	struct TaskNode* tmp = struc->one;
	while (tmp->next != NULL)
	{
		printf("%d ", tmp->TmpValue);
		tmp = tmp->next;
	}
	printf("%d\n", tmp->TmpValue);
}

int main()
{
	int n, a;
	struct queue* list = (struct queue*)malloc(sizeof(struct queue));
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a);
		push_back(list, a);
	}
	print(list);

	int k[3];
	scanf("%d%d%d", &k[0], &k[1], &k[2]);
	for (int i = 0; i < 3; i++) {
		if (find(list, k[i]) != NULL)
			printf("1 ");
		else
			printf("0 ");
	}
	printf("\n");

	int m;
	scanf("%d", &m);
	push_back(list, m);
	print(list);

	int t;
	scanf("%d", &t);
	push_front(list, t);
	print(list);

	int j, x;
	scanf("%d%d", &j, &x);
	insertAfter(list, j, x);
	print(list);

	int z;
	scanf("%d", &z);
	removeFirst(list, z);
	print(list);

	clear(list);
	return 0;
}
