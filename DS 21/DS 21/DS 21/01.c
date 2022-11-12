//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 21. Heap Sort (max heap)
* 
* <실행순서>
* ① 입력파일(input.txt)로부터 key를 읽어 들여 구조체 배열 a에 저장한다. 
* ※ element 타입은 key 필드만으로 구성된 구조체를 재정의한 것으로 가정한다.
* ② 각 레코드의 key에 대해 힙정렬을 실행한다. 
* ※ adjust 함수 수행마다 배열(a)의 인덱스 순서대로 key값을 화면에 출력한다. 
* ※ 출력함수를 정의하여 사용해야 한다. 
* ③ 정렬결과를 파일(output.txt)에 저장한다.
*/

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
   if( !( (p) = malloc( s ) ) ){   \
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX_SIZE 100

typedef struct element {
    int key;
}element;
element initList[100];

int stepcount = 0;

//heapsort
void adjust(element a[], int root, int n);
void heapSort(element a[], int n);


#include<stdio.h>
#include<stdlib.h>
int main()
{
    FILE* fp = NULL;

    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        fprintf(fp, "cannot file open");
        exit(EXIT_FAILURE);
    }

    //입력 키의 개수
    int num;
    fscanf(fp, "%d", &num);

    for (int i = 1; i < num+1; i++)
    {
        fscanf(fp, "%d", &initList[i].key);
    }

    printf("<<<<<Input List>>>>>\n");
    for (int i = 1; i < num+1; i++)
    {
        printf("%4d", initList[i].key);
    }
    printf("\n\n");


    printf("<<<<<executing heap sort>>>>>\n");
    printf("after initialization of max keap...\n");

    heapSort(initList, num);

    printf("\n<<<<<Sorted List>>>>>\n");
    for (int i = 1; i < num+1; i++)
    {
        printf("%4d", initList[i].key);
    }


    FILE* fo = fopen("output.txt", "w");
    for (int i = 1; i < num+1; i++)
    {
        fprintf(fo, "%3d", initList[i].key);
    }
    return 0;
}

//heapsort
void adjust(element a[], int root, int n) {
    int child, rootkey;
    element temp;

    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root;

    while (child <= n)
    {
        if ((child < n) && (a[child].key < a[child + 1].key))
            child++;
        if (rootkey > a[child].key)
            break;
        else {
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

void heapSort(element a[], int n) {
    int i = 0, j = 0;
    element temp;

    for (i = n / 2; i > 0; i--)
    {
        adjust(a, i, n); //max heap 초기화
    }
    for (int k = 1; k < n+1; k++)
    {
        printf("%3d", initList[k].key);
    }
    printf("\n\n");


    for (i = n - 1; i > 0; i--)
    {
        SWAP(a[1], a[i + 1], temp);
        adjust(a, 1, i);


        printf("step %3d: ", ++stepcount);
        for (int k = 1; k < n+1; k++)
        {
            printf("%3d", initList[k].key);
        }
        printf("\n");
    }
}