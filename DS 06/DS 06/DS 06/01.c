// 2020118008 �ں���
// ������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

//fast transpose�� Ȱ���� �������� ��ġ��� ���ϱ�

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
	term A[MAX_TERMS]; //a[0]: �� ũ��, �� ũ��, 0�ƴ� ���� ����
	term B[MAX_TERMS]; //a�� ��ġ ��� b

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

//���Ϸκ��� �������� �Է¹���
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

//fast transpose�� �̿��� �������� ��ġ���
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

//����� ���
void printmatrix(term* C, int(*ary)[6])
{
	for (int i = 1; i <= C->value; i++)
	{
		ary[C[i].row][C[i].col] = C[i].value; //�������� ����� 1���� �迭�� ���� �̿��ؼ� 2���� �迭�� ���� ����
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

