//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

//중위표기법으로 표현된 하나의 수식을 파일로 입력받아 후위표기법으로 변환하여 화면 및 파일에 동시에 출력하는 프로그램
//중위(infix notation)->후위

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80
#define MAX_STRING_SIZE 80

//열거형 자료형 ( ) + - * / % endofstach
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

precedence stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
char post[MAX_STRING_SIZE];
int top = -1;
int index = 0;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void push(int item);
precedence pop();
void stackFull();
void stackEmpty();
void printToken(precedence token);
void postfix(void);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fp = fopen("input.txt", "r");
	fgets(expr, 80, fp);
	printf("<<<<<<<infix to postfix>>>>>>>>>>>\n");
	printf("infix expression          :%s \n", expr);


	printf("postfix expression        :");
	postfix();

	FILE* fb = fopen("output.txt", "w");
	fputs(post, fb);


	return 0;
}

//--------------------스택------------------
void push(int item)
{
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();

	stack[++top] = item;
}

precedence pop()
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


precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

void printToken(precedence token)
{
	char item;

	switch (token) {
	case plus:
		item = '+';
		break;
	case minus:
		item = '-';
		break;
	case times:
		item = '*';
		break;
	case divide:
		item = '/';
		break;
	case mod:
		item = '%';
	}

	printf("%c", item);
	post[index++] = item;

	return;
}

/*중위(infix notation)->후위(postfix notation)
후위표기법으로 나타내는 연산자는 post[]에 저장
연산자를 저장해두는 것은 스택에 저장해서 연산자 우선 순위를 비교해줌*/
void postfix()
{
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		//token이 문자(a,b, c, .. 혹은 1, 2 ,3, ...)이면 post배열에 넣어줌
		if (token == operand) {
			printf("%c", symbol);
			post[index++] = symbol;
		}
		//오른쪽 괄호를 만나면
		else if (token == rparen) {
			while (stack[top] != lparen)
				printToken(pop());
			pop();
		}
		//연산자( + - * / % )를 만나면 우선순위를 비교
		//우선 순위가 더 높은게 스택에 이미 있으면 우선 순위가 더 높은 연산자를 pop해주고 printToken해줌
		//우선순위가 더 낮은게 스택에 들어오면 스택에 push해줌
		else {
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}

	//스택이 비어있지 않으면 token이 end of stack일때까지 printToken해줌
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}

