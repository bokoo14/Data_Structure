// 2020118008 박보경
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

//fast transpose를 활용한 희소행렬의 전치행렬 구하기

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
#define MAX_COL 6

typedef struct
{
	int row;
	int col;
	int value;
}term;

int avail = 9;

void inputmatrix(term* A, char* fname);
void fastTranspose(term a[], term b[]);
void printmatrix(term* C, int(*ary)[6]);
void inputFile(term* D, char* fname);


int main()
{
	term A[MAX_TERMS]; //a[0]: 행 크기, 열 크기, 0아닌 항의 개수
	term B[MAX_TERMS]; //a의 전치 행렬 b

	char* filename1 = "a.txt";
	char* filename2 = "b.txt";

	int ary[7][6] = { 0 };
	int bry[7][6] = { 0 };


	inputmatrix(A, filename1);

	fastTranspose(A, B);

	printf("A \n");
	printmatrix(A, ary);

	printf("\n");

	printf("B \n");
	printmatrix(B, bry);


	inputFile(B, filename2);


	return 0;

}

//파일로부터 희소행렬을 입력받음
void inputmatrix(term* A, char* fname) 
{

	FILE* fp = fopen(fname, "r");

	int row2, col2, value2;

	for (int i = 0; i < avail; i++)
	{
		fscanf_s(fp, "%d %d %d ", &row2, &col2, &value2);
		A[i].row = row2;
		A[i].col = col2;
		A[i].value = value2;
	}
}

//fast transpose를 이용한 희소행렬의 전치행렬
void fastTranspose(term a[], term b[])
{
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row=numCols; b[0].col = a[0].row;
	b[0].value = numTerms;

	if (numTerms > 0)
	{
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col] ++;

		startingPos[0] = 1;

		for (i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

		for (i = 1; i <= numTerms; i++)
		{
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col; b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

//행렬을 출력
void printmatrix(term* C, int(*ary)[6])
{
	for (int i = 1; i <= C->value; i++)
	{
		ary[C[i].row][C[i].col] = C[i].value; //희소행렬이 저장된 1차원 배열의 값을 이용해서 2차원 배열에 값을 저장
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			printf("%d ", ary[i][j]);
		}
		printf("\n");
	}
}


void inputFile(term* D, char* fname)
{
	FILE* fp = fopen(fname, "w");

	for (int i = 0; i < avail; i++)
	{
		fprintf(fp, "%d %d %d\n", D[i].row, D[i].col, D[i].value);

	}

}


