//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 20. Merge Sort "iterative" �պ� ���� �ݺ���
* (1) mergeSort(Program 7.9)�� while ������ �� mergePass ȣ�� ���� �迭 a�� extra�� ���¸� �ܰ������� ��Ÿ����
* �ʱ� �Է� �����ʹ� �迭 a[1:n] �� �ִ�. 
* 
* <�������>
* �� �Է�����(input.txt)�κ��� key�� �о� �鿩 ����ü �迭 a�� �����Ѵ�.
* �� element Ÿ���� key �ʵ常���� ������ ����ü�� �������� ������ �����Ѵ�.
* 
* �� �� ���ڵ��� key�� ���� �ݺ��� ���� �պ������� �����Ѵ�.
* �̶�, mergeSort �Լ��� �����Ͽ� mergePass ���ึ�� ���׸�Ʈ ũ��(s), �迭 a�� extra ���¸� ȭ�鿡 ����϶�.
* �� ���� ���İ���� ȭ�鿡 ����Ѵ�.
* 
*/
#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
	if( !( (p) = malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define MAX_SIZE 100

typedef struct element{
	int key;
}element;
element initList[100];
element mergedList[100];

//mergesort
void merge(element initList[], element mergedList[], int i, int m, int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void mergeSort(element a[], int n);

#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE* fp = NULL;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(fp, "cannot file open");
		exit(EXIT_FAILURE);
	}

	//�Է� Ű�� ����
	int a;
	fscanf(fp, "%d", &a);

	for (int i = 1; i < a+1; i++)
	{
		fscanf(fp, "%d", &initList[i].key);
	}

	printf("<<<<<Input List>>>>>\n");
	for (int i = 1; i < a+1; i++)
	{
		printf("%4d", initList[i].key);
	}
	printf("\n\n");

	printf("<<<<<executing iterative merge sort>>>>>\n");
	mergeSort(initList, a);

	printf("<<<<<Sorted List>>>>>\n");
	for (int i = 1; i < a+1; i++)
	{
		printf("%4d", initList[i].key);
	}
	return 0;
}

//mergesort
void merge(element initList[], element mergedList[], int i, int m, int n)
{
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].key <= initList[j].key)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m)
		for (t = j; t <= n; t++) {
			mergedList[t] = initList[t];
		}
	else
		for (t = i; t <= m; t++) {
			mergedList[k + t - i] = initList[t];
		}
}

void mergePass(element initList[], element mergedList[], int n, int s)
{
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	else
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];
}


void mergeSort(element a[], int n) {
	int s = 1;
	element extra[MAX_SIZE];

	while (s < n)
	{
		
		mergePass(a, extra, n, s);
		printf("segment size: %d\n", s);
		s *= 2;


		printf("     a: ");
		for (int k = 1; k < n + 1; k++)
		{
			printf("%5d", a[k].key);
		}
		printf("\n");

		printf(" extra: ");
		for (int k = 1; k < n + 1; k++)
		{
			printf("%4d ", extra[k].key);
		}
		printf("\n\n");
		


		mergePass(extra, a, n, s);
		printf("segment size: %d\n", s);
		s *= 2;
		printf(" extra: ");
		for (int k = 1; k < n+1; k++)
		{
			printf("%4d ", extra[k].key);
		}
		printf("\n");

		printf("     a: ");
		for (int k = 1; k < n+1 ; k++)
		{
			printf("%5d", a[k]);
		}
		printf("\n\n");
	
	}
}