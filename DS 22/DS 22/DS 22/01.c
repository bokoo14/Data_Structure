//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/*
* 22. Static Hashing – Linear Probing (10점)
[ Linear Probing ] 다음과 같은 해시함수와 Linear Probing을 사용하는 해시테이블에
대해 search, insert 함수를 작성하고 그 결과를 출력하는 프로그램을 작성하라. (10점)

<실행순서>
① 전역변수로 해시테이블(ht)을 초기화하고, MAX 기호상수를 11로 정의한다. 
② 입력파일로부터 읽은 각 문자열과 key값은 element 타입의 구조체를 동적으로 할당받아 저장하고 그 주소를 해당 버킷에 저장한다.
③ 해싱테이블을 최종 생성한 후 인덱스 순서대로 (item, key)를 출력한다.
④ 사용자로부터 문자열을 입력받아 탐색 후 (item, key, 비교횟수)를 출력한다.


<함수정의>
insert 함수
- search(Program 8.3) 함수를 참고하여 구현
- 해싱테이블(ht)에 더 이상 추가할 수 없을 때는 적절한 메시지를 출력하고 종료한다. 
- 중복된 key가 있을 경우에는 적절한 메시지를 출력하고 종료한다.
*/


#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
	if( !( (p) = malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define MAX 11

typedef struct element {
	char item[MAX]; //입력 문자열
	int key; //키 변환함수의 반환 값
}element;
element *ht[MAX]; //해시 테이블


int b = 11; //버킷 수 
int s = 1; //슬롯 수
int count = 0; //비교 횟수

//hashfunction
int h(int k);
//String to Integer
unsigned int stringToInt(char* key);

element* search(int k);
void insert(int k, element* temp);


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

    //문자열을 입력받음
	char str[MAX];
	printf("input strings : ");
 while(fscanf(fp, "%s", &str)!=EOF)
    {
		element* temp;
		MALLOC(temp, sizeof(*temp));

		printf("%8s", str); //파일의 값을 출력

		strcpy(temp->item, str); 
		
		temp->key = stringToInt(temp->item); //파일의 문자열을 키 변환

		insert(temp->key, temp); //키 값을 기준으로 해싱 테이블에 저장
    }
	printf("\n\n");


	//해시 테이블 출력
	printf("             item     key\n");
	for (int i = 0; i < MAX; i++)
	{
		if (ht[i]->item && ht[i]->key)
		{
			printf("ht[%2d]: %10s %7d\n", i, ht[i]->item, ht[i]->key);
		}
		else
		{
			printf("ht[%2d]:\n", i);
		}
	}
	printf("\n");


	//찾기
	element* searchElement;
	char searchItem[MAX];
	int searchKey;
	printf("string to search >> ");
	scanf("%s", searchItem);
	searchKey = stringToInt(searchItem);
	searchElement = search(searchKey);
	if (searchElement) {
		printf("item:  %s, key: % d, the number of comparisions : %d", searchElement->item, searchElement->key, count);
	}
	else
	{
		printf("it doesn't exist!");
	}
	return 0;
}


//hashfunction
int h(int k)
{
	return k % b;
}

//String to Integer
unsigned int stringToInt(char* key) {
	int number = 0;
	while (*key)
	{
		number += *key++;
	}
	return number;
}


//찾는 값이 없으면 return NULL; 찾는 값이 있으면 return ht[currentBucket];
element* search(int k) {
	int homeBucket, currentBucket;
	homeBucket = h(k); //hash function의 값

	/*"ht[currentBucket]의 값이 null이 아니고(채워져 있고), 찾는 값이 아닐 경우" 계속 반복 진행
	비어있으면-> 빠져나옴
	찾는 값이면-> 빠져나옴
	*/
	for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k;)
	{
		currentBucket = (currentBucket + 1) % b; //bucket 한 칸씩 이동
		count++; //반복 수 세주기

		//찾고 있는 bucket의 index가 처음(homeBucket)으로 돌아왔을때(bucket table이 가득 찼을때)
		if (currentBucket == homeBucket) {
			return NULL;
		}
	}

	/*
	* 위의 반복문을 빠져 나왔을때
	* currentBucket의 값이 저장되어 있고
	* 찾는 값이면
	* curretBucket의 버킷 리턴
	*/
	if (ht[currentBucket] && ht[currentBucket]->key == k)
	{
		count++;
		return ht[currentBucket]; //반복 수 세주기
	}

	return NULL;
}

/*
insert 함수
- search(Program 8.3) 함수를 참고하여 구현
- 해싱테이블(ht)에 더 이상 추가할 수 없을 때는 적절한 메시지를 출력하고 종료한다.
- 중복된 key가 있을 경우에는 적절한 메시지를 출력하고 종료한다.
*/
void insert(int k, element * temp) {
	int homeBucket, currentBucket;
	homeBucket = h(k);

	/*"ht[currentBucket]의 값이 null이 아니고(채워져 있고), 찾는 값이 아닐 경우" 계속 반복 진행
	비어있으면-> 빠져나옴
	찾는 값이면-> 빠져나옴
	*/
	for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k;)
	{
		currentBucket = (currentBucket + 1) % b; //bucket 한 칸 이동

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
	else
	{
		printf("\n\n");
		printf("중복된 키가 존재! 종료!");
		exit(EXIT_FAILURE);
	}

}