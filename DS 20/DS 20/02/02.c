//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 20. Merge Sort: recursive 합병정렬 재귀적
* 
* <실행순서>
* ① 입력파일(input.txt)로부터 key를 읽어 들여 구조체 배열 a에 저장한다. 
* ※ element 타입은 key 필드만으로 구성된 구조체를 재정의한 것으로 가정한다.
* ② 각 레코드의 key에 대해 재귀적인 합병정렬을 실행한다. 
* ※ Program 7.11코드 수정 : if( a[last1] <= a[last2] ) -> if( a[last1].key <= a[last2].key )
* ③ 실행예와 같이 합병정렬 과정을 볼 수 있도록 rmergeSort함수 등을 적절하게 수정하여 RLV, LRV 방식 두 가지 경우에 대해 각각 실행결과를 보여라.
*/

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
	if( !( (p) = malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define MAX_SIZE 100

typedef struct element {
	int key;
}element;
element initList[100];
int link[100] = {0};


int start1, start2;

//recursive merge sort
int rmergeSort(element a[], int link[], int left, int right);
int listMerge(element a[], int link[], int start1, int start2);

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
	int num;
	fscanf(fp, "%d", &num);
	

	for (int i = 1; i < num+1; i++)
	{
		fscanf(fp, "%d", &initList[i].key);
	}

	printf("<<<<<starting from initial %d chain. >>>>>\n", num);
	printf("<<<<<each of which has one node>>>>>\n");
	printf("      ");
	for (int i = 0; i < num+1; i++)
	{
		printf("[%2d]", i);
	}
	printf("\n");

	printf("link:");
	for (int i = 0; i < num + 1; i++)
	{
		printf("%4d", link[i]);
	}
	printf("\n");

	printf("  a:    -");
	for (int i = 1; i < num+1; i++)
	{
		printf("%4d", initList[i].key);
	}
	printf("\n\n");


	printf("<<<<<executing iterative merge sort>>>>>\n");
	rmergeSort(initList, link, 1, num);


	printf("<<<<<Sorted List>>>>>\n");
	int cnt = 0;
	int i = 0;
	for (int cnt = 0; cnt < num; cnt++)
	{
		printf("%3d", initList[link[i]]);
		i = link[i];
	}
	return 0;
}

// Program 7.10 의 수정함수
int rmergeSort(element a[], int link[], int left, int right)
{
	printf("rmergeSort<a, link, %3d, %3d>\n", left, right);

	int mid, mergedSorted, leftSorted, rightSorted;
	if (left >= right) return left;
	mid = (left + right) / 2;
	// case 1: RLV
	rightSorted = rmergeSort(a, link, mid + 1, right); // sort right half
	leftSorted = rmergeSort(a, link, left, mid); // sort left half
	mergedSorted = listMerge(a, link, leftSorted, rightSorted);
	/*
	// case 2: LRV
	leftSorted = rmergeSort(a, link, left, mid); // sort left half
	rightSorted = rmergeSort(a, link, mid + 1, right); // sort right half
	mergedSorted = listMerge(a, link, leftSorted, rightSorted );
	*/
	return mergedSorted;
}


int listMerge(element a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;
	printf("\nlistMerged <a, link, %d, %d>\n", start1, start2);
	
	for(last1= start1, last2=start2; last1&&last2;)
		if (a[last1].key <= a[last2].key)
		{
			link[lastResult] = last1;
			lastResult = last1; last1 = link[last1];
		}
		else
		{
			link[lastResult] = last2;
			lastResult = last2; last2 = link[last2];
		}

	if (last1 == 0) link[lastResult] = last2;
	else link[lastResult] = last1;


	int num = 10;
	printf("      ");
	for (int i = 0; i < num+1; i++)
	{
		printf("[%2d]", i);
	}
	printf("\n");

	printf("link:");
	for (int i = 0; i < num + 1; i++)
	{
		printf("%4d", link[i]);
	}
	printf("\n");

	printf("  a:    -");
	for (int i = 1; i < num+1; i++)
	{
		printf("%4d", initList[i].key);
	}
	printf("\n\n");


	return link[0];


}