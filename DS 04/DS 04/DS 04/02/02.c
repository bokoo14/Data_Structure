//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>

void input2dArray(int ary[][3], int rows, int cols); // 사용자 데이터 입력
void print2dArray(int ary[][3], int rows, int cols); // 행렬 출력
void add(int a[][3], int b[][3], int c[][3], int rows, int cols);

int main(void)
{
	int a[2][3], b[2][3], c[2][3];

	printf("input data for 2 X 3 matrix X A>> ");
	input2dArray(a, 2, 3);

	printf("input data for 2 X 3 matrix X B>> ");
	input2dArray(b, 2, 3);

	printf(" \n");

	printf("matrix A\n");
	print2dArray(a, 2, 3);

	printf("matrix B\n");
	print2dArray(b, 2, 3);

	printf("matrix C\n");
	add(a, b, c, 2, 3);
	print2dArray(c, 2, 3);


	return 0;
}


void input2dArray(int ary[][3], int rows, int cols) // 사용자 데이터 입력
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			scanf("%d", &ary[i][j]);
} 

void print2dArray(int ary[][3], int rows, int cols) // 행렬 출력
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			printf("%d  ", ary[i][j]);
		printf(" \n");
	}


}
void add(int a[][3], int b[][3], int c[][3], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}