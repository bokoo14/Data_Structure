//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

/*후위(postfix notation)->중위(infix notation) 
후위 표기법(postfix notation)으로 표현된 하나의 수식을 파일로 입력받아 그 계산 결과를 화면에 출력하는 프로그램
후위 표기법 계산
사용되는 연산자: + - * / %
사용되는 피연산자: 1~9사이의 한 자리 정수
( ) 연산자는 입력되지 않음
divide by zero에 대한 테스트 및 처리는 구현하지 않음
입력수식의 문자열 길이는 최대 80으로 함
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80  //입력 수식의 문자열 길이 최대 80

//열거형 자료형 ( ) + - * / % endofstack 피연산자
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
	//파일을 입력받음 
	FILE* fp = fopen("input.txt", "r");

	//파일에 있는 데이터를 80만큼 expr에 받음 
	fgets(expr, 80, fp);
	int result = eval();

	printf("postfix expression : %s \n", expr); //
	printf("the evaluation value: %d \n", result);

	return 0;
}

//후위표기법을 계산하는 함수 (스택을 이용)
int eval()
{
	//열거형 이용
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; //counter for expression string (표현에 대한 값을 세줌)

	//token에 연산자와 피연산자를 받음
	token = getToken(&symbol, &n);

	/*end of stack이 아닐 때
	피연산자일때는 아스키코드를 활용해서 int형으로 바꿔서 push
	연산자일때는 피연산자 2개를 pop해서 연산*/
	while (token != eos) {
		//스택에 들어오는 값이 숫자이면 push
		if (token == operand)
			push(symbol - '0'); //아스키코드를 활용해서 int형으로 바꿔줌
		//스택에 들어오는 값이 문자(연산자)라면 숫자 2개를 pop()하고 그 값을 계산
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

		//token에 연산자와 피연산자를 받음
		token = getToken(&symbol, &n);
	}

	//연산된 값(pop의 결과)을 return 
	return pop();
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
//--------------------스택------------------
