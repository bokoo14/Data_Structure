//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 20. Merge Sort "iterative" 합병 정렬 반복적
* (1) mergeSort(Program 7.9)의 while 문에서 각 mergePass 호출 후의 배열 a와 extra의 상태를 단계적으로 나타내기
* 초기 입력 데이터는 배열 a[1:n] 에 있다. 
* 
* <실행순서>
* ① 입력파일(input.txt)로부터 key를 읽어 들여 구조체 배열 a에 저장한다.
* ※ element 타입은 key 필드만으로 구성된 구조체를 재정의한 것으로 가정한다.
* 
* ② 각 레코드의 key에 대해 반복을 통한 합병정렬을 실행한다.
* 이때, mergeSort 함수를 수정하여 mergePass 수행마다 세그먼트 크기(s), 배열 a와 extra 상태를 화면에 출력하라.
* ③ 최종 정렬결과를 화면에 출력한다.
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

	//입력 키의 개수
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