//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

//03
#include <stdio.h>

//1차원 배열을 매개변수에 전달
int sumAry1D_f1(int ary[], int size);
int sumAry1D_f2(int *ary, int size);
int sumAry1D_f3(int ary[6], int size);

int main(void)
{
	
	int ary1D[] = { 1, 2, 3, 4, 5, 6 };

	//배열의 이름 자체가 배열의 주소값
	//배열의 주소값을 전달해야 한다
	printf("sumAry1D_f1() %d\n", sumAry1D_f1(ary1D,6));
	printf("sumAry1D_f2() %d\n", sumAry1D_f2(ary1D, 6));
	printf("sumAry1D_f3() %d\n", sumAry1D_f3(ary1D, 6));

	return 0;

}

//배열원소의 합을 구하는 프로그램
int sumAry1D_f1(int ary[], int size)
{
	int sum = 0, i = 0;

	for (i = 0; i < size; i++)
	{
		sum += ary[i];
	}

	return sum;

}

int sumAry1D_f2(int *ary, int size)
{
	int sum = 0, i = 0;

	for (i = 0; i < size; i++)
	{
		sum += ary[i];
	}

	return sum;

}

int sumAry1D_f3(int ary[6], int size)
{
	int sum = 0, i = 0;

	for (i = 0; i < size; i++)
	{
		sum += ary[i];
	}

	return sum;

}






