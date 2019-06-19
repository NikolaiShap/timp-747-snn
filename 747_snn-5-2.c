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

void print(TreeNode * Root)
{
	TaskNode* mass[15];
	int tmp = 0;
	TaskNode* mass2[15];
	int tmp_2 = 0;
	TaskNode* node = Root->root;
	while (tmp_2 < Root->count)
	{
		while (node != NULL)
		{
			tmp_2++;
			if (node->RightLeaves != NULL)
			{
				tmp++;
				mass[tmp] = node->RightLeaves;
			}
			mass2[tmp_2] = node;
			node = node->LeftLeaves;

		}
		node = mass[tmp];
		tmp = tmp - 1;
	}
	for (int i = 1; i <= tmp_2; i++)
	{
		printf("%d ", mass2[i]->significance);
	}
	printf("\n");
}


int main() {
	TreeNode* tree = (TreeNode*)malloc(sizeof(TaskNode));
	init(tree);

	int a[7];
	for (int i = 0; i < 7; i++)
	{
		scanf("%d", &a[i]);
		insert(tree, a[i]);
	}



	print(tree);

}

