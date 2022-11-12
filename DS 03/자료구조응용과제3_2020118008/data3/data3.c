//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<time.h>
#include "selectionSort.h"
#define MAX_SIZE 1000


void main(void)
{

	FILE* fp = fopen("char2.txt", "w");
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;

	/* times for n=0, 10, ...., 100, 200, ...., 1000 */
	fprintf(fp, "     n       reputations time\n");

	printf("     n       reputations time\n");
	for (n = 0; n <= 2000; n += step) //n을 2000까지 증가시켜 데이터 생성
	{
		long repetitons = 0;
		clock_t start=clock();
		do
		{
			repetitons++;
			for (i = 0; i < n; i++) //n을 2000까지 증가시켜 데이터 생성
				a[i] = n - i;
			sort(a, n);
		} while (clock() - start < 1000);
	
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;

		duration /= repetitons;

		printf("%6d %9d %f\n", n, repetitons,duration);
		fprintf(fp, "%6d %9d %f\n", n, repetitons,duration);

		if (n == 100) step = 100;
	}

}
