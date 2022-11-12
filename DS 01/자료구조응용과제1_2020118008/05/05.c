//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
//05
#include <stdio.h>

//3차원 배열을 매개변수에 전달
//배열 포인터: 배열을 가르킬 수 있는 포인터
int sumAry3D_f1(int ary[][2][3], int SEC, int ROW, int COL);// 배열파라미터(권장)
int sumAry3D_f2(int(*ary)[2][3], int SEC, int ROW, int COL); // 배열포인터
int sumAry3D_f3(int ary[2][2][3], int SEC, int ROW, int COL);

int main(void)
{
	int ary3D[][2][3] = { {{1, 2, 3}, {4, 5, 6}},{{7, 8, 9}, {10, 11, 12}} };

	printf("sumAry3D_f1() %d\n", sumAry3D_f1(ary3D,2 ,2, 3));
	printf("sumAry3D_f2() %d\n", sumAry3D_f2(ary3D, 2, 2, 3));
	printf("sumAry3D_f3() %d\n", sumAry3D_f3(ary3D, 2, 2, 3));

	return 0;

}

int sumAry3D_f1(int ary[][2][3], int SEC, int ROW, int COL)
{
	int sum = 0, i = 0, j = 0, k = 0;

	for (i = 0; i < SEC; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			for (k=0; k<COL; k++)
			sum += ary[i][j][k];
		}
	}

	return sum;

}

int sumAry3D_f2(int(*ary)[2][3], int SEC, int ROW, int COL)
{

	int sum = 0, i = 0, j = 0, k = 0;

	for (i = 0; i < SEC; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			for (k = 0; k < COL; k++)
				sum += ary[i][j][k];
		}
	}

	return sum;

}

int sumAry3D_f3(int ary[2][2][3], int SEC, int ROW, int COL)
{
	int sum = 0, i = 0, j = 0, k = 0;

	for (i = 0; i < SEC; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			for (k = 0; k < COL; k++)
				sum += ary[i][j][k];
		}
	}

	return sum;

}
