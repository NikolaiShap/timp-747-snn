#include <stdio.h>
#include <stdlib.h>

typedef struct TaskNode
{
	int significance;
	struct TaskNode* LeftLeaves;
	struct TaskNode* RightLeaves;
	struct TaskNode* Root_;
} TaskNode;

typedef struct TreeNode
{
	struct TaskNode* root;
	int count;
} TreeNode;

typedef struct QueueNode
{
	TaskNode* need;
	struct QueueNode* following;
}QueueNode;

typedef struct ListNode
{
	QueueNode* first;
	QueueNode* last;
}List;

void createlist(List* q)
{
	q->first = NULL;
	q->last = NULL;
};

int push(List* q, TaskNode* n)
{
	QueueNode* newList = (QueueNode*)malloc(sizeof(QueueNode));
	newList->need = n;
	newList->following = NULL;
	if (q->first)
		q->last->following = newList;
	else
		q->first = newList;
	q->last = newList;
	return 0;
}

void clearlist(List* TmpList)
{
	QueueNode* TmpNode, * nq;
	TmpNode = TmpList->first;
	do
	{
		nq = TmpNode;
		TmpNode = TmpNode->following;
		free(nq);
	} while (TmpNode);
	TmpList->first = NULL;
	TmpList->last = NULL;
}

void init(TreeNode* TmpTree) {

	TmpTree->root = NULL;
}

void clear(TreeNode* tree) {
	while (tree->root != NULL)
		RemoveMin(tree->root, tree);
}

int insert(TreeNode * tree, int value) {
	TaskNode* TempNode = (TaskNode*)malloc(sizeof(TaskNode));

	TempNode->significance = value;


	if (tree->root == NULL) {
		TempNode->LeftLeaves = TempNode->RightLeaves = NULL;
		TempNode->Root_ = NULL;
		tree->root = TempNode;
		tree->count = 1;
		return 0;
	}

	if (TempNode->significance == tree->root->significance)
		return -1;

	TaskNode * root2 = (TaskNode*)malloc(sizeof(TaskNode)), *root3 = NULL;

	root2 = tree->root;

	while (root2 != NULL)
	{
		root3 = root2;
		if (value < root2->significance)
			root2 = root2->LeftLeaves;
		else
			root2 = root2->RightLeaves;
	}

	if (TempNode->significance == root3->significance) {
		return -1;
	}

	TempNode->Root_ = root3;
	TempNode->LeftLeaves = NULL;
	TempNode->RightLeaves = NULL;

	if (value < root3->significance)
		root3->LeftLeaves = TempNode;
	else
		root3->RightLeaves = TempNode;
	tree->count++;
	return 0;
}

int RemoveMin(TaskNode * n, TreeNode * TmpTree) {
	TmpTree->count--;

	if (TmpTree->count != 1) {

		while (n->LeftLeaves != NULL)
			n = n->LeftLeaves;

		if (n->RightLeaves != NULL) {
			n->RightLeaves->Root_ = n->Root_;

			if (n == TmpTree->root)
				TmpTree->root = n->RightLeaves;
			else
				n->Root_->LeftLeaves = n->RightLeaves;
		}
		else
			n->Root_->LeftLeaves = NULL;

		int value = n->significance;
		free(n);

		return value;
	}
	else {
		TmpTree->root = NULL;
		TmpTree->count = 0;
		free(TmpTree->root);

		return 0;
	}
}

TaskNode* search(TaskNode * TmpNode, int value) {
	if ((TmpNode == NULL) || (TmpNode->significance == value))
		return TmpNode;
	if (value < TmpNode->significance)
		return search(TmpNode->LeftLeaves, value);
	else
		return search(TmpNode->RightLeaves, value);
}

TaskNode * min(TaskNode * root) {
	TaskNode* TmpNode = root;
	while (TmpNode->LeftLeaves != NULL)
		TmpNode = TmpNode->LeftLeaves;
	return TmpNode;
}

int findBaseNode(TreeNode * tree, int value, TaskNode * *node) {
	TaskNode* itNeedAble, * root2;
	root2 = tree->root;
	itNeedAble = search(root2, value);
	if (itNeedAble == NULL) {
		return 1;
	}

	*node = itNeedAble;
	return 0;
}


int rotateLeft(TreeNode * tree) {
	TaskNode* itNeedAble = tree->root->RightLeaves;

	if (itNeedAble == NULL)
		return 1;

	tree->root->RightLeaves = itNeedAble->LeftLeaves;
	itNeedAble->LeftLeaves = tree->root;
	itNeedAble->Root_ = tree->root->Root_;
	tree->root->Root_ = itNeedAble;
	tree->root = itNeedAble;

	return 0;
}

int rotateRight(TreeNode * tree) {
	TaskNode* itNeedAble = tree->root->LeftLeaves;

	if (itNeedAble == NULL)
		return 1;

	tree->root->LeftLeaves = itNeedAble->RightLeaves;
	itNeedAble->RightLeaves = tree->root;
	itNeedAble->Root_ = tree->root->Root_;
	tree->root->Root_ = itNeedAble;
	tree->root = itNeedAble;

	return 0;
}

void print(TaskNode * node)
{
	if (node)
	{
		List list1, list2;
		List* TmpList1 = &list1;
		List* TmpList2 = &list2;
		createlist(TmpList1);
		createlist(TmpList2);
		TaskNode* TmpNode = NULL;
		QueueNode* q = NULL;
		int c = 0, val = node->significance, j = 0;
		TaskNode* l = node->LeftLeaves;
		TaskNode* r = node->RightLeaves;
		push(TmpList1, node);
		while (1)
		{
			while (TmpList1->first)
			{
				if (TmpList1->first)
				{
					QueueNode* nodelist_pop;
					TmpNode = TmpList1->first->need;
					nodelist_pop = TmpList1->first;
					TmpList1->first = TmpList1->first->following;
					if (TmpList1->first == NULL)
						TmpList1->last = NULL;
					free(nodelist_pop);
				}
				else
					TmpNode = NULL;
				if (TmpList1->first == NULL)
				{
					if (TmpNode->significance == val && c == 1)
						printf("_\n");
					else
						printf("%d\n", TmpNode->significance);
				}
				else if (TmpNode->significance == val && c == 1)
					printf("_ ");
				else
					printf("%d ", TmpNode->significance);
				if (TmpNode->LeftLeaves)
					push(TmpList2, TmpNode->LeftLeaves);
				else
					push(TmpList2, node);
				if (TmpNode->RightLeaves)
					push(TmpList2, TmpNode->RightLeaves);
				else
					push(TmpList2, node);
			}
			node->LeftLeaves = node->RightLeaves = NULL;
			c = 1;
			q = TmpList2->first;
			while (TmpList2->first->need->significance == val)
			{
				TmpList2->first = TmpList2->first->following;
				if (TmpList2->first->following == NULL)
					if (TmpList2->first->need->significance == val)
					{
						j = 1;
						node->LeftLeaves = l;
						node->RightLeaves = r;
						clearlist(TmpList2);
						break;
					}
			}
			TmpList2->first = q;
			if (j == 1)
				break;
			TmpList1->first = TmpList2->first;
			TmpList1->last = TmpList2->last;
			TmpList2->first = NULL;
			TmpList2->last = NULL;
		}
	}
	else
		printf("-\n");
}

void printTree(TreeNode * tree) {
	print(tree->root);

}

TaskNode* _Remove(TaskNode * TmpTree, int value)
{
	TaskNode* temp;
	if (!TmpTree) {
		return TmpTree;
	}
	else if (value < TmpTree->significance) {
		TmpTree->LeftLeaves = _Remove(TmpTree->LeftLeaves, value);
	}
	else if (value > TmpTree->significance) {
		TmpTree->RightLeaves = _Remove(TmpTree->RightLeaves, value);
	}
	else {
		if (TmpTree->LeftLeaves && TmpTree->RightLeaves) {
			temp = min(TmpTree->RightLeaves);
			temp->LeftLeaves = TmpTree->LeftLeaves;
			temp = TmpTree->RightLeaves;
			free(TmpTree);
			return temp;
		}
		else if (TmpTree->LeftLeaves == TmpTree->RightLeaves) {
			free(TmpTree);
			return NULL;
		}
		else {
			if (!TmpTree->LeftLeaves) temp = TmpTree->RightLeaves;
			else temp = TmpTree->LeftLeaves;
			free(TmpTree);
			return temp;
		}
	}
	return TmpTree;
}

int Remove(TreeNode * TmpTree, int value) {
	TaskNode* itNeedAble = _Remove(TmpTree->root, value);
	if (!itNeedAble)
		return 1;
	else {
		TmpTree->count--;
		TmpTree->root = itNeedAble;
		return 0;
	}
}


int main() {
	TreeNode* tree = (TreeNode*)malloc(sizeof(TaskNode));
	init(tree);

	int a[4];
	scanf("%d%d%d%d", &a[0], &a[1], &a[2], &a[3]);
	for (int i = 0; i < 4; i++)
		insert(tree, a[i]);

	print(tree->root);

	scanf("%d%d%d", &a[0], &a[1], &a[2]);
	for (int i = 0; i < 3; i++)
		insert(tree, a[i]);

	print(tree->root);

	int m;

	scanf("%d", &m);

	TaskNode * TreeNode = (TaskNode*)malloc(sizeof(TaskNode));

	if (findBaseNode(tree, m, &TreeNode) == 1)
		printf("-\n");
	else {
		if (TreeNode->Root_ == NULL)
			printf("_ ");
		else
			printf("%d ", TreeNode->Root_->significance);

		if (TreeNode->LeftLeaves == NULL)
			printf("_ ");
		else
			printf("%d ", TreeNode->LeftLeaves->significance);
		if (TreeNode->RightLeaves == NULL)
			printf("_ ");
		else
			printf("%d ", TreeNode->RightLeaves->significance);
	}

	printf("\n");

	scanf("%d", &m);

	if (findBaseNode(tree, m, &TreeNode) == 1)
		printf("-\n");
	else {
		if (TreeNode->Root_ == NULL)
			printf("_ ");
		else
			printf("%d ", TreeNode->Root_->significance);

		if (TreeNode->LeftLeaves == NULL)
			printf("_ ");
		else
			printf("%d ", TreeNode->LeftLeaves->significance);
		if (TreeNode->RightLeaves == NULL)
			printf("_ ");
		else
			printf("%d ", TreeNode->RightLeaves->significance);
	}

	scanf("%d", &m);

	Remove(tree, m);

	print(tree->root);

	while (rotateLeft(tree) == 0);

	print(tree->root);
	while (rotateRight(tree) == 0);

	print(tree->root);

	printf("%d\n", tree->count);

	clear(tree);

	print(tree->root);

	system("pause");
	return 0;
}

