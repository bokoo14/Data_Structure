//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 19(2). Insertion sort
* 2. 다음과 같이 사용자로부터 데이터를 입력받아서 "삽입정렬(insertion sort)"을 수행한 결과를 출력 
* 각 레코드는 (key, name, grade)의 필드로 구성된다. (3점)
* 
* (1) 입력파일(input.txt)
* 
* (2) 실행순서
* ① 입력파일로부터 데이터를 읽어 들여 구조체 배열에 저장한다. 
* ② key에 대해 삽입정렬을 실행한다. 
* ③ 정렬된 순서대로 (key, name, grade)를 화면에 출력한다. 
* ④ 정렬결과를 파일(output.txt)에 저장한다.
*/


#define _CRT_SECURE_NO_WARNINGS

typedef struct element {
	int key;
	char name[10];
	int grade;
}element;
element e[100]; //구조체배열


void insert(element e, element a[], int i);
void insertionSort(element a[], int n);

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
	int a;
	fscanf(fp, "%d", &a);


	//key, name, grade순으로 입력받기 (배열의 1부터 저장, 0은 비워주기)
	int i = 1;
	while (fscanf(fp, "%d %s %d", &e[i].key, e[i].name, &e[i].grade) != EOF) {
		i++;
	}

	//입력된 값 출력 (배열의 1부터 저장, 0은 비워주기)
	printf("<<<<<Input List>>>>>\n");
	for (int i = 1; i < a+1; i++)
	{
		printf("<%d, %s, %d>\n", e[i].key, e[i].name, e[i].grade);
	}

	printf("\n");


	//구조체 배열, 구조체 배열의 갯수(정렬할 값들의 갯수) key값을 기준으로 정렬
	insertionSort(e, a);

	//정렬 후 출력 (배열의 1부터 저장, 0은 비워주기)
	printf("<<<<<Sorted List>>>>>\n");
	for (int i = 1; i < a+1; i++)
	{
		printf("<%d, %s, %d>\n", e[i].key, e[i].name, e[i].grade);
	}

	//파일에 저장 (배열의 1부터 저장, 0은 비워주기)
	FILE* fout = fopen("output.txt", "w");
	for (int k = 1; k < a+1; k++)
	{
		fprintf(fout, "( %d, %s, %d)\n", e[k].key, e[k].name, e[k].grade);
	}
	fclose(fout);

	return 0;
}


//key에 대해 삽입정렬
void insert(element e, element a[], int i) {
	//삽입할 값 임시 저장
	a[0] = e;
	//정렬할 값이 더 작으면 위치 이동시켜줌 "<-방향"으로 이동
	while (e.key < a[i].key)
	{
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

//삽입 정렬
void insertionSort(element a[], int n) {
	int j;

	//2~n까지 단계적으로 정렬해줌 "->방향"으로 이동
	for (j = 2; j <= n; j++)
	{
		element temp = a[j]; //각 단계에서 정렬할 값(j번째 원소)
		insert(temp, a, j - 1);
	}

}