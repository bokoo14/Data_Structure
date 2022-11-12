//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다


/* 14. Trees : 이진트리 생성 및 순회 (2)
* 1. 후위표현식을 입력받아 Figure 5.16과 같은 산술식의 이진트리를 구성한 후, 
* 이진트리 순회를 통해 중위표현식, 전위표현식, 후위표현식을 출력하는 프로그램을 작성하라. (5점)
* 
* [데이터 입력형식]
* - 입력파일(input.txt) : AB/C*D*E+
* - 피연산자(Operands) : 알파벳 한 글자 
* - 연산자(Operators) : +, -, *, /, %
* 
* ※ 자료구조응용 09. 1번 프로그램을 수정하여 구현할 수 있음
* - eval()을 수정하여 후위표현식을 이진트리로 만드는 createBinTree() 함수를 정의
* - getToken() 과 precedence 형은 그대로 사용, stack은 일부 수정
* 
* [실행순서]
* ① 후위표현식으로 부터 산술식의 이진트리를 생성한다. ※ createBinTree();
* ※ 자료구조응용 09. 1번 프로그램을 수정하여 구현할 수 있음
* - eval()을 수정하여 후위표현식을 이진트리로 만드는 createBinTree() 함수를 정의
* - getToken() 과 precedence 형은 그대로 사용, stack은 일부 수정
* ※ 산술식의 이진트리에서 연산자 노드의 왼쪽 서브트리는 그 연산자의 왼쪽 피연산자로 사용되고 
* 오른쪽 서브트리는 오른쪽 피연산자로 사용됨
* ② 이진트리 중위순회를 통해 중위표현식(infix expression)을 출력한다. ※ inorder(root);
* ③ 이진트리 전위순회를 통해 전위표현식(prefix expression)을 출력한다. ※ preorder(root);
* ④ 이진트리 후위순회를 통해 후위표현식(postfix expression)을 출력한다. ※ postorder(root); 
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100

#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//이진트리노드
typedef struct node * treePointer;
typedef struct node {
	char data; //문자출력을 위해 char형으로 지정
	treePointer leftChild, rightChild;
}node;

treePointer root;
treePointer stack[MAX_STACK_SIZE];
int top = -1;
char expr[81]; //postfix expression


typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

//수식 입력받기
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

//binary tree 생성
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
	while (fscanf(fp, "%c", &expr[i++]) != EOF) //end of file이 될때까지
	{	
	}

	//파일로 부터 입력받은 후위표현식을 이진트리로 만들기
	printf("the length of input string sholud be less than 80\n");
	root = createBinTree();

	printf("input string <postfix expression>: ");
	printf("%s", expr);
	printf("\n");
	printf("creating its binary tree\n \n");


	//파일로 부터 입력받은 후위표현식을 이진트리로 만들고, 그 이진트리를 순회
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


//tree traversal
//중위순회
void inorder(treePointer ptr) {
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}

//후위순회
void postorder(treePointer ptr) {
	if (ptr)
	{
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}

//전위순회
void preorder(treePointer ptr) {
	if (ptr)
	{
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}



//binary tree
//노드 생성 함수, 링크 필드는 NULL로 지정
treePointer createNode(char data) {

	treePointer p = NULL;
	MALLOC(p, sizeof(*p));

	p->data = data;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}

//eval()을 수정하여 "후위표현식을 이진트리로 만드는 createBinTree()함수"를 정의
treePointer createBinTree(void)
{ /* postfix expression으로부터 이진트리를 만든  후 루트 노드 포인터를 반환 */
	treePointer pNode;
	precedence token;
	char symbol;
	int n = 0; /* counter for the expression string */
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos)
	{
		pNode = createNode(symbol);
		// 기호일때 두 노드(A, B, C,..)를 연결, 루트 노드는 기호(+, -, *, /, %)
		if (token != operand) // operator node (+, -, *, /, %)
		{
			pNode->rightChild = pop(); // link operand
			pNode->leftChild = pop(); // link operand
		}
		push(pNode); //문자일때 (A, B, C, ...)
		token = getToken(&symbol, &n);
	}
	return pop(); /* return root pointer */
}
