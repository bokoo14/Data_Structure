//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 16(2) ����Ž��Ʈ��
* 2. ������ ���� ������ ��� n���� ������ ����Ž��Ʈ��(binary search tree)�� �����ϴ� ���α׷�
* 
* (1) �������
* �� ���������� ���� seed�� ����Ž��Ʈ���� ��� ����(n)�� �Է¹���  �� scanf
* �� 1~500 ������ ������ �����Ͽ� ����� key�� item �ʵ� ������ �����ϰ� ���
* �� ����Ž��Ʈ���� key ���� �ߺ��� ������ ������ ����
* �� ���� key, item�� ����Ͽ� ����Ž��Ʈ���� ��带 �ϳ� �߰��� 
* �� Program 5.17. insert
* �� Program 5.17���� ���� modifiedSearch�Լ��� Program 5.16�� ������
* �� ��~�� ������ n�� �����Ͽ� ����Ž��Ʈ���� ���� �� �����߻� ������� ��带 �߰��ؾ� ��
* �� Ž���� key�� �Է¹޾Ƽ� ����Ž���Ͽ� �� ����� ����Ѵ�. �� Program 5.15 Ȥ�� 5.16
* �� ����Ž��Ʈ���� �����ϰ� �ִ� ����� key���� ������������ ���ĵǵ��� �����
* �� inorder traversal ���
*/
#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
	if( !( (p) =malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define MAX_SIZE 500

typedef int iType;
typedef struct {
	int key;
	iType item;
}element;
typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
}node;
treePointer tree;

//recursion search of a binary search tree
element* search(treePointer root, int k);
//iterative search of a binary tree
element* iterSearch(treePointer tree, int k);
//inserting a dictionary pair into a binary search tree
void insert(treePointer* node, int k, iType theItem);

//program 5.16 iterSearch ����
treePointer modifiedSearch(treePointer node, int k);

//���� ��ȸ
void inorder(treePointer ptr);

#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n;
	int seed;
	int searchnum;
	printf("random number generation <1~500>\n");
	printf("the number of nodes in BST <less than and equal to 50> : ");
	scanf("%d", &n);
	printf("seed: ");
	scanf("%d", &seed);
	printf("\n");

	printf("creating a BST from random numbers \n");
	srand(seed);


	int cnt=0;
	int numbers[MAX_SIZE + 1] = { 0 };
	int key;
	while (cnt < n)
	{
		key = 1 + rand() % MAX_SIZE;
		if (!numbers[key]) // unique random number
		{
			numbers[key] ++;
			printf("%4d", key);
			insert(&tree, key, (iType)key);
			cnt++;
		}
	}
	printf("\n");


	printf("the key to search :");
	scanf("%d", &searchnum);
	element* ptr = search(tree, searchnum);
	if (search(tree, searchnum)) {
		printf("the element's item is %d\n",ptr->item); 
	}
	else {
		printf("there is no such an element \n\n");
	}
	printf("\n\n");


	printf("inorder traversal of the BST shows the sorted sequence\n");
	inorder(tree);

	return 0;
}


//recursion search of a binary search tree
element* search(treePointer root, int k) {
	if (!root) return NULL;
	if (k == root->data.key) return &(root->data);
	if (k < root->data.key) return search(root->leftChild, k);
	return  search(root->rightChild, k);
}


//iterative search of a binary tree
element* iterSearch(treePointer tree, int k) {
	while (tree)
	{
		if (k == tree->data.key) return &(tree->data);
		if (k < tree->data.key)
			tree = tree->leftChild;
		else
			tree = tree->rightChild;
	}
	return NULL;
}


//inserting a dictionary pair into a binary search tree
void insert(treePointer* node, int k, iType theItem)
{ 
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node))
	{
		
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*node)
		{
			if (k < temp->data.key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else
		{
			*node = ptr;
		}
	}
}

//program 5.16 iterSearch ���� => ����Ž��Ʈ�� ����
treePointer modifiedSearch(treePointer node, int k){
	treePointer temp = NULL;
	if (!node) return NULL;
	while (node)
	{
		temp = node;
		if (k == node->data.key) return NULL;
		if (k < node->data.key)
			node = node->leftChild;
		else 
			node = node->rightChild;
	}
	return temp;
}

//���� ��ȸ
//�������� ���
void inorder(treePointer ptr) {
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%4d", ptr->data.key);
		inorder(ptr->rightChild);
	}
}
