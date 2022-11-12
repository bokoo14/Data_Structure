//1-1
#include <stdio.h>

int main(void)
{
	//2020118008박보경 
	//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

	//배열
	int arr[] = { 8,2,8 };
	//배열 포인터
	int* parr = arr;
	int i;

	printf("ary를 이용한 출력\n");
	for (i = 0; i < 3; i++)
		printf("%d ", arr[i]);

	printf("\n \n");

	printf("p를 이용한 출력\n");
	for (i = 0; i < 3; i++)
		printf("%d ", parr[i]);

	return 0;
}