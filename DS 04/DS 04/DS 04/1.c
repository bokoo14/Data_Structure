//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

//�������� �Ҵ���� 2���� �迭�� �������� �Ҵ���� 2���� �迭�� �Լ��� �����ϴ� ����� ���ϴ� ���α׷� 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//�����Ҵ� �迭
int sumAry2D_f1(int ary2D[][3], int rows, int cols);
int sumAry2D_f2(int(*ary2D)[3], int rows, int cols);
int sumAry2D_f3(int ary2D[2][3], int rows, int cols);

//�����Ҵ� �迭
int sumAry2D_f4(int** ary, int rows, int cols);
int sumAry2D_f5(int*** ary, int rows, int cols);

//���� �޸� free
int freeAry2D(int ** ary, int rows);

int main(void)
{
	// �����Ҵ��� 2���� �迭(2��3��)
	int ary2D[2][3] = { {1, 2, 3}, {4, 5, 6} };

	// �����Ҵ��� 2���� �迭(2��3��)
	int r, c;
	int** ary = (int**)malloc(sizeof(int*) * 2);
	for (r = 0; r < 2; r++)
		ary[r] = (int*)malloc(sizeof(int) * 3);

	for (r = 0; r < 2; r++)
		for (c = 0; c < 3; c++)
			ary[r][c] = r + c;

	// �����Ҵ� �迭
	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary2D, 2, 3));

	// �����Ҵ� �迭
	printf("sumAry2D_f4() %d\n", sumAry2D_f4(ary, 2, 3));
	printf("sumAry2D_f5() %d\n", sumAry2D_f5(&ary, 2, 3));

	// �����Ҵ� �迭�� sumAry2D_f1, f2, f3�� ������ �� ������? �׽�Ʈ�غ���!
	//printf("sumAry2D_f1~f3() %d\n", sumAry2D_f1(ary, 2, 3));// ->������ �� ����

	// �����Ҵ� �迭�� sumAry2D_f4, f5�� ������ �� ������? �׽�Ʈ�غ���!
	//printf("sumAry2D_f4~f5() %d\n", sumAry2D_f4(ary2D, 2, 3));// ->������ �� ����

	freeAry2D(ary, 2); // �����Ҵ� �迭�� �޸� ����
	return 0;
}

//�����Ҵ� �迭
int sumAry2D_f1(int ary2D[][3], int rows, int cols) 
{
	int sum = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			sum += ary2D[i][j];
	return sum;

}
int sumAry2D_f2(int (*ary2D)[3], int rows, int cols)
{
	int sum = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			sum += ary2D[i][j];
	return sum;
}
int sumAry2D_f3(int ary2D[2][3], int rows, int cols) 
{
	int sum = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			sum += ary2D[i][j];
	return sum;
}

//�����Ҵ� �迭
int sumAry2D_f4(int **ary, int rows, int cols) 
{
	int sum = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			sum += ary[i][j];
	return sum;
}
int sumAry2D_f5(int ***ary, int rows, int cols) 
{
	int sum = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			sum += (*ary)[i][j];
	return sum;
}

int freeAry2D(int** ary, int rows)
{
	for (int i = 0; i < rows; i++)
			free(ary[i]);

	free(ary);
	printf("2d array-free!!!");
}