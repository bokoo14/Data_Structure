//1-2
#include <stdio.h>

int main(void)
{
	//2020118008박보경 
	//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

	int arr[][3] = { 4,2,3,5,2,3 };
	//배열 포인터: 2차원 배열의 주소값을 저장 
	int(*parr)[3] = arr;
	int i, j;

	printf("ary를 이용한 출력\n");
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	printf("\n \n");

	printf("p를 이용한 출력\n");
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d ", parr[i][j]);

		}
		printf("\n");
	}

	return 0;
}
