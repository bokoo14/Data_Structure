//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�


/*23(2) Chaining
* 2. [Chaining] ������ ���� �Է����Ϸκ��� ���ڿ��� �Է¹޾� �ؽ����̺��� �߰��ϴ� ���α׷�
* ���� Ȩ ��Ŷ ü���� "������"�� �߰���
* 
* <�ؽ�����>
* �Է�����(input.txt) :acos atoi char define exp ceil cos float floor ctime
* �� �Է¹��ڿ��� �ִ� ũ��� 10���� �����Ѵ�.
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


int count = 0; //�� Ƚ��
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

	//���ڿ��� �Է¹���
	int i, cnt;
	char str[MAX_STRING][MAX_STRING];

	printf("input strings : ");

	cnt = 0;
	while (fscanf(fp, "%s", &str[cnt]) != EOF)
	{
		printf("%8s", str[cnt]);   cnt++; // input���� ���
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
			if (current->link == NULL) { // ������ ��忡 ����
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
