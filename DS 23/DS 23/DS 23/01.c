//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 23(1) Static Hashing - Random Probing
* 1. [Random Probing] 다음과 같은 division 해시함수와 Random Probing을 사용하는 해시테이블에 대해 
* search, insert 함수를 작성하고 그 결과를 출력하는 프로그램을 작성하라. (8점) 
* 
* 해싱함수(h(k)): k%b 키 탐색순서 - h(k), (h(k)+s(i))%b, 1≤i≤b-1, s(i)는 유사난수(pseudo random number)
* 
* 난수생성 : s(i)는 1≤i≤b-1 시퀀스에 대해 1에서 b-1 범위의 난수를 정확하게 한 번씩 생성해야 하며, 
* 매 탐색마다 동일한 seed를 사용하여야 함. 이러한 특징의 난수생성기를 직접 구현하는 대신, 
* C 언어의 srand, rand함수를 활용함
* 버킷 수 (b) : 8
* 슬롯 수 (s) : 1
* 
* <실행순서> 
* ① 해시테이블(ht)을 element* 타입의 구조체포인터 배열의 전역변수로 선언하고 초기화한다. 
* ※ element는 key 요소만으로 구성된 구조체이다. ※ 입력되는 key 값은 0보다 큰 정수이다. 
* ② 사용자로부터 seed를 입력받는다. ③ 1에서 b-1 범위의 난수 시퀀스를 중복 없이 생성해서 전역변수인 배열에 저장한다. 
* ④ 입력파일로부터 읽은 key값은 element 타입의 구조체를 동적으로 할당받아 저장하고 그 주소를 해당 버킷에 저장한다. 
* ※ h, s, insert 함수를 정의하여 사용
*  - 해싱테이블(ht)에 더 이상 추가할 수 없을 때는 적절한 메시지를 출력하고 종료한다.
*  - 중복된 key가 있을 경우에는 적절한 메시지를 출력하고 종료한다.
* ⑤ 해싱테이블을 최종 생성한 후 인덱스 순서대로 key를 출력하라.
* ⑥ 사용자로부터 키를 입력받아 탐색 후 (key, 비교횟수)를 출력하되 0이 입력될 때 까지 반복한다. 
* ※ search 함수를 정의하여 사용
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
element* ht[MAX]; //해시 테이블


int b = 8; //버킷 수 
int s = 1; //슬롯 수
int count = 0; //비교 횟수
int randNum[MAX]; //난수 생성하여 값을 저장


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


    //문자열을 입력받음
    int array[MAX];
    int i = 0;
    printf("input strings : ");
    while (fscanf(fp, "%d", &array[i]) != EOF)
    {
        printf("%7d", array[i]); //파일의 문자열 출력
        i++;
    }
    printf("\n");


    //1 ~ b-1범위의 난수를 중복 없이 생성해서 전역변수인 배열에 저장
    int seed;
    printf("input seed >> ");
    scanf("%d", &seed); //1을 입력
    srand(seed); // seed값 입력(1)
    int num;
    for (int i = 1; i < MAX; i++) {
        num = rand() % (MAX - 1) + 1; //난수 생성 1~(MAX-1)까지의 랜덤한 수를 생성
        randNum[i] = num; //전역변수 배열 randNum에 random값 저장

        for (int j = 1; j < i; j++)
        {
            if (randNum[i] == randNum[j])
                i--;
        }

    }
    //난수 출력
    for (int i = 1; i < MAX; i++) {
        printf("randNum[%2d] :  %d\n", i, randNum[i]);
    }


    //array배열의 값을 temp->key값에 저장
    for (int i = 0; i < 6; i++)
    {
        element* temp;
        MALLOC(temp, sizeof(*temp));

        temp->key = array[i];

        insert(temp->key, temp);
    }
    printf("\n\n");


    //해시 테이블 출력
    printf("                 key\n");
    for (i = 0; i < MAX; i++) { // hash table출력
        if (ht[i])
            printf("ht[%2d] : %10d\n", i, ht[i]->key);
        else // if (ht[i]==NULL) 
            printf("ht[%2d] : \n", i);
    }
    printf("\n");



    //찾기
    element* searchElement;
    int searchKey;
    while (1) {
        printf("input 0 to quit\n");
        printf("key to search >> ");
        scanf("%d", &searchKey);

        if (searchKey == 0)
            break;

        //버킷에 값이 있는 경우
        if (searchElement = search(searchKey)) {
            printf("key: % d, the number of comparisions : %d\n\n", searchElement->key, count);
            count = 0;
        }
        //버킷에 값이 없는 경우
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
insert 함수
- search(Program 8.3) 함수를 참고하여 구현
- 해싱테이블(ht)에 더 이상 추가할 수 없을 때는 적절한 메시지를 출력하고 종료한다.
- 중복된 key가 있을 경우에는 적절한 메시지를 출력하고 종료한다.
*/
void insert(int k, element* temp) {
    int homeBucket, currentBucket;
    homeBucket = h(k);
    int c = 1;
    /*"ht[currentBucket]의 값이 null이 아니고(채워져 있고), 찾는 값이 아닐 경우" 계속 반복 진행
    비어있으면-> 빠져나옴
    찾는 값이면-> 빠져나옴
    */
    for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k;)
    {
        currentBucket = (homeBucket + randNum[c++]) % b; //random probing

        //찾고 있는 bucket의 index가 처음(homeBucket)으로 돌아왔을때(bucket table이 가득 찼을때)
        if (currentBucket == homeBucket) {

            printf("\n\n");
            printf("해싱 테이블에 더 이상 추가할 수 없음! 종료!");
            exit(EXIT_FAILURE);
        }

    }

    //currentBucket이 비어있으면 현재의 값을 저장!
    if (ht[currentBucket] == NULL)
    {
        ht[currentBucket] = temp;
    }
    //중복된 키가 존재하면 출력을 하고 종료
    else
    {
        printf("\n\n");
        printf("중복된 키가 존재! 종료!");
        exit(EXIT_FAILURE);
    }
    
}

element* search(int k) {
    int homeBucket, currentBucket;
    homeBucket = h(k); //hash function의 값
    int r = 1;

    /*"ht[currentBucket]의 값이 null이 아니고(채워져 있고), 찾는 값이 아닐 경우" 계속 반복 진행
    비어있으면-> 빠져나옴
    찾는 값이면-> 빠져나옴
    */
    for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k;)
    {
        count++; //반복 수 세주기
        currentBucket = (homeBucket + randNum[r++]) % b; //random probing


        //찾고 있는 bucket의 index가 처음(homeBucket)으로 돌아왔을때(bucket table이 가득 찼을때)
        if (currentBucket == homeBucket) {
            return NULL;
        }
    }

    /*
    * 위의 반복문을 빠져 나왔을때
    * currentBucket의 값이 저장되어 있고
    * 찾는 값이면 ht[currentBucket] 리턴
    */
    if (ht[currentBucket] && ht[currentBucket]->key == k)
    {
        count++;
        return ht[currentBucket]; //반복 수 세주기
    }
    return NULL;
}