//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 16(1) �ִ�����
* 1. �Է� ������ �����͸� ����Ͽ� "�ִ�����"�� ���� �ǽ��� ����
* 
* [�������]
* �� �����Է��� �����鼭 �ִ������� �����Ѵ�.
* �� �Է¸���, ������ �ִ������� �迭���Ҹ� �ε��� ������� ����Ѵ�. 
* �� �ִ������� �ִ밪�� �������� ���Ұ�����ŭ �����Ѵ�.
* �� ��������, �籸���� �ִ������� �迭���Ҹ� �ε��� ������� ����Ѵ�.
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
	//�����Է��� �����鼭 �ִ������� �����Ѵ�
	while (fscanf(fp, "%d", &item) != EOF)
	{
		push(item, &n);
		//�� �Է¸���, ������ �ִ������� �迭���Ҹ� �ε��� ������� ����Ѵ�
		for (int i = 1; i <= n; i++)
		{
			printf("%d ", heap[i].key);
		}
		printf("\n");
	}


	printf("***** deletion from a max heap ***** \n");
	while (n > 0)
	{
		//�ִ������� �ִ밪�� �������� ���Ұ�����ŭ �����Ѵ�
		item = pop(&n);
		//�� ��������, �籸���� �ִ������� �迭���Ҹ� �ε��� ������� ����Ѵ�
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

	//i�� 1�� ����
	i = ++(*n);

	/*
	* while��) ���� �������� ���� �θ��庸�� ũ�� �θ����� ��ġ�� ����
	* �ڽ� ����� �ڸ�(index i)�� �θ� ���(index i/2)�� ���� ����
	* �θ� ����� �ڸ�(index i/2)�� item�� ����
	* 
	* ���� �������� ���� �θ��庸�� ������
	* �׳� �ڽ� ����� �ڸ�(index)�� item�� ����
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

	//heap���� �����ϴ� ���� �׻� ��Ʈ ���
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