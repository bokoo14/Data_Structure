//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�


/* 14. Trees : ����Ʈ�� ���� �� ��ȸ (2)
* 1. ����ǥ������ �Է¹޾� Figure 5.16�� ���� ������� ����Ʈ���� ������ ��, 
* ����Ʈ�� ��ȸ�� ���� ����ǥ����, ����ǥ����, ����ǥ������ ����ϴ� ���α׷��� �ۼ��϶�. (5��)
* 
* [������ �Է�����]
* - �Է�����(input.txt) : AB/C*D*E+
* - �ǿ�����(Operands) : ���ĺ� �� ���� 
* - ������(Operators) : +, -, *, /, %
* 
* �� �ڷᱸ������ 09. 1�� ���α׷��� �����Ͽ� ������ �� ����
* - eval()�� �����Ͽ� ����ǥ������ ����Ʈ���� ����� createBinTree() �Լ��� ����
* - getToken() �� precedence ���� �״�� ���, stack�� �Ϻ� ����
* 
* [�������]
* �� ����ǥ�������� ���� ������� ����Ʈ���� �����Ѵ�. �� createBinTree();
* �� �ڷᱸ������ 09. 1�� ���α׷��� �����Ͽ� ������ �� ����
* - eval()�� �����Ͽ� ����ǥ������ ����Ʈ���� ����� createBinTree() �Լ��� ����
* - getToken() �� precedence ���� �״�� ���, stack�� �Ϻ� ����
* �� ������� ����Ʈ������ ������ ����� ���� ����Ʈ���� �� �������� ���� �ǿ����ڷ� ���ǰ� 
* ������ ����Ʈ���� ������ �ǿ����ڷ� ����
* �� ����Ʈ�� ������ȸ�� ���� ����ǥ����(infix expression)�� ����Ѵ�. �� inorder(root);
* �� ����Ʈ�� ������ȸ�� ���� ����ǥ����(prefix expression)�� ����Ѵ�. �� preorder(root);
* �� ����Ʈ�� ������ȸ�� ���� ����ǥ����(postfix expression)�� ����Ѵ�. �� postorder(root); 
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100

#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//����Ʈ�����
typedef struct node * treePointer;
typedef struct node {
	char data; //��������� ���� char������ ����
	treePointer leftChild, rightChild;
}node;

treePointer root;
treePointer stack[MAX_STACK_SIZE];
int top = -1;
char expr[81]; //postfix expression


typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

//���� �Է¹ޱ�
//int eval();
precedence getToken(char* symbol, int* n);

//stack
void push(treePointer item);
treePointer pop();
void stackFull();
void stackEmpty();

//tree traversal 
void inorder(treePointer ptr);
void postorder(treePointer ptr);
void preorder(treePointer ptr);

//binary tree ����
treePointer createNode(char data);
treePointer createBinTree(void);



int main()
{
	FILE* fp = fopen("input.txt", "r");

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (fscanf(fp, "%c", &expr[i++]) != EOF) //end of file�� �ɶ�����
	{	
	}

	//���Ϸ� ���� �Է¹��� ����ǥ������ ����Ʈ���� �����
	printf("the length of input string sholud be less than 80\n");
	root = createBinTree();

	printf("input string <postfix expression>: ");
	printf("%s", expr);
	printf("\n");
	printf("creating its binary tree\n \n");


	//���Ϸ� ���� �Է¹��� ����ǥ������ ����Ʈ���� �����, �� ����Ʈ���� ��ȸ
	printf("inorder traversal  :");
	inorder(root);
	printf("\n");

	printf("preorder traversal  :");
	preorder(root);
	printf("\n");

	printf("postorder traversal  :");
	postorder(root);
	printf("\n");

	return 0;
}


/* �����ڿ� �ǿ����� �ޱ�
( )�� ��� �� ���������� ������ ����
�������� �� �Լ��� �ڷ������� ����
return ���� plus, minus, times,..�̱� ������ �Լ��� �ڷ����� precedence�� ���־�� �� */
precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}


//--------------------����------------------
void push(treePointer item)
{
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();

	stack[++top] = item;
}

treePointer pop()
{
	if (top == -1)
		stackEmpty();

	return stack[top--];
}

void stackFull()
{
	fprintf(stderr, "stack is full, cannot add element \n");
	exit(EXIT_FAILURE);
}

void stackEmpty()
{
	fprintf(stderr, "stack is empty, cannot delete element \n");
	exit(EXIT_FAILURE);
}
//--------------------����------------------


//tree traversal
//������ȸ
void inorder(treePointer ptr) {
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}

//������ȸ
void postorder(treePointer ptr) {
	if (ptr)
	{
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}

//������ȸ
void preorder(treePointer ptr) {
	if (ptr)
	{
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}



//binary tree
//��� ���� �Լ�, ��ũ �ʵ�� NULL�� ����
treePointer createNode(char data) {

	treePointer p = NULL;
	MALLOC(p, sizeof(*p));

	p->data = data;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}

//eval()�� �����Ͽ� "����ǥ������ ����Ʈ���� ����� createBinTree()�Լ�"�� ����
treePointer createBinTree(void)
{ /* postfix expression���κ��� ����Ʈ���� ����  �� ��Ʈ ��� �����͸� ��ȯ */
	treePointer pNode;
	precedence token;
	char symbol;
	int n = 0; /* counter for the expression string */
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos)
	{
		pNode = createNode(symbol);
		// ��ȣ�϶� �� ���(A, B, C,..)�� ����, ��Ʈ ���� ��ȣ(+, -, *, /, %)
		if (token != operand) // operator node (+, -, *, /, %)
		{
			pNode->rightChild = pop(); // link operand
			pNode->leftChild = pop(); // link operand
		}
		push(pNode); //�����϶� (A, B, C, ...)
		token = getToken(&symbol, &n);
	}
	return pop(); /* return root pointer */
}