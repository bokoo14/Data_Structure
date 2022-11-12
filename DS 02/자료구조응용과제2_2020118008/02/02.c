//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#include <stdio.h>
#include <stdlib.h>

float sum(float list[], int n)
{
	float tempsum = 0;
	int i;
	for (i = 0; i < n; i++)
		tempsum += list[i];
	return tempsum;
}

float rsum(float list[], int n)
{
	if (n) return rsum(list, n - 1) + list[n - 1];
	return 0;
}

int main(void)
{
	int n;
	float ss, rss;
	float list[10];

	printf("input>>");
	scanf_s("%d", &n);

	int j;
	for (j = 0; j < n; j++)
	{
		list[j] = (float)j+1;
	}

	ss = sum(list, n);
	rss = rsum(list, n);
	printf("sum: 1에서 %d까지의 정수 합은 %f\n",n, ss);
	printf("sum: 1에서 %d까지의 정수 합은 %f \n", n, rss);

	return 0;
}

