//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 
* 13(2) ["ť"�� �̿��� "��������Ʈ�� ����"]
* �����Է��� �޾� ������ ���� ��������Ʈ���� �����Ͽ�, ������ȸ, ������ȸ, ������ȸ�� ���� ����ϴ� ���α׷�
* 
* [�������]
* �� �Է�����(input.txt)�κ��� ������ ���� ��������Ʈ���� �����Ѵ�.
* �� ����Ʈ�� ������ȸ�� ���� �����͸� ����Ѵ�. �� inorder(root);
* �� ����Ʈ�� ������ȸ�� ���� �����͸� ����Ѵ�. �� preorder(root);
* �� ����Ʈ�� ������ȸ�� ���� �����͸� ����Ѵ�. �� postorder(root);
*/

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }
#define MAX_QUEUE_SIZE 100

#include<stdio.h>
#include <string.h>
#include<stdlib.h>

//Ʈ�� ��� ���� �� ť ����
typedef struct node* treePointer;
typedef struct node {
	char data; //��������� ���� char������ ����
	treePointer leftChild, rightChild;
}node;

treePointer root = NULL;
treePointer queue[MAX_QUEUE_SIZE];

//queue
int rear = -1;
int front = -1;

treePointer queueEmpty();
void queueFull();
void deleteq();
void addq(treePointer item);
treePointer getFront();


//binary tree
treePointer createNode(char data); //��� ���� �Լ��̹Ƿ� ��ũ �ʵ�� NULL�� ����
treePointer createCompBinTree(FILE *fp);

//pRoot�� ����Ű�� ��������Ʈ���� pNode�� ����Ű�� �� ��带 �߰��Ѵ�
void insert(treePointer pNode);


//binary tree traversals
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);



int main()
{
	FILE* fp=fopen("input.txt","r");

	printf("creating a complete binary tree\n \n");
	root=createCompBinTree(fp);

	printf("three binary tree traversals\n");
	printf("inorder traversal        : ");
	inorder(root);
	printf("\n");

	printf("preorder traversal       : ");
	preorder(root);
	printf("\n");

	printf("postorder traversal      : ");
	postorder(root);
	printf("\n");

	return 0;
}


//------------------------ť-------------------------
//���� ť�� �������
//������ �޽����� ����ϰ� NULL �����͸� ��ȯ�ǵ��� ��
treePointer queueEmpty()
{
	fprintf(stderr, "queue is empty, cannot delete element.\n");
	return NULL;
}

//���� ť�� ���� á���� ������ �޽����� ����ϰ� ���α׷��� ������
//array shift�� �������� ����
void queueFull()
{
	printf(stderr, "queue is empty, cannot delete element.\n");
	exit(EXIT_FAILURE);
}

//����ť�� enqueue()
void addq(treePointer item)
{
	//���� ť���� rear�� ���� queue�� ������ index�� ����Ű�� ����������
	if (rear == MAX_QUEUE_SIZE - 1)
		queueFull();
	queue[++rear] = item;
}

//����ť�� dequeue()
void deleteq()
{
	//���� ť�� front�� rear�� ���� ������ �������
	if (front == rear)
		queueEmpty();
	queue[++front];

}

//ť�� ���� �����׸� ���� ��ȯ�ϴ� �Լ�, ť�� �׸��� �������� ����
treePointer getFront() {
	return queue[front+1];
}
//------------------------ť-------------------------


//--------------binary tree --------------
//��� ���� �Լ�, ��ũ �ʵ�� NULL�� ����
treePointer createNode(char data) {

	treePointer p = NULL;
	MALLOC(p, sizeof(*p));

	p->data = data;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}

//����Ʈ�� ����
treePointer createCompBinTree(FILE *fp){
	char data;
	treePointer newNode;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	//data�� �Է¹��� �� ���� ��带 �����Ͽ� insert ����
	while (fscanf(fp, "%c", &data) != EOF) //end of file�� �ɶ�����
	{
		newNode = createNode(data);
		insert(newNode);
	}
	
	return root;

}

//pRoot�� ����Ű�� ��������Ʈ���� pNode�� ����Ű�� �� ��带 �߰�
void insert(treePointer pNode)
{
	treePointer frontnode;

	if (!root) //if tree is empty
	{
		root = pNode; //initialize the root with the new node 
	}
	else //if tree is not empty
	{
		frontnode = getFront(); //get the front node of the queue
		if (!(frontnode->leftChild)) //if the left child of this front node doesn't exist
		{
			frontnode->leftChild = pNode; //set the left child as the new node
		}
		else if (!(frontnode->rightChild)) //if the right child of this front node doesn't exist
		{
			frontnode->rightChild = pNode; //set the right child as the new node
		}

		if ((frontnode->leftChild) && (frontnode->rightChild)) //if the front node has both children
		{
			deleteq();
		}
	}
	addq(pNode); //add the new node
}
//--------------binary tree--------------


//--------------binary tree traversals--------------
//������ȸ
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}

}

//������ȸ
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

//������ȸ
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}
//--------------binary tree traversals--------------