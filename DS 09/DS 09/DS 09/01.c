//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

/*����(postfix notation)->����(infix notation) 
���� ǥ���(postfix notation)���� ǥ���� �ϳ��� ������ ���Ϸ� �Է¹޾� �� ��� ����� ȭ�鿡 ����ϴ� ���α׷�
���� ǥ��� ���
���Ǵ� ������: + - * / %
���Ǵ� �ǿ�����: 1~9������ �� �ڸ� ����
( ) �����ڴ� �Էµ��� ����
divide by zero�� ���� �׽�Ʈ �� ó���� �������� ����
�Է¼����� ���ڿ� ���̴� �ִ� 80���� ��
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80  //�Է� ������ ���ڿ� ���� �ִ� 80

//������ �ڷ��� ( ) + - * / % endofstack �ǿ�����
typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top = -1;


int eval();
precedence getToken(char* symbol, int* n);
void push(int item);
int pop();
void stackFull();
void stackEmpty();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//������ �Է¹��� 
	FILE* fp = fopen("input.txt", "r");

	//���Ͽ� �ִ� �����͸� 80��ŭ expr�� ���� 
	fgets(expr, 80, fp);
	int result = eval();

	printf("postfix expression : %s \n", expr); //
	printf("the evaluation value: %d \n", result);

	return 0;
}

//����ǥ����� ����ϴ� �Լ� (������ �̿�)
int eval()
{
	//������ �̿�
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; //counter for expression string (ǥ���� ���� ���� ����)

	//token�� �����ڿ� �ǿ����ڸ� ����
	token = getToken(&symbol, &n);

	/*end of stack�� �ƴ� ��
	�ǿ������϶��� �ƽ�Ű�ڵ带 Ȱ���ؼ� int������ �ٲ㼭 push
	�������϶��� �ǿ����� 2���� pop�ؼ� ����*/
	while (token != eos) {
		//���ÿ� ������ ���� �����̸� push
		if (token == operand)
			push(symbol - '0'); //�ƽ�Ű�ڵ带 Ȱ���ؼ� int������ �ٲ���
		//���ÿ� ������ ���� ����(������)��� ���� 2���� pop()�ϰ� �� ���� ���
		else {
			op2 = pop();
			op1 = pop();
			switch (token) {
			case plus:
				push(op1 + op2);
				break;
			case minus:
				push(op1 - op2);
				break;
			case times:
				push(op1 * op2);
				break;
			case divide:
				push(op1 / op2);
				break;
			case mod:
				push(op1 % op2);
			}
		}

		//token�� �����ڿ� �ǿ����ڸ� ����
		token = getToken(&symbol, &n);
	}

	//����� ��(pop�� ���)�� return 
	return pop();
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
void push(int item)
{
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();

	stack[++top] = item;
}

int pop()
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