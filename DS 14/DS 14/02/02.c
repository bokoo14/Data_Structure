//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 
* 14. Trees : ����Ʈ�� ���� �� ��ȸ (2)
* 2. ����ǥ������ �Է¹޾� Figure 5.16�� ���� ����Ʈ���� ������ ��, 
* "�ݺ����� ����� ����, ���� �� level-order ��ȸ"�� �ϴ� ���α׷��� �ۼ��϶�.(10��)
* �� ����, ����, �������� ��ȸ�� �� 3, 4, 3�� �� ������ȸ�� �������� (5�� �߰�) 
* 
* [�������]
* �� ����ǥ�������� ���� ������� ����Ʈ���� �����Ѵ�. �� createBinTree(); 
* �� �ݺ����� ����� ����Ʈ�� ������ȸ, ������ȸ�� ���� �����͸� ����Ѵ�. 
* �� iterInorder(root); iterPreorder(root); 
* �� �翡�� ����� ������ �״�� ��� 
* �� level-order traversal�� ���� �� ����� �����͸� ����Ѵ�. 
* �� levelOrder(root); // circular queue ���
* 
* ����-> �ݺ����� �̿��� ����, ����. ����
* ť-> ���� ��ȸ
*/


#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}node;
treePointer root;

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
char expr[81]; //postfix expression

precedence getToken(char* symbol, int* n);

//stack
treePointer stack[MAX_STACK_SIZE];
int top = -1;
void push(treePointer item);
treePointer pop();
void stackFull();
void stackEmpty();

// circular queue
treePointer queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;
treePointer queueEmpty();
void queueFull();
void addq(treePointer item);
treePointer deleteq();


//binary tree ����
treePointer createNode(char data);
treePointer createBinTree(void);

//�ݺ����� ����� ����Ʈ�� ������ȸ, ������ȸ, ������ȸ�� ���� �����͸� ���
void iterInorder(treePointer node);
void iterPreorder(treePointer node);
void iterPostorder(treePointer node);
void levelOrder(treePointer ptr);


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

	printf("the length of input string sholud be less than 80\n");
	root = createBinTree();

	printf("input string <postfix expression>: ");
	printf("%s", expr);
	printf("\n");
	printf("creating its binary tree\n \n");


	printf("iterative  inorder traversal  :");
	iterInorder(root);
	printf("\n");

	printf("iterative preorder traversal  :");
	iterPreorder(root);
	printf("\n");

	printf("iterative postorder traversal  :");
	iterPostorder(root);
	printf("\n");

	printf("level order traversal  :");
	levelOrder(root);
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


//------------------------ȯ�� ť-------------------------
//ȯ�� ť�� �������
//������ �޽����� ����ϰ� NULL �����͸� ��ȯ�ǵ��� ��
treePointer queueEmpty()
{
	fprintf(stderr, "queue is empty, cannot delete element.\n");
	return NULL;
}

//ȯ�� ť�� ���� á���� ������ �޽����� ����ϰ� ���α׷��� ������
//array shift�� �������� ����
void queueFull()
{
	printf(stderr, "queue is empty, cannot delete element.\n");
	exit(EXIT_FAILURE);
}

//ȯ��ť�� enqueue()
void addq(treePointer item)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear)
		queueFull();
	queue[rear] = item;
}

//ȯ��ť�� dequeue()
treePointer deleteq()
{
	treePointer item;

	//ȯ�� ť�� front�� rear�� ���� ������ �������
	if (front == rear)
		return queueEmpty();
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
//------------------------ť-------------------------



//binary tree ����
//��� ���� �Լ�, ��ũ �ʵ�� NULL�� ����
treePointer createNode(char data) {

	treePointer p = NULL;
	MALLOC(p, sizeof(*p));

	p->data = data;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}

treePointer createBinTree(void)
{ /* postfix expression���κ��� ����Ʈ���� ���� �� ��Ʈ ��� �����͸� ��ȯ */
	treePointer pNode;
	precedence token;
	char symbol;
	int n = 0; /* counter for the expression string */
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos)
	{
		pNode = createNode(symbol);
		if (token != operand) // operator node
		{
			pNode->rightChild = pop(); // link operand
			pNode->leftChild = pop(); // link operand
		}
		push(pNode);
		token = getToken(&symbol, &n);
	}
	return pop(); /* return root pointer */
}


//�ݺ����� ����� ����Ʈ�� ������ȸ, ������ȸ�� ���� �����͸� ���
//�ݺ��� ������ȸ => LVR
void iterInorder(treePointer node) {
	top = -1;
	for (;;)
	{
		//L
		for (; node; node = node->leftChild)
			push(node);
		
		if (top == -1) 
			break;

		node = pop();

		if (!node) break;

		//V
		printf("%c", node->data);

		//R
		node = node->rightChild;
	}
}

//�ݺ��� ������ȸ => VLR
void iterPreorder(treePointer node) {
	top = -1;
	for (;;)
	{
		for (; node; node = node->leftChild)
		{
			//V
			printf("%c", node->data);
			push(node);
		}
		
		if (top == -1)
			break;

		//L
		node = pop();

		if (!node) break;

		//R
		node = node->rightChild;
	}
}

//�ݺ��� ������ȸ => LRV
void iterPostorder(treePointer node) {
	top = -1;

	treePointer temp;

	for (;;)
	{
		//L
		for (; node; node = node->leftChild)
		{
			push(node); 
		}

		if (top == -1)
			break;
		node = pop();
		temp = node;
		if (!node) break;

		//R
		if (node->rightChild)
		{
			node = node->rightChild;
			printf("%c", node->data);
			printf("%c", temp->data);
			node = node->rightChild;
		}
		else
		{
			node = node->rightChild;
			//V
			printf("%c", temp->data);
		}
		;
	}
}

//������ȸ-> ȯ�� ť Ȱ��
void levelOrder(treePointer ptr)
{
	front = rear = 0;
	if (!ptr) return;
	addq(ptr);
	for (;;) {
		if (front == rear)
			break;
		ptr = deleteq();
		if (ptr)
		{
			printf("%c", ptr->data);
			if (ptr->leftChild)
				addq(ptr->leftChild);
			if (ptr->rightChild)
				addq(ptr->rightChild);
		}
		else break;
	}
}
