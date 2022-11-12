//1-3
//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#include <stdio.h>

int main(void)
{
	//3차원 배열
	int arr[][2][3] = { 1,2,3,4,5,6,7,8,9,10,11,12};
	//3차원 배열 포인터: 3차원 배열의 주소값을 저장
	//배열의 주소를 저장할 수 있는 포인터
	int(*parr)[2][3] = arr;
	int i, j, k;

	printf("ary를 이용한 출력\n");
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			for (k = 0; k < 3; k++)
			{
				printf("%4d ", arr[i][j][k]);
			}
			printf("\n");

		}
		printf("\n");
	}

	printf("\n \n");

	printf("p를 이용한 출력\n");
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			for (k = 0; k < 3; k++)
			{
				printf("%4d ", parr[i][j][k]);
			}
			printf("\n");

		}
		printf("\n");
	}

	return 0;
}
