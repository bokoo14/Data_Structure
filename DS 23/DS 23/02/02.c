//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다


/*23(2) Chaining
* 2. [Chaining] 다음과 같이 입력파일로부터 문자열을 입력받아 해싱테이블에 추가하는 프로그램
* 노드는 홈 버킷 체인의 "마지막"에 추가됨
* 
* <해싱조건>
* 입력파일(input.txt) :acos atoi char define exp ceil cos float floor ctime
* ※ 입력문자열의 최대 크기는 10임을 가정한다.
* 
*/

#define _CRT_SECURE_NO_WARNINGS
#define  MALLOC(p,s)\
   if(!((p) = malloc(s))){\
   fprintf(stderr,"Insufficient memory");\
   exit(EXIT_FAILURE);\
}
#define MAX_BUCKET 11
#define MAX_STRING 10


typedef struct element
{
	char item[10];
	int key;
}element;

typedef struct node* nodePointer;
typedef struct node
{
	element data;
	element* link;
}node;


int count = 0; //비교 횟수
nodePointer ht[MAX_BUCKET];

//hash function
int h(int k);

element* search(int k);
void insert(int k, nodePointer temp);


#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	
	FILE* fp = NULL;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	//문자열을 입력받음
	int i, cnt;
	char str[MAX_STRING][MAX_STRING];

	printf("input strings : ");

	cnt = 0;
	while (fscanf(fp, "%s", &str[cnt]) != EOF)
	{
		printf("%8s", str[cnt]);   cnt++; // input파일 출력
	}
	printf("\n");


	
	for (int i = 0; i < cnt; i++)
	{
		nodePointer temp;
		MALLOC(temp, sizeof(*temp));
		strcpy(temp->data.item, str[i]);
		temp->data.key = stringToInt(temp->data.item);

		temp->link = NULL;

		insert(temp->data.key, temp);
	}

	nodePointer curr;
	printf("        item   key\n");
	for (int i = 0; i < MAX_BUCKET; i++)
	{
		printf("ht[%2d] : ", i);
		for (curr = ht[i];curr;curr=curr->link) 
		{
			if (curr->data.key) {
				printf("<%4s %3d> ", curr->data.item, curr->data.key);
			}
			else
			{
				printf("\n");
			}
		}
		printf("\n");
	}
	printf("\n");

	char searchString[MAX_STRING];
	int searchNum;
	element* searchElement;
	while (1) {
		printf("input ^z to quit\n");
		printf("string to search >> ");
		scanf("%s", searchString);
		if (!strcmp(searchString, "^z"))
		{
			break;
		}
		searchNum = stringToInt(searchString);

		if (searchElement = search(searchNum))
		{
			printf("item: %s, key: %d, the number of comparisions: %d \n\n", searchString, searchNum, count);
			count = 0;
		}
		else
		{
			printf("it doesn't exist!\n\n");
		}

	}

	return 0;
	
}

int h(int k)
{
	return k % MAX_BUCKET;
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


void insert(int k, nodePointer temp)
{
	nodePointer current;
	int homeBucket = h(k);
	//printf("%d ", homeBucket); // debug

	current = ht[homeBucket];

	if (current == NULL) {
		ht[homeBucket] = temp;
		//printf("%s  ", ht[homeBucket]->data.item); // debug
		//printf("%d   ", ht[homeBucket]->data.key); // debug
	}
	else {
		for (current = ht[homeBucket]; current; current = current->link) {
			if (current->link == NULL) { // 마지막 노드에 삽입
				current->link = temp;
				//printf("%s  ", curr->data.item); // debug
				break;
				//printf("%s  ", curr->data.item); // debug
			}
		}
	}
	//printf("%s  ", curr->data.item); // debug
	//printf("%d   ", curr->data.key); // debug
}

//chain search
element* search(int k)
{
	nodePointer current;
	int homeBucket = h(k);

	for (current = ht[homeBucket]; current; current = current->link) {
		count++;
		if (current->data.key == k)
			return &current->data;
	}
	return NULL;
}

