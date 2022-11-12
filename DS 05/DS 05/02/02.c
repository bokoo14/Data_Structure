//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

//희소행렬의 전치행렬을 구하는 프로그램

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_TERMS 100

typedef struct
{
	int row; //행
	int col; //열 
	int value; //값
}term;

int avail = 9;

void inputmatrix(term* A, char* fname);
void transpose(term a[], term b[]);
void printmatrix(term* C, int (*ary)[6]);
void inputFile(term* D, char* fname);

int main()
{
	//희소행렬을 위한 배열(행, 열, 값을 저장)
	term A[MAX_TERMS];
	term B[MAX_TERMS];

	char* filename1 = "a.txt";
	char* filename2 = "b.txt";

	//출력을 위한 행렬(2차원 배열)
	int ary[7][6] = { 0 };
	int bry[7][6] = { 0 };

	//파일로부터 희소행렬을 입력받음
	//파일로부터 입력받은 행렬의 (행, 열)의 값을 배열에 저장
	inputmatrix(A, filename1);

	transpose(A, B);

	printf("A \n");
	printmatrix(A, ary);

	printf("\n");

	printf("B \n");
	printmatrix(B, bry);


	char* filenameB = "b.txt";
	inputFile(B, filename2);
	
	return 0;
}

//파일로부터 희소행렬을 입력받음
//파일로부터 입력받은 행렬의 (행, 열)의 값을 배열에 저장
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

//전치행렬을 구함
void transpose(term a[], term b[])
{
	int n, i, j, currentb;
	n = a[0].value;
	b[0].row = a[0].col;
	b[0].col = a[0].row;
	b[0].value = n;

	if (n > 0)
	{
		currentb = 1;
		for (i = 0; i < a[0].col; i++)
			for (j = 1; j <= n; j++)
				if (a[j].col == i)
				{
					b[currentb].row = a[j].col;
					b[currentb].col = a[j].row;
					b[currentb].value = a[j].value;
					currentb++;
				}
	}
}

//행렬을 프린트
void printmatrix(term *C, int (*ary)[6])
{
	for (int i = 1; i <= C->value; i++)
	{
		ary[C[i].row][C[i].col] = C[i].value;
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

//파일에 입력
void inputFile(term* D, char* fname) 
{
	FILE* fp = fopen(fname, "w");

	for (int i = 0; i < avail; i++)
	{
		fprintf(fp, "%d %d %d\n", D[i].row, D[i].col, D[i].value);

	}

}
