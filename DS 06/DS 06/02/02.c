// 2020118008 �ں���
// ������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

//�����Ҵ�迭�� ����

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
		op = strtok(input, delimiter); //���ڸ� �������� ���ڿ� �ڸ���(���� ���ڸ� �������� ���ڿ��� �ڸ�)

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

//������ �������
element stackEmpty()
{
	element item;
	item.id = -1;
	fprintf(stderr, "Stack is empty, cannot delete element");
	return item;
	exit(EXIT_FAILURE);
}

//������ ���� á���� pop()�� ����Ͽ� ���� ���ÿ�ҵ��� ����� �� �� exit�� ȣ��
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

//���� ���ÿ� ������ ����
void push(element item) 
{
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}

//���ÿ� �ִ� ���� pop
element pop()
{
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}
