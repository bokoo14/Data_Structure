//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�. 

//���� �Ҵ� �迭�� �̿��� ���� ť(linear queue)
//rear: ����   front: ����

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 5
#define MAX_NAME_SIZE 10

typedef struct
{
	int id;
	char name[MAX_QUEUE_SIZE];
}element;
element queue[MAX_QUEUE_SIZE];

//���� ť�� ��������� rear�� front�� ���� -1
int rear = -1;
int front = -1;
int cnt = 0;

element queueEmpty();
void queueFull();
element deleteq(); 
void addq(element item);

int main()
{
	char input[80];
	char* delimiter = " \n";
	char* op = NULL;
	element student;
	int cnt= 0;

	printf("<< linear queue operations where MAX_QUEUE_SIZE is 5>>\n");
	printf("add 1 Jung\n");
	printf("delete\n");
	printf("*************************************************\n");

	while (1)
	{
		gets(input);
		op = strtok(input, delimiter);

		if (!strcmp(op, "add"))
		{
			sscanf(input + strlen(op) + 1, "%d%s", &student.id, student.name);
			addq(student);
		}
		else if (!strcmp(op, "delete"))
		{
			element item;
			item = deleteq();
			cnt++;
			//if (item.id == -1)
				//queueEmpty();

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

//���� ť�� �������
element queueEmpty()
{
	fprintf(stderr, "queue is empty, cannot delete element.\n");
	exit(EXIT_FAILURE);
}

//���� ť�� ���� á����
void queueFull()
{
	//front�� ���� -1�̸� ���� ť�� ������ ���� á�ٴ� ���
	if (front == -1) 
	{
		fprintf(stderr, "Queue is full, cannot add element!\n");
		fprintf(stderr, "currnet queue element\n");
		for (int i = 0; i <= MAX_QUEUE_SIZE - 1; i++)
		{
			printf("%d  %s \n", queue[i].id, queue[i].name);
			deleteq();
		}

		exit(EXIT_FAILURE);
	}
	//front�� ���� -1�� �ƴ϶�� ���� ť�� array shifting���־�� �Ѵ�
	else
	{
		printf("array shifiting...\n");
		int f = front;
		int i = 0;
		for ( i = 0; i < (rear - front); i++)
		{
			queue[i] = queue[++f];
		}
		rear = i - 1;
		front = -1;
	}

}

//����ť�� enqueue()
void addq(element item)
{
	//���� ť���� rear�� ���� queue�� ������ index�� ����Ű�� ����������
	if (rear == MAX_QUEUE_SIZE - 1)
		queueFull();
	queue[++rear] = item;
}

//����ť�� dequeue()
element deleteq()
{
	//���� ť�� front�� rear�� ���� ������ �������
	if (front == rear)
		return queueEmpty();
	return queue[++front];

}
