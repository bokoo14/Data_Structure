//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 
* 14. Trees : 이진트리 생성 및 순회 (2)
* 2. 후위표현식을 입력받아 Figure 5.16과 같은 이진트리를 구성한 후, 
* "반복문을 사용한 중위, 전위 및 level-order 순회"를 하는 프로그램을 작성하라.(10점)
* ※ 중위, 전위, 레벨오더 순회는 각 3, 4, 3점 ※ 후위순회는 도전과제 (5점 추가) 
* 
* [실행순서]
* ① 후위표현식으로 부터 산술식의 이진트리를 생성한다. ※ createBinTree(); 
* ② 반복문을 사용한 이진트리 중위순회, 전위순회를 통해 데이터를 출력한다. 
* ※ iterInorder(root); iterPreorder(root); 
* ※ ①에서 사용한 스택을 그대로 사용 
* ③ level-order traversal을 통해 각 노드의 데이터를 출력한다. 
* ※ levelOrder(root); // circular queue 사용
* 
* 스택-> 반복문을 이용한 중위, 전위. 후위
* 큐-> 레벨 순회
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


//binary tree 생성
treePointer createNode(char data);
treePointer createBinTree(void);

//반복문을 사용한 이진트리 중위순회, 전위순회, 레벨순회를 통해 데이터를 출력
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
	while (fscanf(fp, "%c", &expr[i++]) != EOF) //end of file이 될때까지
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


/* 연산자와 피연산자 받기
( )의 경우 이 문제에서는 사용되지 않음
열거형을 이 함수의 자료형으로 지정
return 값이 plus, minus, times,..이기 때문에 함수의 자료형을 precedence로 해주어야 함 */
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


//--------------------스택------------------
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
//--------------------스택------------------


//------------------------환형 큐-------------------------
//환형 큐가 비었을때
//간단한 메시지를 출력하고 NULL 포인터를 반환되도록 함
treePointer queueEmpty()
{
	fprintf(stderr, "queue is empty, cannot delete element.\n");
	return NULL;
}

//환형 큐가 가득 찼을때 간단한 메시지를 출력하고 프로그램을 종료함
//array shift를 구현하지 않음
void queueFull()
{
	printf(stderr, "queue is empty, cannot delete element.\n");
	exit(EXIT_FAILURE);
}

//환형큐에 enqueue()
void addq(treePointer item)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear)
		queueFull();
	queue[rear] = item;
}

//환형큐에 dequeue()
treePointer deleteq()
{
	treePointer item;

	//환형 큐는 front와 rear의 값이 같으면 비어있음
	if (front == rear)
		return queueEmpty();
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
//------------------------큐-------------------------



//binary tree 생성
//노드 생성 함수, 링크 필드는 NULL로 지정
treePointer createNode(char data) {

	treePointer p = NULL;
	MALLOC(p, sizeof(*p));

	p->data = data;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}

treePointer createBinTree(void)
{ /* postfix expression으로부터 이진트리를 만든 후 루트 노드 포인터를 반환 */
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


//반복문을 사용한 이진트리 중위순회, 전위순회를 통해 데이터를 출력
//반복적 중위순회 => LVR
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

//반복적 전위순회 => VLR
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

//반복적 후위순회 => LRV
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

//레벨순회-> 환형 큐 활용
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

