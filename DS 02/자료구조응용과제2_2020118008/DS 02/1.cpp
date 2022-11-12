//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX_SIZE 100
//x<y이면 -1, x=y이면 0 x>y이면 1 리턴
#define COMPARE(x,y) (((x)<(y))? -1:((x)==(y))? 0 : 1)

void sort(int list[], int); //selction sort 선택정렬
int binsearh(int list[], int searchnum, int left, int right);
int binarysearch2(int list[], int searchnum, int left, int right);

int main(void)
{
	int i, n;
	int list[MAX_SIZE];
	printf("Enter the number of numbers to generates:");
	//몇개의 data를 받을지 
	scanf_s("%d", &n);

	if ((n < 1) || (n > MAX_SIZE))
	{
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);

	}

	//n개의 수를 받아서 난수 생성을 한 후, list[i]에 넣음
	for (i = 0; i < n; i++)
	{
		list[i] = rand() % 1000;
		printf("%d  ", list[i]);
	}

	//선택 정렬
	sort(list, n);
	printf("\n Sorted array:\n");

	/*print out sorted numbers*/
	for (i = 0; i < n; i++)
		printf("%d  ", list[i]);
	printf("\n");

	int bin1, bin2;
	int a;

	printf("배열 안에 원하는 값이 존재하는가?\n");
	printf("원하는 값: ");
	scanf_s("%d", &a);

	//0~n-1까지의 값 중에서 a값을 탐색
	//함수 swap, compare와 반복문을 사용한 이진탐색을 구현
	bin1 = binsearh(list, a, 0, n - 1);
	printf("%d\n", bin1);

	//0~n-1까지의 값 중에서 a값을 탐색
	//매크로 SWAP, COMPARE와 재귀호출을 사용한 이진탐색을 구현
	bin2 = binarysearch2(list, a, 0, n - 1);
	printf("%d\b", bin2);

	return 0;
}

void sort(int list[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j; //비교해서 더 작은걸 min에 넣어줌
		SWAP(list[i], list[min], temp); //i번째에 작은 원소를 넣어줌 
	}
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int compare(int x, int y)//y가 더 크면 -1 리턴 같으면 0리턴 x가 더 크면 1리턴
{
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}

int binsearh(int list[], int searchnum, int left, int right)//swap, compare와 반복문을 사용한 이진탐색
{
	int middle;
	while (left <= right)
	{
		middle = (left + right) / 2;
		switch (compare(list[middle], searchnum))
		{
		case -1: left = middle + 1;
			break;
		case 0: return middle;
		case 1: right = middle - 1;
		}
	}
	return -1;
}

int binarysearch2(int list[], int searchnum, int left, int right) //매크로 SWAP, COMPARE와 재귀호출을 사용한 이진탐색
{
	int middle;
	if (left <= right)
	{
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum))
		{
		case -1: return  binarysearch2(list, searchnum, middle + 1, right);
		case 0: return middle;
		case 1: return  binarysearch2(list, searchnum, left, middle - 1);
		}
	}
	return -1;
}