//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

//3행 4열의 행렬 2개(a.txt, b.txt)를 파일 입력받아 행렬 더하기 함수의 program step count를 계산하여 출력하는 프로그램

#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#define MAX_SIZE 4

void add(int a[][MAX_SIZE], int b[][MAX_SIZE], int c[][MAX_SIZE], int rows, int cols);

int main() 
{
	int a[3][MAX_SIZE], b[3][MAX_SIZE], c[3][MAX_SIZE];
	FILE* fp1 = fopen("a.txt", "r");
	FILE* fp2 = fopen("b.txt", "r");
	FILE* fp3 = fopen("c.txt", "w");
	
	//행(3), 열(4)만큼 파일의 내용을 배열에 받아옴
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fscanf(fp1, "%d", &a[i][j]); //a의 파일 내용을 받아옴 (3행 4열)
			fscanf(fp2, "%d", &b[i][j]); //b의 파일 내용을 받아옴 (3행 4열) 
		}
	}

	//program step count를 계산해주는 함수
	//a[3][4]+b[3][4]를 계산한 행렬을 c[3][4]에 넣음
	add(a, b, c, 3, 4);

	//행렬 c[3][4]를 파일 fp3에 넣음
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fprintf(fp3, "%d ", c[i][j]);
		}
		fprintf(fp3, " \n");
	}

	return 0;
}


void add(int a[][MAX_SIZE], int b[][MAX_SIZE], int c[][MAX_SIZE], int rows, int cols){

	int count = 0;
	int i, j;
	for (i = 0; i < rows; i++)
	{
		count++; //for i for loop :총 3
		for (j = 0; j < cols; j++)
		{
			count++; //for j for loop :총 12
			c[i][j] = a[i][j] + b[i][j];
			count++; //for assignment statement :총 12
		}
		count++; //last time of j for loop :총 3
	}
	count++; //last time of i for loop : 총 1

	printf("%d", count);
	//step count: 31출력
}

//program 1.17
//위의 코드를 간략화시킨 것
/*void add(int a[][MAX_SIZE], int b[][MAX_SIZE], int c[][MAX_SIZE], int rows, int cols) {

	int count = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
			count += 2;
		}
		count += 2;
	}
	count++;
	printf_s("step count: %d", count);
}*/