//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

//�������� ��ġ����� ���ϴ� ���α׷�

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_TERMS 100

typedef struct
{
	int row; //��
	int col; //�� 
	int value; //��
}term;

int avail = 9;

void inputmatrix(term* A, char* fname);
void transpose(term a[], term b[]);
void printmatrix(term* C, int (*ary)[6]);
void inputFile(term* D, char* fname);

int main()
{
	//�������� ���� �迭(��, ��, ���� ����)
	term A[MAX_TERMS];
	term B[MAX_TERMS];

	char* filename1 = "a.txt";
	char* filename2 = "b.txt";

	//����� ���� ���(2���� �迭)
	int ary[7][6] = { 0 };
	int bry[7][6] = { 0 };

	//���Ϸκ��� �������� �Է¹���
	//���Ϸκ��� �Է¹��� ����� (��, ��)�� ���� �迭�� ����
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

//���Ϸκ��� �������� �Է¹���
//���Ϸκ��� �Է¹��� ����� (��, ��)�� ���� �迭�� ����
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

//��ġ����� ����
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

//����� ����Ʈ
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

//���Ͽ� �Է�
void inputFile(term* D, char* fname) 
{
	FILE* fp = fopen(fname, "w");

	for (int i = 0; i < avail; i++)
	{
		fprintf(fp, "%d %d %d\n", D[i].row, D[i].col, D[i].value);

	}

}