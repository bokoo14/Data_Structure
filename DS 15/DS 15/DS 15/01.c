//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/*15.(1) �������� ����
*  1. ��ȣ�� ������ infix expression�� �������� ���Ϸκ��� �Է¹޾� ����ǥ����(postfix expression)���� ��ȯ�Ͽ� ȭ�� �� ���Ϸ� ����ϴ� ���α׷��� �ۼ��϶�. (3��) 
* �� �߰����� 2�� ������ ����(���� ���� �ҽ��� �״�� �ٿ�޾� ��� ����)
* 
* [�������λ���]
* �� �־��� �ǽ����� �ҽ�����( ds16_1_student.c )�� �����Ͽ� �����Ѵ�. 
* �� ���� : precedence, isp, icp, getTocken, printTocken
* �� logical and(&&), logical or(||), logical not (!)�� &, |, ~���� ����Ͽ� ����Ѵ�. 
* �� ���� p.130, Figure 3.12 ������ �켱���� : || < && < ! 
* �� ��ȣ�� ���� ��쿡�� ����� �켱������ �ݿ��ϵ��� �����Ǿ�� ��
* �� postfix expression�� ��ȣ�� �������� �ʴ´�. �� �ݵ�� ȭ�� �� ����(postfix.txt)�� ���� ��µǾ�� �Ѵ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80

char expr[MAX_EXPR_SIZE]; //���Ͽ� ����� infix expression
char post[MAX_EXPR_SIZE]; //a postfix expression

int top = -1;
int index = 0;

typedef enum { lparen, rparen, or , and, not, eos, operand } precedence;

precedence stack[MAX_STACK_SIZE];

int isp[] = { 0, 19, 4, 5, 15, 0 };
int icp[] = { 20, 19, 4, 5, 15, 0 };

//stack
void push(precedence item);
precedence pop();
void stackFull();
void stackEmpty();

//������ �ޱ�
precedence getToken(char* symbol, int* n);
void printToken(precedence token);
void postfix(void);

int main(void)
{
    //������ ������ expr�迭�� �������� �޾ƿ�
    FILE* fp;
    int i = 0;
    if ((fp = fopen("infix.txt", "r")) == NULL)
    {
        fprintf(stderr, "cannot open the file");
        exit(EXIT_FAILURE);
    }
    while (fscanf(fp, "%c ", &expr[i++]) != EOF) {}


    printf("<<<<<< infix to postfix >>>>>>\n");
    printf("infix expression     :%s", expr); //���Ͽ� ����Ǿ� �ִ� ������ ���(expr�迭 ���)
    printf("\n");

    //����ǥ�������� ����
    printf("postfix expression   :");
    postfix();

    //���Ͽ� ����ǥ������ ����Ǿ� �ִ� post����
    FILE* fb = fopen("postfix.txt", "w");
    fputs(post, fb);

    return 0;
}

//stack
void push(precedence item)
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
    fprintf(stderr, "Stack is full, cannot add element\n");
    exit(EXIT_FAILURE);
}

void stackEmpty()
{
    fprintf(stderr, "Stack is empty, cannot delete element\n");
    exit(EXIT_FAILURE);
}


/*
* ������ �ޱ�
* precedence�� ��(and or not)�� �޾Ƽ� item�� �����Ͽ� ���
* item�� ��(&, |, ~)�� post�迭�� �����Ѵ�
*/
void printToken(precedence token) 
{
    char item;
    switch (token)
    {
    case and:
        item = '&';
        break;
    case or:
        item = '|';
        break;
    case not:
        item = '~';
        break;
    default:
        break;
    }
    printf("%c", item);
    post[index++] = item;
}

// (, ), |, &, ~, \0 ���� �޾ƿͼ� precedence�� ��ȯ�Ѵ�
precedence getToken(char* symbol, int* n)
{ /* get the next token, symbol is the character representation,
    whichis returned, the tokenis represented by its enumerated value,
    which is returned inthe function name */
    *symbol = expr[(*n)++];
    switch (*symbol)
    {
    case '(': return lparen;

    case ')': return rparen;

    case '|': return or ;

    case '&': return and;

    case '~': return not;

    case '\0': return eos;

    default: return operand; /* no error checking, default is operand */
    }
}

//����ǥ������� �ٲ㼭 post�� �ִ´�
void postfix()
{
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand) {
            printf("%c", symbol);
            post[index++] = symbol;
        }
        else if (token == rparen) {
            while (stack[top] != lparen)
                printToken(pop());
            pop();
        }
        else {
            while (isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }
    }
    while ((token = pop()) != eos)
        printToken(token); 
    printf("\n");
}

