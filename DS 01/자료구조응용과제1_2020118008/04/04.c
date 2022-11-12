//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

//04
#include <stdio.h>

//2차원 배열을 매개변수에 전달
//배열 포인터: 배열을 가르킬 수 있는 포인터
int sumAry2D_f1(int ary[][3], int ROW, int COL); // 배열파라미터 (권장)
int sumAry2D_f2(int(*ary)[3], int ROW, int COL); // 배열포인터
int sumAry2D_f3(int ary[2][3], int ROW, int COL);

int main(void)
{
	int ary2D[][3] = { {1, 2, 3}, {4, 5, 6} };

	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary2D, 2, 3));

	return 0;

}

//배열의 모든 값을 더해주는 함수
int sumAry2D_f1(int ary[][3], int ROW, int COL)
{
	int sum = 0, i = 0, j = 0;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			sum += ary[i][j];
		}
	}

	return sum;

}

int sumAry2D_f2(int(*ary)[3], int ROW, int COL)
{
	int sum = 0, i = 0, j = 0;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			sum += ary[i][j];
		}
	}

	return sum;

}

int sumAry2D_f3(int ary[2][3], int ROW, int COL)
{
	int sum = 0, i = 0, j = 0;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			sum += ary[i][j];
		}
	}

	return sum;

}


