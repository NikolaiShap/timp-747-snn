#include <stdio.h>
#include<stdlib.h>

struct node {
 	int value;
	struct node *next;
	struct node *prev;
} node;

struct listx2{		
	struct node* first;
	struct node* last;	
} listx2;

int isEmpty(struct listx2* spisok)
{
	return spisok->first==NULL && spisok->last==NULL;
}

struct node* find(struct listx2* spisok,int k)
{
	struct node *tmp=spisok->first;
	while(tmp->value!=k){
		if(tmp->next!=NULL){
			tmp=tmp->next;
		}else{
			return 0;
		}
	}
	return tmp;
}

struct node* find_invers(struct listx2* spisok,int k)
{
	struct node *tmp=spisok->last;
	while(tmp->value!=k){
		if(tmp->prev!=NULL){
			tmp=tmp->prev;
		}else{
			return 0;
		}
	}
	return tmp;
}

void init(struct listx2* spisok,int value)
{
	struct node* tmp;
	tmp = (struct node*)malloc(sizeof(struct node));
	tmp->value=value;
	tmp->next=NULL;
	tmp->prev=NULL;
	spisok->first = tmp;
	spisok->last = tmp;
}

int push_back(struct listx2* spisok, int x)
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct node *tmp = (struct node*)malloc(sizeof(struct node));
		tmp->value=x;
		tmp->prev=spisok->last;
		tmp->next=NULL;
		spisok->last=tmp;
		tmp->prev->next=tmp;
	}
	return 0;
}

int push_front(struct listx2* spisok,int x) 
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
        struct node *tmp = (struct node*)malloc(sizeof(struct node));
		tmp->value=x;
		tmp->prev=NULL;
		tmp->next=spisok->first;
		spisok->first=tmp;
		tmp->next->prev=tmp;
	}
	return 0;
}

int clear(struct listx2* spisok)
{
	if(isEmpty(spisok)==1)
	{
		struct node *tmp=spisok->first;
		struct node *temp=NULL;
		while(tmp!=NULL)
		{
			temp=tmp->next;
			free(tmp);
			tmp=temp;
		}
		spisok->first=NULL;
		spisok->last=NULL;
	}
}

void _remove(struct listx2* spisok, struct node *tmp){
	if(tmp!=NULL){
		if (tmp==spisok->first && tmp==spisok->last) {
			clear(spisok);
			return;
		}
		if (tmp==spisok->first)
		{
			spisok->first=tmp->next;
			tmp->next->prev=NULL;
		}
		else if(tmp==spisok->last)
		{
			spisok->last=tmp->prev;
			tmp->prev->next=NULL;
		}
		else if (tmp!=spisok->first && tmp!=spisok->last)
		{
			tmp->next->prev=tmp->prev;
			tmp->prev->next=tmp->next;
		}
		free(tmp);
	}
}

int removeLast(struct listx2* spisok,int x)
{
	struct node* element = find_invers(spisok,x);
	if (element!=NULL){
		_remove(spisok,element);
		return 0;
	}
	return -1;
}

int removeFirst(struct listx2* spisok, int x)
{
	struct node* element = find(spisok,x);
	if (element!=NULL){
		_remove(spisok,element);
		return 0;
	}
	return -1;
}

int insertAfter	(struct listx2* spisok,int num, int data)
{
	struct node* tmp = spisok->first;
	for (int i = 1;i<num;i++)
	{
		tmp=tmp->next;
		if(tmp==NULL) 
			return -1;
	}
	struct node *temp = malloc(sizeof(node));
	temp->value=data;
	temp->next=tmp->next;
	temp->prev=tmp;
	tmp->next->prev=temp;
	tmp->next=temp;  
	return 0;   
}

int insertBefore(struct listx2* spisok,int num, int data)
{
	struct node* tmp = spisok->first;
	for (int i = 1;i<num;i++)
	{
		tmp=tmp->next;
		if(tmp==NULL) 
			return -1;
	}
	struct node *temp = malloc(sizeof(node));
	temp->value=data;
	temp->prev=tmp->prev;
	temp->next=tmp;
	tmp->prev=temp;
	temp->prev->next=temp;      
	return 0; 
}

void print(struct listx2* spisok)
{
	struct node* tmp=spisok->first;
	while(tmp->next!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->next;
	}
	printf("%d\n", tmp->value);
}

void print_invers(struct listx2* spisok)
{
	struct node* tmp=spisok->last;
	while(tmp->prev!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->prev;
	}
	printf("%d\n", tmp->value);	
}



int main()
{
	int n,a;
	struct listx2* struc=(struct listx2*)malloc(sizeof(struct listx2));	
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a);
		push_back(struc,a);
	}
	print(struc);
	
	int k[3];
        scanf("%d%d%d",&k[0],&k[1],&k[2]);
	for(int i=0;i<3;i++){
		if(find(struc,k[i])!=NULL)
			printf("1 ");
		else
			printf("0 ");
	}
	printf("\n");

	int m;
	scanf("%d",&m);
	push_back(struc,m);
	print_invers(struc);

	int t;
	scanf("%d",&t);
	push_front(struc,t);
	print(struc);

	int j,x;
	scanf("%d%d",&j,&x);
	insertAfter(struc,j,x);
	print_invers(struc);

	int u,y;
	scanf("%d%d",&u,&y);
	insertBefore(struc,u,y);
	print(struc);
	int z;
	scanf("%d",&z);
	removeFirst(struc,z);
	print_invers(struc);
	int r;
	scanf("%d",&r);
	removeLast(struc,r);
	print(struc);

	clear(struc);
	return 0;
}
