//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다


/* 
* 15(2) 충족가능 문제 
* 2. [충족가능 문제(Satisfiability Problem)] postfix expression의 명제식을 파일로부터 입력받아 
* 이진트리를 구성하여 중위순회(inorder traversal)한 결과를 화면에 출력 한 후,
* 충족가능문제의 모든 조합에 대한 결과를 화면에 출력하는 프로그램을 작성하라. (12점)
* 
* [입력파일 및 이진트리]
* - 입력파일(postfix.txt) : ab~&a~c&|c~| 
* - 피연산자(Operands) : 알파벳 소문자
* - 연산자(Operators) : & | ~
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p, s) \
	if( !( (p) = malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 81

//satisfiability problem 
#define TRUE 1
#define FALSE 0
typedef enum { NOT, AND, OR, true, false }logical;

typedef struct node* treePointer;
typedef struct node {
    treePointer leftChild;
    char var; //a, b, c
    logical data; //AND, OR, NOT, true, false
    short int value; //TRUE, FALSE
    treePointer rightChild;
}tNode;

treePointer root = NULL;
logical aData, bData, cData;


//satisfiability problem
//program 5.9 postorder evaluation function
// 값이 true 인지 false인지 계산
void postOrderEval(treePointer node, logical aData, logical bData, logical cData);


//명제식의 이진트리 생성
char expr[MAX_EXPR_SIZE];
char post[MAX_EXPR_SIZE];

int index = 0;

typedef enum {lparen, rparen, or , and, not, eos, operand }precedence;


//연산자 받기
precedence getToken(char* symbol, int* n);
void printToken(precedence token);

//이진 트리 생성
treePointer createBinTree(void);

//stack
int top = -1;
treePointer stack[MAX_STACK_SIZE];
void push(treePointer item);
treePointer pop();
void stackFull();
treePointer stackEmpty();


//이진 트리 순회
void inorder(treePointer ptr);

int main(void)
{

    int result;
    FILE* fp;

    if ((fp = fopen("postfix.txt", "r")) == NULL)
    {
        fprintf(stderr, "cannot open the file");
        exit(EXIT_FAILURE);
    }

    printf("************* satisfiability problem ************\n");
    printf("Note: For efficienccy, &, |, ~ are used instead of \nlogical and(&&),logical or(||), logical not (!)\n");
    printf("*************************************************\n");
    int i = 0;
    while (fscanf(fp, "%c", &expr[i++]) != EOF) {}
    printf("input string(postfix)");
    printf("%s \n", expr);

    printf("creating binary tree for satisfiability algorithm...\n\n");
    root = createBinTree();

    printf("inorder traversal: ");
    inorder(root);
    printf("\n\n");


    printf("for all combinations of(a, b, c)...\n");
    printf("(t, t, t) is ");
    postOrderEval(root, true, true, true);
    if (root->value == 1)
        printf("TRUE");
    else if (root->value == 0)
        printf("FALSE");
    printf("\n");

    printf("(t, t, f) is ");
    postOrderEval(root, true, true, false);
    if (root->value == 1)
        printf("TRUE");
    else if (root->value == 0)
        printf("FALSE");
    printf("\n");

    printf("(t, f, t) is ");
    postOrderEval(root, true, false, true);
    if (root->value == 1)
        printf("TRUE");
    else if (root->value == 0)
        printf("FALSE");
    printf("\n");

    printf("(t, f, f) is ");
    postOrderEval(root, true, false, false);
    if (root->value == 1)
        printf("TRUE");
    else if (root->value == 0)
        printf("FALSE");
    printf("\n");

    printf("(f, t, t) is ");
    postOrderEval(root, false, true, true);
    if (root->value == 1)
        printf("TRUE");
    else if (root->value == 0)
        printf("FALSE");
    printf("\n");

    printf("(f, t, f) is ");
    postOrderEval(root, false, true, false);
    if (root->value == 1)
        printf("TRUE");
    else if (root->value == 0)
        printf("FALSE");
    printf("\n");

    printf("(f, f, t) is ");
    postOrderEval(root, false, false, true);
    if (root->value == 1)
        printf("TRUE");
    else if (root->value == 0)
        printf("FALSE");
    printf("\n");

    printf("(f, f, f) is ");
    postOrderEval(root, false, false, false);
    if (root->value == 1)
        printf("TRUE");
    else if (root->value == 0)
        printf("FALSE");
    printf("\n");
    return 0;
}

//satisfiability problem
//program 5.9 postorder evaluation function
// 값이 true 인지 false인지 계산
void postOrderEval(treePointer node, logical aData, logical bData, logical cData)
{
    if (node)
    {
        if (node->var == 'a')
        {
            node->data = aData;
        }
        else if (node->var == 'b')
        {
            node->data = bData;
        }
        else if (node->var == 'c')
        {
            node->data = cData;
        }

        postOrderEval(node->leftChild, aData, bData, cData);
        postOrderEval(node->rightChild, aData, bData, cData);

        switch (node->data)
        {
        case NOT: node->value = !node->rightChild->value;
            break;
        case AND: node->value = node->rightChild->value && node->leftChild->value;
            break;
        case OR: node->value = node->rightChild->value || node->leftChild->value;
            break;
        case true: node->value = TRUE;
            break;
        case false: node->value = FALSE;
        }
    }
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
    case or :
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
{
    *symbol = expr[(*n)++];
    switch (*symbol)
    {
    case '&': return and;		// use '&' as the logical and(&&) 
    case '|': return or ;		// use '|' as the logical or(||)
    case '~': return not;		// use '~' as the logical not(!)
    case '\0': return eos;
    default: return operand; /* no error checking, default is operand */
    }
}

//이진트리 생성
treePointer createBinTree(void)
{
    treePointer pNode;
    precedence token;
    char symbol;
    int n = 0; /* counter for the expression string */
    top = -1;
    token = getToken(&symbol, &n);
    while (token != eos)
    {
        if (token == operand)// 피연산자
        {
            // operand node
            MALLOC(pNode, sizeof(*pNode));
            pNode->var = symbol;		// propositional variables a, b, c			
            pNode->leftChild = NULL;
            pNode->rightChild = NULL;

            push(pNode); /* stack insert */
        }
        else if (token != operand) //연산자
        {
            if (token == not )
            { // unary operator - not
                MALLOC(pNode, sizeof(*pNode));
                pNode->data = NOT;					// operator, data is logical data type
                pNode->rightChild = pop();		// link operand
                pNode->leftChild = NULL;		// link operand
            }
            else
            { // binary operator - and or
                MALLOC(pNode, sizeof(*pNode));

                if (token == and)
                    pNode->data = AND;			// operator
                else if (token == or)
                    pNode->data = OR;

                pNode->rightChild = pop();		// link operand op2
                pNode->leftChild = pop();		// link operand op1
            }
            push(pNode);
        }
        token = getToken(&symbol, &n);
    }
    return pop();
}


//stack
treePointer pop()
{/* delete and return the top int from the stack */
    if (top == -1)
        return stackEmpty();	/* returns an error key */
    return stack[top--];
}

treePointer stackEmpty()
{
    treePointer item;
    item = NULL;  // error key value - null pointer
    return item;
}

void push(treePointer item)
{/* add an item to the global stack */
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

void stackFull()
{
    fprintf(stderr, "stack is full, cannot add item\n");
    exit(EXIT_FAILURE);
}


//중위순회한 결과를 화면에 출력
void inorder(treePointer ptr)
{
    if (ptr)
    {
        inorder(ptr->leftChild);


        if (ptr->data == NOT)
            printf("~");
        else if (ptr->data == AND)
            printf("&");
        else if (ptr->data == OR)
            printf("|");

        if (ptr->var == 'a')
            printf("a");
        else if (ptr->var == 'b')
            printf("b");
        else if (ptr->var == 'c')
            printf("c");


        inorder(ptr->rightChild);
    }
}