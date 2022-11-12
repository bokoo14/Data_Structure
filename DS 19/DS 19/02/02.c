//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 19(4). Quick sort
* 위 3번 입력리스트의 데이터를 파일로 입력받아 퀵정렬 수행결과 및 quickSort 함수호출 회수를 구하여 출력
* 단, 각 레코드는 하나의 int형 key 필드로 구성되어 있다. (3점)
* 
* (1) 입력파일(input.txt) 
* 
* (2) 실행순서
* ① 입력파일(input.txt)로부터 데이터를 읽어 들여 구조체 배열 a에 저장한다.
* ② 각 레코드의 key에 대해 퀵정렬을 실행한다. 
* ③ 정렬된 key값 및 quickSort 함수호출 회수를 화면에 출력하라. 
* ④ 정렬결과를 파일(output.txt)에 저장한다.
* 
*/

#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))


typedef struct element {
	int key;
}element;
element e[20];

int cnt =0; //함수가 호출되는 수
int q=0; //원소의 수
void quickSort(element a[], int left, int right);

#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE* fp = NULL;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open file");
		exit(EXIT_FAILURE);
	}

	//갯수를 입력받음 
	fscanf(fp, "%d", &q);

	for (int m = 0; m < q; m++)
	{
		fscanf(fp, "%d", &e[m].key);
	}
	
	
	printf("<<<<<Input List>>>>>\n");
	for (int i = 0; i < q; i++)
	{
		printf("%3d", e[i].key);
	}

	printf("\n\n");


	printf("executive of quick sort...\n");
	for (int i = 1; i < q+1; i++)
	{
		printf(" [%2d] ", i);
	}
	printf(" [left right] \n");


	quickSort(e, 0, q-1 );

	printf("calls of quick sort: %d", cnt);


	FILE* fout = fopen("output.txt", "w");

	fprintf(fout, "%2d\n", q);
	for (int k = 0; k < q ; k++)
	{
		fprintf(fout, "%3d", e[k].key);
	}
	fclose(fout);

	return 0;
}

void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;


	cnt++; //몇번 함수가 호출되었는지 세어줌

	//quickSort를 할때마다 값들을 출력해줌
	for (int k = 0; k < q; k++)
	{
		printf("%6d", a[k]);
	}
	printf(": %3d %3d ", left+1, right+1);
	printf("\n");
	
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = a[left].key;
		do {
			do i++; while (a[i].key < pivot); //key값이 더 클때까지
			do j--; while (a[j].key > pivot); //key값이 더 작을때까지
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}

}