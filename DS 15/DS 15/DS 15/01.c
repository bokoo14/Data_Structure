//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/*15.(1) 충족가능 문제
*  1. 괄호를 포함한 infix expression의 명제식을 파일로부터 입력받아 후위표현식(postfix expression)으로 변환하여 화면 및 파일로 출력하는 프로그램을 작성하라. (3점) 
* ※ 중간고사 2번 문제와 동일(본인 제출 소스를 그대로 다운받아 사용 가능)
* 
* [구현세부사항]
* ① 주어진 실습문제 소스파일( ds16_1_student.c )을 수정하여 구현한다. 
* ※ 수정 : precedence, isp, icp, getTocken, printTocken
* ② logical and(&&), logical or(||), logical not (!)을 &, |, ~으로 대신하여 사용한다. 
* ※ 교재 p.130, Figure 3.12 연산자 우선순위 : || < && < ! 
* ※ 괄호가 없는 경우에도 제대로 우선순위를 반영하도록 구현되어야 함
* ③ postfix expression은 괄호를 포함하지 않는다. ④ 반드시 화면 및 파일(postfix.txt)로 같이 출력되어야 한다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80

char expr[MAX_EXPR_SIZE]; //파일에 저장된 infix expression
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

//연산자 받기
precedence getToken(char* symbol, int* n);
void printToken(precedence token);
void postfix(void);

int main(void)
{
    //파일으 끝까지 expr배열에 명제식을 받아옴
    FILE* fp;
    int i = 0;
    if ((fp = fopen("infix.txt", "r")) == NULL)
    {
        fprintf(stderr, "cannot open the file");
        exit(EXIT_FAILURE);
    }
    while (fscanf(fp, "%c ", &expr[i++]) != EOF) {}


    printf("<<<<<< infix to postfix >>>>>>\n");
    printf("infix expression     :%s", expr); //파일에 저장되어 있는 명제식 출력(expr배열 출력)
    printf("\n");

    //후위표현식으로 변경
    printf("postfix expression   :");
    postfix();

    //파일에 후위표현식이 저장되어 있는 post저장
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
* 연산자 받기
* precedence의 값(and or not)을 받아서 item에 저장하여 출력
* item의 값(&, |, ~)을 post배열에 저장한다
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

// (, ), |, &, ~, \0 값을 받아와서 precedence를 반환한다
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

//후위표기법으로 바꿔서 post에 넣는다
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


