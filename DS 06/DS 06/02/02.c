// 2020118008 박보경
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

//정적할당배열의 스택

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 10

typedef struct 
{
	int id; 
	char name[MAX_NAME_SIZE];
}element;

element stack[MAX_STACK_SIZE];

int top = -1;

element stackEmpty();
void stackFull();
void push(element item);
element pop();


int main()
{
	char input[80];
	char* delimiter = " \n";
	char* op = NULL;
	element student;
	int cnt;

	printf("<< stack operations where MAX_SIZE is 5>>\n");
	printf("push 1 Jung\n");
	printf("pop\n");
	printf("*************************************************\n");

	while (1)
	{
		gets(input);
		op = strtok(input, delimiter); //문자를 기준으로 문자열 자르기(공백 문자를 기준으로 문자열을 자름)

		if (!strcmp(op, "push"))
		{
			sscanf(input + strlen(op) + 1, "%d%s", &student.id, student.name);
			push(student);
		}
		else if (!strcmp(op, "pop"))
		{
			element item;
			item = pop();
			if (item.id == -1)
				stackEmpty();
			
			//if (item.id == 1)
				//exit(EXIT_FAILURE);
		}
		else if (!strcmp(op, "quit"))
			break;
		else
			printf("wrong command!try again!\n");
	}

	return 0;
}

//스택이 비었을때
element stackEmpty()
{
	element item;
	item.id = -1;
	fprintf(stderr, "Stack is empty, cannot delete element");
	return item;
	exit(EXIT_FAILURE);
}

//스택이 가득 찼을때 pop()을 사용하여 현재 스택요소들을 출력해 준 후 exit을 호출
void stackFull()
{
	fprintf(stderr, "Stack is full, cannot add element\n");
	fprintf(stderr, "currnet stack element\n");
	for (int i = MAX_STACK_SIZE-1; i >= 0; i--)
	{
		printf( "%d  %s \n", stack[i].id, stack[i].name);
		pop();
	}
	
	exit(EXIT_FAILURE);
}

//전역 스택에 아이템 삽입
void push(element item) 
{
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}

//스택에 있는 값을 pop
element pop()
{
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}

