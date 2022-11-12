//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

//정적으로 할당받은 2차원 배열과 동적으로 할당받은 2차원 배열을 함수로 전달하는 방법을 비교하는 프로그램 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//정적할당 배열
int sumAry2D_f1(int ary2D[][3], int rows, int cols);
int sumAry2D_f2(int(*ary2D)[3], int rows, int cols);
int sumAry2D_f3(int ary2D[2][3], int rows, int cols);

//동적할당 배열
int sumAry2D_f4(int** ary, int rows, int cols);
int sumAry2D_f5(int*** ary, int rows, int cols);

//동적 메모리 free
int freeAry2D(int ** ary, int rows);

int main(void)
{
	// 정적할당의 2차원 배열(2행3열)
	int ary2D[2][3] = { {1, 2, 3}, {4, 5, 6} };

	// 동적할당의 2차원 배열(2행3열)
	int r, c;
	int** ary = (int**)malloc(sizeof(int*) * 2);
	for (r = 0; r < 2; r++)
		ary[r] = (int*)malloc(sizeof(int) * 3);

	for (r = 0; r < 2; r++)
		for (c = 0; c < 3; c++)
			ary[r][c] = r + c;

	// 정적할당 배열
	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary2D, 2, 3));

	// 동적할당 배열
	printf("sumAry2D_f4() %d\n", sumAry2D_f4(ary, 2, 3));
	printf("sumAry2D_f5() %d\n", sumAry2D_f5(&ary, 2, 3));

	// 동적할당 배열을 sumAry2D_f1, f2, f3로 전달할 수 있을까? 테스트해보라!
	//printf("sumAry2D_f1~f3() %d\n", sumAry2D_f1(ary, 2, 3));// ->전달할 수 없다

	// 정적할당 배열을 sumAry2D_f4, f5로 전달할 수 있을까? 테스트해보라!
	//printf("sumAry2D_f4~f5() %d\n", sumAry2D_f4(ary2D, 2, 3));// ->전달할 수 없다

	freeAry2D(ary, 2); // 동적할당 배열의 메모리 해제
	return 0;
}

//정적할당 배열
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

//동적할당 배열
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