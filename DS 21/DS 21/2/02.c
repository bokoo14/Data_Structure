//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 21(2) Radix sort (LSD)
* 
* <실행순서>
* ① 입력파일(input.txt)로부터 데이터를 읽어 들여 구조체 배열 a에 저장한다
* ※ element 타입의 key 필드만으로 구성된 구조체를 재정의한 것으로 가정한다. 
* ※ 튜터는 다른 d 입력에 대해 테스트하여야 한다. 
* ② 각 레코드의 key에 대해 기수정렬을 실행한다. 
* ※ (a)(b)(c)(d) 각 단계가 끝난 후의 체인의 Key값을 link 순서대로 화면에 출력하라.
* ③ 정렬 결과를 파일(output.txt)에 저장한다.
*/

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
   if( !( (p) = malloc( s ) ) ){   \
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

typedef struct element {
    int key;
}element;
element initList[100];
int *link;

int* front, * rear;
int first=1;

//첫번째 줄 받아오기
int aa, bb;

//radixsort
int radixSort(element a[], int link[], int d, int r, int n);

void printList();
void printQueues();
int digit(element a, int i, int d);

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main()
{
    FILE* fp = NULL;

    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        fprintf(fp, "cannot file open");
        exit(EXIT_FAILURE);
    }

    //첫쨰 줄: d, n
    fscanf(fp, "%d %d", &aa, &bb);

    //둘째 줄: key 리스트 구조체 배열에 저장
    for (int i = 1; i < bb + 1; i++)
    {
        fscanf(fp, "%d", &initList[i].key);
    }
    MALLOC(link, sizeof(link) * bb); //포인터 만들기

    //기수정렬 bin은 10
    radixSort(initList, link, aa, 10, bb);

    FILE* fo = fopen("output.txt", "w");

    for (int i = 1; i < bb + 1; i++)
    {
        fprintf(fo, "%3d", initList[i].key);
    }
    return 0;
}

//radixsort
int radixSort(element a[], int link[], int d, int r, int n) {
    MALLOC(front, sizeof(front) * r);
    MALLOC(rear, sizeof(rear) * r);

    int i, bin, current, last;
    first = 1;
    int pass = 1;


    for (i = 1; i < n; i++)
        link[i] = i + 1;
    link[n] = 0;
    printf("****************initial chain****************\n");
    printList();


    for (i = d - 1; i >= 0; i--)
    {
        for (bin = 0; bin < r; bin++) {
            front[bin] = 0;
            rear[bin] = 0;
        }

        for (current = first; current; current = link[current])
        {
            bin = digit(a[current], i, r);
            if (front[bin] == 0) front[bin] = current;
            else link[rear[bin]] = current;
            rear[bin] = current;
        }

        for (bin = 0; !front[bin]; bin++);
            first = front[bin]; last = rear[bin];
       

        for (bin++; bin < r; bin++)
            if (front[bin])
            {
                link[last] = front[bin]; last = rear[bin];
            }
        link[last] = 0;

        printf("*************** pass %d ***************\n", pass++);
        printList();
        printQueues();
    }

    return first;
}

/*
* ② printList 함수
- a, link 배열에 대해 인덱스 순서대로 출력
- first를 출력
- 정렬된 결과를 chain 순서대로 출력
*/
void printList() {
    printf("        ");
    for (int k = 1; k <= bb; k++)
    {
        printf("[%2d]", k);
    }
    printf("\n");

    printf("   link:");
    for (int i = 1; i <= bb; i++)
    {
        printf("%4d", link[i]);
    }
    printf("\n");

    printf("      a:");
    for (int i = 1; i < bb+1; i++)
    {
        printf("%4d", initList[i].key);
    }
    printf("\n");

    printf("  first: %d\n\n", first);

    printf("result: ");
    int current = first;
    while (current != 0)
    {
        printf("%4d", initList[current].key);
        current = link[current];
    }
    printf("\n\n");

}


/*③ printQueues 함수
- front, rear 배열에 대해 인덱스 순서대로 출력
*/
void printQueues() {
    printf("        ");
    for (int k = 0; k < 10; k++)
    {
        printf("[%2d]", k);
    }
    printf("\n");

    printf("  rear:");
    for (int i = 0; i<10; i++)
    {
        printf("%4d", rear[i]);
    }
    printf("\n");

    printf(" front:");
    for (int i = 0; i < 10; i++)
    {
        printf("%4d", front[i]);
    }
    printf("\n\n");
}

/*④ digit 함수
- 파일로부터 입력된 임의의 d에 대해서도 실행되도록 할 것
- 필요하다면 함수의 파라미터를 추가할 수 있음
- r이 10인 경우에 대해서만 구현하면 됨
*/
int digit(element a, int i, int r) {
 
    int quotient;

    quotient = a.key;
    for (int m = 0; m < aa-i-1; m++)
        quotient = quotient / r;

    return  quotient % r;
}