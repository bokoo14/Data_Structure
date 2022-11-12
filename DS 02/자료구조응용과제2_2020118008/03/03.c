//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#include <stdio.h>
#include <stdlib.h>

int alloc(int x);
void input(int* pNum, int size, FILE* fp);
void output(int* pNum, int size, FILE* fp);
void increase(int* pNum, int size);

int main(void)
{
	int num, * pNum;
	FILE* fpIn = fopen("input.txt", "r");
	FILE* fpOut = fopen("output.txt", "w");

	fscanf(fpIn, "%d", &num); //데이터 갯수
	pNum = alloc(num); //num크기만큼 메모리 할당. 동적 메모리 할당받은 데이터를 pNum에 저장
	//pNum = (int*)malloc(sizeof(int) * num);
	input(pNum, num, fpIn); //파일로부터 num개 데이터 입력
	increase(pNum, num); //각 데이터를 1씩 증가
	output(pNum, num, fpOut); //증가된 데이터를 파일출력

	free(pNum);
	fclose(fpIn);
	fclose(fpOut);

	return 0;;
}

//num크기만큼 메모리 할당
int alloc(int x) 
{
	int* p = (int*)malloc(sizeof(int) * x);
	return p;
}

//파일로부터 num개 데이터 입력
void input(int* pNum, int size, FILE* fp)
{
	int x;
	for (int i = 0; i < size; i++)
	{
		fscanf(fp, "%d ", &x);
		pNum[i] = x;
		printf("%3d", x);
	}
	printf("\n");
}

//각 데이터를 1씩 증가
void increase(int* pNum, int size) 
{
	for (int i = 0; i < size; i++)
	{
		pNum[i] = pNum[i] + 1;
		printf("%3d", pNum[i]);
	}
	printf("\n");
}

//증가된 데이터를 파일출력
void output(int* pNum, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		fprintf(fp, "%d ", pNum[i]);
		printf("%3d", pNum[i]);
	}
}
