//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다. 

//정적 할당 배열을 이용한 선형 큐(linear queue)
//rear: 삽입   front: 삭제

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

//선형 큐가 비었을때는 rear와 front의 값은 -1
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

//선형 큐가 비었을때
element queueEmpty()
{
	fprintf(stderr, "queue is empty, cannot delete element.\n");
	exit(EXIT_FAILURE);
}

//선형 큐가 가득 찼을때
void queueFull()
{
	//front의 값이 -1이면 선형 큐가 완전히 가득 찼다는 얘기
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
	//front의 값이 -1이 아니라면 선형 큐를 array shifting해주어야 한다
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

//선형큐에 enqueue()
void addq(element item)
{
	//선형 큐에서 rear의 값이 queue의 마지막 index를 가리키면 가득차있음
	if (rear == MAX_QUEUE_SIZE - 1)
		queueFull();
	queue[++rear] = item;
}

//선형큐에 dequeue()
element deleteq()
{
	//선형 큐는 front와 rear의 값이 같으면 비어있음
	if (front == rear)
		return queueEmpty();
	return queue[++front];

}

