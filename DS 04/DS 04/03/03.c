//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p,s)\
    if (!((p) = malloc(s))) {\
    	fprintf(stderr, "Insufficient memory.");\
        exit(EXIT_FAILURE);\
    }

void inputMatrix(int** ary, int rows, int cols); // 사용자 데이터 입력
void printMatrix(int** ary, int rows, int cols); // 행렬 출력
void addMatrix(int** a, int** b, int** c, int rows, int cols);
int** make2dArray(int rows, int cols); //동적할당으로 2차원 배열 생성하기
void free2dArray(int** ary, int rows); //동적할당 배열을 사용한 행렬 덧셈

int main()
{
	int rows, cols;
	int** a=0, ** b=0, ** c=0;

	printf("Enter row size and column size (ex) 2 3>> ");
	scanf("%d  %d", &rows, &cols);


	a = make2dArray(rows, cols);
	b= make2dArray(rows, cols);
	c= make2dArray(rows, cols);


	printf("Input data for 2 X 3 matrix A >>");
	inputMatrix(a, rows,cols);

	printf("Input data for 2 X 3 matrix B >>");
	inputMatrix(b, rows, cols);

	printf("matrix A\n");
	printMatrix(a, rows, cols);
	printf("   \n");


	printf("matrix B\n");
	printMatrix(b, rows, cols);
	printf("   \n");

	printf("matrix C\n");
	addMatrix(a, b, c, rows, cols);
	printMatrix(c, rows, cols);

	printf("   \n");


	free2dArray(a, rows);
	//free2dArray(b, rows);
	//free2dArray(a, rows);
	return 0;
}



void inputMatrix(int** ary, int rows, int cols) // 사용자 데이터 입력
{
	for(int i=0; i<rows;i++)
		for(int j=0; j<cols;j++)
			scanf("%d", &ary[i][j]);
}

void printMatrix(int** ary, int rows, int cols) // 행렬 출력
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			printf("%d  ", ary[i][j]);
		printf("  \n");
	}

}

void addMatrix(int** a, int** b, int** c, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}

int** make2dArray(int rows, int cols) //동적할당으로 2차원 배열 생성하기
{
	int** ary, i;
	MALLOC(ary, rows * sizeof(*ary)); // 매크로함수 MALLOC을 사용
	for (i = 0; i < rows; i++)
		MALLOC(ary[i], cols * sizeof(**ary));
	return ary;
}

void free2dArray(int** ary, int rows)
{
	for (int i = 0; i < rows; i++)
		free(ary[i]);

	free(ary);

	printf("2d array-free!!!");
}

