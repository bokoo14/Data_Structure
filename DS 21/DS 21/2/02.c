//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 21(2) Radix sort (LSD)
* 
* <�������>
* �� �Է�����(input.txt)�κ��� �����͸� �о� �鿩 ����ü �迭 a�� �����Ѵ�
* �� element Ÿ���� key �ʵ常���� ������ ����ü�� �������� ������ �����Ѵ�. 
* �� Ʃ�ʹ� �ٸ� d �Է¿� ���� �׽�Ʈ�Ͽ��� �Ѵ�. 
* �� �� ���ڵ��� key�� ���� ��������� �����Ѵ�. 
* �� (a)(b)(c)(d) �� �ܰ谡 ���� ���� ü���� Key���� link ������� ȭ�鿡 ����϶�.
* �� ���� ����� ����(output.txt)�� �����Ѵ�.
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

//ù��° �� �޾ƿ���
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

    //ù�� ��: d, n
    fscanf(fp, "%d %d", &aa, &bb);

    //��° ��: key ����Ʈ ����ü �迭�� ����
    for (int i = 1; i < bb + 1; i++)
    {
        fscanf(fp, "%d", &initList[i].key);
    }
    MALLOC(link, sizeof(link) * bb); //������ �����

    //������� bin�� 10
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
* �� printList �Լ�
- a, link �迭�� ���� �ε��� ������� ���
- first�� ���
- ���ĵ� ����� chain ������� ���
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


/*�� printQueues �Լ�
- front, rear �迭�� ���� �ε��� ������� ���
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

/*�� digit �Լ�
- ���Ϸκ��� �Էµ� ������ d�� ���ؼ��� ����ǵ��� �� ��
- �ʿ��ϴٸ� �Լ��� �Ķ���͸� �߰��� �� ����
- r�� 10�� ��쿡 ���ؼ��� �����ϸ� ��
*/
int digit(element a, int i, int r) {
 
    int quotient;

    quotient = a.key;
    for (int m = 0; m < aa-i-1; m++)
        quotient = quotient / r;

    return  quotient % r;
}