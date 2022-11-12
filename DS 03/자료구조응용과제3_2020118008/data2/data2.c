//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

//program 1.24를 사용하여 선택정렬에 대한 성능측정

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<time.h>
#include "selectionSort.h"
#define MAX_SIZE 1001

void main(void)
{
	FILE* fp = fopen("char.txt", "w");
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration; 
	clock_t start;

	/* times for n=0, 10, ...., 100, 200, ...., 1000 */
	fprintf(fp, "   n   time\n");

	for (n = 0; n <= 2000; n += step) //n을 2000까지 증가시켜 데이터 생성
	{
		for (i = 0; i < n; i++) //n을 2000까지 증가시켜 데이터 생성
			a[i] = n - i;

		start = clock();
		sort(a, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;

		printf("%6d %6f\n", n, duration);
		fprintf(fp, "%6d %6f\n", n, duration);

		if (n == 100) step = 100;
	}

}






