//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/*
* 13. Trees: ����Ʈ�� ���� �� ��ȸ(1)
* ����Ʈ���� �����ϰ� ����Ʈ�� ��ȸ��� �� ������ȸ, ������ȸ, ������ȸ�� ���� ����ϴ� ���α׷� �ۼ�
* 
* [�������]
* 1) ����Ʈ�� ���� (���������� ��带 ������ ��, �׸��� ���� ������ ����Ʈ���� �ǰ� ��ũ�� �����Ѵ�)
* 2) ����Ʈ�� ������ȸ�� ���� ������ ���
* 3) ����Ʈ�� ������ȸ�� ���� ������ ���
* 4) ����Ʈ�� ������ȸ�� ���� ������ ���
*/

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }

#include<stdio.h>
#include<stdlib.h>

//���� Ʈ�� ��� ����
typedef struct node* treePointer;
typedef struct node {
	char data; //��������� ���� char������ ����
	treePointer leftChild, rightChild;
}node;

treePointer root;

//binary tree
treePointer createNode(char data); //��� ���� �Լ��̹Ƿ� ��ũ �ʵ�� NULL�� ����
treePointer createBinTree(); //����Ʈ�� ���� �Լ�

//binary tree traversals
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);



int main()
{
	treePointer tree = NULL;
	
	printf("creating a binary tree\n \n");
	tree=createBinTree();

	printf("three binary tree traversals\n");
	printf("inorder traversal    : ");
	inorder(tree);
	printf("\n");

	printf("preorder traversal   : ");
	preorder(tree);
	printf("\n");

	printf("postorder traversal  : ");
	postorder(tree);
	printf("\n");

	return 0;
}

//binary tree
//��� ���� �Լ�, ��ũ �ʵ�� NULL�� ����
treePointer createNode(char data) {

	treePointer p = NULL;
	MALLOC(p, sizeof(*p));

	p->data = data;
	p->leftChild = NULL; //��ũ �ʵ� NULL�� ����
	p->rightChild = NULL; //��ũ �ʵ� NULL�� ����

	return p;
}

/*
* ����Ʈ�� ����
* ���������� ��带 ������ ��, �׸��� ���� ������ ����Ʈ���� �ǰ� ��ũ�� �����Ѵ�
*/
treePointer createBinTree() {
	
	treePointer A = createNode('A');
	treePointer B = createNode('B');
	treePointer C = createNode('C');
	treePointer D = createNode('D');
	treePointer E = createNode('E');

	A->leftChild = B;
	A->rightChild = C;

	B->leftChild = D;
	B->rightChild = E;

	//��Ʈ��带 return
	return A;
}

//binary tree traversals
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