//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 23(1) Static Hashing - Random Probing
* 1. [Random Probing] ������ ���� division �ؽ��Լ��� Random Probing�� ����ϴ� �ؽ����̺��� ���� 
* search, insert �Լ��� �ۼ��ϰ� �� ����� ����ϴ� ���α׷��� �ۼ��϶�. (8��) 
* 
* �ؽ��Լ�(h(k)): k%b Ű Ž������ - h(k), (h(k)+s(i))%b, 1��i��b-1, s(i)�� ���糭��(pseudo random number)
* 
* �������� : s(i)�� 1��i��b-1 �������� ���� 1���� b-1 ������ ������ ��Ȯ�ϰ� �� ���� �����ؾ� �ϸ�, 
* �� Ž������ ������ seed�� ����Ͽ��� ��. �̷��� Ư¡�� ���������⸦ ���� �����ϴ� ���, 
* C ����� srand, rand�Լ��� Ȱ����
* ��Ŷ �� (b) : 8
* ���� �� (s) : 1
* 
* <�������> 
* �� �ؽ����̺�(ht)�� element* Ÿ���� ����ü������ �迭�� ���������� �����ϰ� �ʱ�ȭ�Ѵ�. 
* �� element�� key ��Ҹ����� ������ ����ü�̴�. �� �ԷµǴ� key ���� 0���� ū �����̴�. 
* �� ����ڷκ��� seed�� �Է¹޴´�. �� 1���� b-1 ������ ���� �������� �ߺ� ���� �����ؼ� ���������� �迭�� �����Ѵ�. 
* �� �Է����Ϸκ��� ���� key���� element Ÿ���� ����ü�� �������� �Ҵ�޾� �����ϰ� �� �ּҸ� �ش� ��Ŷ�� �����Ѵ�. 
* �� h, s, insert �Լ��� �����Ͽ� ���
*  - �ؽ����̺�(ht)�� �� �̻� �߰��� �� ���� ���� ������ �޽����� ����ϰ� �����Ѵ�.
*  - �ߺ��� key�� ���� ��쿡�� ������ �޽����� ����ϰ� �����Ѵ�.
* �� �ؽ����̺��� ���� ������ �� �ε��� ������� key�� ����϶�.
* �� ����ڷκ��� Ű�� �Է¹޾� Ž�� �� (key, ��Ƚ��)�� ����ϵ� 0�� �Էµ� �� ���� �ݺ��Ѵ�. 
* �� search �Լ��� �����Ͽ� ���
*/
#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
   if( !( (p) = malloc( s ) ) ){   \
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }
#define MAX 8

typedef struct element {
    int key; 
}element;
element* ht[MAX]; //�ؽ� ���̺�


int b = 8; //��Ŷ �� 
int s = 1; //���� ��
int count = 0; //�� Ƚ��
int randNum[MAX]; //���� �����Ͽ� ���� ����


//hashfunction
int h(int k);

element* search(int k);
void insert(int k, element* temp);


#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main()
{

    FILE* fp = NULL;

    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "cannot open the file");
        exit(EXIT_FAILURE);
    }


    //���ڿ��� �Է¹���
    int array[MAX];
    int i = 0;
    printf("input strings : ");
    while (fscanf(fp, "%d", &array[i]) != EOF)
    {
        printf("%7d", array[i]); //������ ���ڿ� ���
        i++;
    }
    printf("\n");


    //1 ~ b-1������ ������ �ߺ� ���� �����ؼ� ���������� �迭�� ����
    int seed;
    printf("input seed >> ");
    scanf("%d", &seed); //1�� �Է�
    srand(seed); // seed�� �Է�(1)
    int num;
    for (int i = 1; i < MAX; i++) {
        num = rand() % (MAX - 1) + 1; //���� ���� 1~(MAX-1)������ ������ ���� ����
        randNum[i] = num; //�������� �迭 randNum�� random�� ����

        for (int j = 1; j < i; j++)
        {
            if (randNum[i] == randNum[j])
                i--;
        }

    }
    //���� ���
    for (int i = 1; i < MAX; i++) {
        printf("randNum[%2d] :  %d\n", i, randNum[i]);
    }


    //array�迭�� ���� temp->key���� ����
    for (int i = 0; i < 6; i++)
    {
        element* temp;
        MALLOC(temp, sizeof(*temp));

        temp->key = array[i];

        insert(temp->key, temp);
    }
    printf("\n\n");


    //�ؽ� ���̺� ���
    printf("                 key\n");
    for (i = 0; i < MAX; i++) { // hash table���
        if (ht[i])
            printf("ht[%2d] : %10d\n", i, ht[i]->key);
        else // if (ht[i]==NULL) 
            printf("ht[%2d] : \n", i);
    }
    printf("\n");



    //ã��
    element* searchElement;
    int searchKey;
    while (1) {
        printf("input 0 to quit\n");
        printf("key to search >> ");
        scanf("%d", &searchKey);

        if (searchKey == 0)
            break;

        //��Ŷ�� ���� �ִ� ���
        if (searchElement = search(searchKey)) {
            printf("key: % d, the number of comparisions : %d\n\n", searchElement->key, count);
            count = 0;
        }
        //��Ŷ�� ���� ���� ���
        else
        {
            printf("it doesn't exist!\n\n");
        }
    }


    return 0;
}


//hashfunction
int h(int k)
{
    return k % b;
}

/*
insert �Լ�
- search(Program 8.3) �Լ��� �����Ͽ� ����
- �ؽ����̺�(ht)�� �� �̻� �߰��� �� ���� ���� ������ �޽����� ����ϰ� �����Ѵ�.
- �ߺ��� key�� ���� ��쿡�� ������ �޽����� ����ϰ� �����Ѵ�.
*/
void insert(int k, element* temp) {
    int homeBucket, currentBucket;
    homeBucket = h(k);
    int c = 1;
    /*"ht[currentBucket]�� ���� null�� �ƴϰ�(ä���� �ְ�), ã�� ���� �ƴ� ���" ��� �ݺ� ����
    ���������-> ��������
    ã�� ���̸�-> ��������
    */
    for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k;)
    {
        currentBucket = (homeBucket + randNum[c++]) % b; //random probing

        //ã�� �ִ� bucket�� index�� ó��(homeBucket)���� ���ƿ�����(bucket table�� ���� á����)
        if (currentBucket == homeBucket) {

            printf("\n\n");
            printf("�ؽ� ���̺��� �� �̻� �߰��� �� ����! ����!");
            exit(EXIT_FAILURE);
        }

    }

    //currentBucket�� ��������� ������ ���� ����!
    if (ht[currentBucket] == NULL)
    {
        ht[currentBucket] = temp;
    }
    //�ߺ��� Ű�� �����ϸ� ����� �ϰ� ����
    else
    {
        printf("\n\n");
        printf("�ߺ��� Ű�� ����! ����!");
        exit(EXIT_FAILURE);
    }
    
}

element* search(int k) {
    int homeBucket, currentBucket;
    homeBucket = h(k); //hash function�� ��
    int r = 1;

    /*"ht[currentBucket]�� ���� null�� �ƴϰ�(ä���� �ְ�), ã�� ���� �ƴ� ���" ��� �ݺ� ����
    ���������-> ��������
    ã�� ���̸�-> ��������
    */
    for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k;)
    {
        count++; //�ݺ� �� ���ֱ�
        currentBucket = (homeBucket + randNum[r++]) % b; //random probing


        //ã�� �ִ� bucket�� index�� ó��(homeBucket)���� ���ƿ�����(bucket table�� ���� á����)
        if (currentBucket == homeBucket) {
            return NULL;
        }
    }

    /*
    * ���� �ݺ����� ���� ��������
    * currentBucket�� ���� ����Ǿ� �ְ�
    * ã�� ���̸� ht[currentBucket] ����
    */
    if (ht[currentBucket] && ht[currentBucket]->key == k)
    {
        count++;
        return ht[currentBucket]; //�ݺ� �� ���ֱ�
    }
    return NULL;
}