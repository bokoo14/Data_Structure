//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

//����ǥ������� ǥ���� �ϳ��� ������ ���Ϸ� �Է¹޾� ����ǥ������� ��ȯ�Ͽ� ȭ�� �� ���Ͽ� ���ÿ� ����ϴ� ���α׷�
//����(infix notation)->����

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80
#define MAX_STRING_SIZE 80

//������ �ڷ��� ( ) + - * / % endofstach
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

//--------------------����------------------
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
//--------------------����------------------


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

/*����(infix notation)->����(postfix notation)
����ǥ������� ��Ÿ���� �����ڴ� post[]�� ����
�����ڸ� �����صδ� ���� ���ÿ� �����ؼ� ������ �켱 ������ ������*/
void postfix()
{
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		//token�� ����(a,b, c, .. Ȥ�� 1, 2 ,3, ...)�̸� post�迭�� �־���
		if (token == operand) {
			printf("%c", symbol);
			post[index++] = symbol;
		}
		//������ ��ȣ�� ������
		else if (token == rparen) {
			while (stack[top] != lparen)
				printToken(pop());
			pop();
		}
		//������( + - * / % )�� ������ �켱������ ��
		//�켱 ������ �� ������ ���ÿ� �̹� ������ �켱 ������ �� ���� �����ڸ� pop���ְ� printToken����
		//�켱������ �� ������ ���ÿ� ������ ���ÿ� push����
		else {
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}

	//������ ������� ������ token�� end of stack�϶����� printToken����
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}
