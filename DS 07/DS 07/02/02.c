//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�. 

//�����Ҵ�迭�� �̿��� ȯ��ť(circular queue)

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 2
#define MAX_NAME_SIZE 10
#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }

typedef struct
{
	int id;
	char name[MAX_NAME_SIZE];
}element;

element* queue;

//�������� capacity, front, rear�� �ʱⰪ�� ���� 2, 0, 0
int capacity = 2;
int rear = 0;
int front = 0;
int cnt = 0; 

element queueEmpty();
void queueFull();
void addq(element item);
element deleteq();
void copy(element *a, element *b, element *c);

int main()
{
	char input[80];
	char* delimiter = " \n";
	char* op = NULL;
	element student;
	int cnt = 0;

	MALLOC(queue,  capacity*sizeof(*queue));

	printf("<<  Circular queue operations where MAX_QUEUE_SIZE is 2>>\n");
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

//ť�� �������
element queueEmpty()
{
	fprintf(stderr, "queue is empty, cannot delete element.\n");
	exit(EXIT_FAILURE);
}

//ť�� ���� á�� �� 
//queue capacity�� �� ��� Ȯ��
void queueFull() 
{
	int start;
	element* newQueue;
	//���� �޸� �Ҵ����� capacitiy�� 2��� Ȯ�� ����
	MALLOC(newQueue, 2 * capacity * sizeof(*queue));
	
	start = (front + 1) % capacity;

	if(start < 2)
		copy(queue + start, queue + start + capacity - 1, newQueue);
	else 
	{
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 1;
	capacity *= 2;

	printf("queue capacity is doubled \n");
	printf("current queue capacity is %d \n", capacity);

	free(queue);
	queue=newQueue;
}

//���� ť���� ����: rear
void addq(element item) 
{
	rear = (rear + 1) % capacity;
	if (front == rear)
		queueFull();
	queue[rear] = item;
}

//���� ť���� ����: delete
element deleteq()
{
	//front�� rear�� ������ ť�� �������
	if (front == rear)
		return queueEmpty();
	//����ť�� front�� �� ĭ ������ �ű�
	front = (front + 1) % capacity;
	printf("delete item: %d %s \n", queue[front].id, queue[front].name);
	return queue[front];
}

//a�� b�� ���� ���� ���� ������ c�� a�� copy
void copy(element *a, element *b, element *c) 
{
	while (a != b)
		*c++ = *a++;
}