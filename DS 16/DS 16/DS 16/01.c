//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 16(1) 최대히프
* 1. 입력 파일의 데이터를 사용하여 "최대히프"에 대한 실습을 수행
* 
* [실행순서]
* ① 파일입력을 받으면서 최대히프를 구성한다.
* 매 입력마다, 구성된 최대히프의 배열원소를 인덱스 순서대로 출력한다. 
* ② 최대히프의 최대값을 연속으로 원소개수만큼 삭제한다.
* 매 삭제마다, 재구성된 최대히프의 배열원소를 인덱스 순서대로 출력한다.
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENTS 200

#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key; 
}element;

element heap[MAX_ELEMENTS];


//insertion into a max heap
void push(element item, int* n);
//deletion from a max heap
element pop(int* n);

#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE* fp = fopen("input.txt", "r");
	element item;
	int n = 0;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	printf("***** insertion into a max heap *****\n");
	//파일입력을 받으면서 최대히프를 구성한다
	while (fscanf(fp, "%d", &item) != EOF)
	{
		push(item, &n);
		//매 입력마다, 구성된 최대히프의 배열원소를 인덱스 순서대로 출력한다
		for (int i = 1; i <= n; i++)
		{
			printf("%d ", heap[i].key);
		}
		printf("\n");
	}


	printf("***** deletion from a max heap ***** \n");
	while (n > 0)
	{
		//최대히프의 최대값을 연속으로 원소개수만큼 삭제한다
		item = pop(&n);
		//매 삭제마다, 재구성된 최대히프의 배열원소를 인덱스 순서대로 출력한다
		for (int i = 1; i <= n; i++)
		{
			printf("%d ", heap[i].key);
		}
		printf("\n");
	}
	return 0;
}

//insertion into a max heap
void push(element item, int* n)
{
	int i;
	if (HEAP_FULL(*n))
	{
		fprintf(stderr, "The heap is full. \n");
		exit(EXIT_FAILURE);
	}

	//i값 1씩 증가
	i = ++(*n);

	/*
	* while문) 현재 넣으려는 값이 부모노드보다 크면 부모노드의 위치에 삽입
	* 자식 노드의 자리(index i)에 부모 노드(index i/2)의 값을 대입
	* 부모 노드의 자리(index i/2)에 item을 대입
	* 
	* 현재 넣으려는 값이 부모노드보다 작으면
	* 그냥 자식 노드의 자리(index)에 item을 대입
	*/
	while ((i != 1) && (item.key > heap[i / 2].key))
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

// Deletion from a max heap
element pop(int* n)
{
	int parent, child;
	element item, temp;

	if (HEAP_EMPTY(*n))
	{
		fprintf(stderr, "The heap is empty. \n");
		exit(EXIT_FAILURE);
	}

	//heap에서 삭제하는 노드는 항상 루트 노드
	item = heap[1];

	temp = heap[(*n)--];
	parent = 1;
	child = 2;

	while (child <= *n)
	{ 
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
			child++;
		if (temp.key >= heap[child].key) break;

		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}

	heap[parent] = temp;
	return item;
}
