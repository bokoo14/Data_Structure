//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�


/* 
* 15(2) �������� ���� 
* 2. [�������� ����(Satisfiability Problem)] postfix expression�� �������� ���Ϸκ��� �Է¹޾� 
* ����Ʈ���� �����Ͽ� ������ȸ(inorder traversal)�� ����� ȭ�鿡 ��� �� ��,
* �������ɹ����� ��� ���տ� ���� ����� ȭ�鿡 ����ϴ� ���α׷��� �ۼ��϶�. (12��)
* 
* [�Է����� �� ����Ʈ��]
* - �Է�����(postfix.txt) : ab~&a~c&|c~| 
* - �ǿ�����(Operands) : ���ĺ� �ҹ���
* - ������(Operators) : & | ~
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
// ���� true ���� false���� ���
void postOrderEval(treePointer node, logical aData, logical bData, logical cData);


//�������� ����Ʈ�� ����
char expr[MAX_EXPR_SIZE];
char post[MAX_EXPR_SIZE];

int index = 0;

typedef enum {lparen, rparen, or , and, not, eos, operand }precedence;


//������ �ޱ�
precedence getToken(char* symbol, int* n);
void printToken(precedence token);

//���� Ʈ�� ����
treePointer createBinTree(void);

//stack
int top = -1;
treePointer stack[MAX_STACK_SIZE];
void push(treePointer item);
treePointer pop();
void stackFull();
treePointer stackEmpty();


//���� Ʈ�� ��ȸ
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
// ���� true ���� false���� ���
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
 
// (, ), |, &, ~, \0 ���� �޾ƿͼ� precedence�� ��ȯ�Ѵ�
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

//����Ʈ�� ����
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
        if (token == operand)// �ǿ�����
        {
            // operand node
            MALLOC(pNode, sizeof(*pNode));
            pNode->var = symbol;		// propositional variables a, b, c			
            pNode->leftChild = NULL;
            pNode->rightChild = NULL;

            push(pNode); /* stack insert */
        }
        else if (token != operand) //������
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


//������ȸ�� ����� ȭ�鿡 ���
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