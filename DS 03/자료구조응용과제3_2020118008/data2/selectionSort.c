//매크로 SWAP을 사용하는 sort함수 정의

#include "selectionSort.h"

void sort(int list[], int n) 
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i; //반복할때마다 min에 i값을 대입
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min]) //list의 j값과 min값을 비교
                min = j; //두 값 중 작은 값을 j에 대입
        SWAP(list[i], list[min], temp); //list[i]값에 작은 값을 교환
    }
}