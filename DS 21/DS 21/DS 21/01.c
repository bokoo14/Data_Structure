//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 21. Heap Sort (max heap)
* 
* <�������>
* �� �Է�����(input.txt)�κ��� key�� �о� �鿩 ����ü �迭 a�� �����Ѵ�. 
* �� element Ÿ���� key �ʵ常���� ������ ����ü�� �������� ������ �����Ѵ�.
* �� �� ���ڵ��� key�� ���� �������� �����Ѵ�. 
* �� adjust �Լ� ���ึ�� �迭(a)�� �ε��� ������� key���� ȭ�鿡 ����Ѵ�. 
* �� ����Լ��� �����Ͽ� ����ؾ� �Ѵ�. 
* �� ���İ���� ����(output.txt)�� �����Ѵ�.
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

    //�Է� Ű�� ����
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
        adjust(a, i, n); //max heap �ʱ�ȭ
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