//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다. 

/*연결리스트: 다항식 덧셈
체인을 이용한 다항식 더하기 프로그램
a이면 오름차순, d이면 내림차순으로 입력
다항식을 표현하는 체인은 내림차순이어야 함
-> 오름차순으로 입력되는 각 항은 체인의 첫 노드로 삽입
-> 내림차순으로 입력되는 각 항은 체인의 마지막 노드로 삽입
*/

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if( !( (p) = (polyPointer)malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)

// 노드 생성
typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;
polyPointer a = NULL, b = NULL, c = NULL;

void findLast(polyPointer first, polyPointer* last);
void insert(polyPointer* first, polyPointer x, int coef, int expon);
void printList(polyPointer first);
polyPointer padd(polyPointer a, polyPointer b);
void attach(int coefficient, int exponent, polyPointer* ptr);
void erase(polyPointer* first);
void inputPoly(char* filename, polyPointer* p);

int main(void)
{
	//두 개의 다항식 데이터 파일로부터 입력받아서 각 다항식을 체인 형태로 구현
	inputPoly("a.txt", &a);
	inputPoly("b.txt", &b);

	//다항식 a를 출력
	printf("a :");	
	printList(a);

	//다항식 b를 출력
	printf("b :");
	printList(b);

	//다항식 a와 b를 더해줌
	c = padd(a, b);

	//다항식 c를 출력
	printf("a+b=c: ");	
	printList(c);

	//다항식 a, b, c를 지움
	erase(&a);
	erase(&b);
	erase(&c);

	return 0;
}

void insert(polyPointer* first, polyPointer x, int coef, int expon)
{
	//새로운 노드를 하나 생성
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coef;
	temp->expon = expon;

	//앞에 생성된 노드들이 존재한다면 (first가 비어있지 않으면)
	if (*first)
	{
		if (!x)
		{
			temp->link = *first;
			*first = temp;
		}
		else
		{
			temp->link = x->link;
			x->link = temp;
		}
	}
	else
	{
		temp->link = NULL;
		*first = temp;
	}
}

void inputPoly(char* filename, polyPointer* p)
{
	int coef, expon;
	polyPointer x = NULL;
	polyPointer last = NULL;
	char order;

	//파일을 읽음
	FILE* fp;
	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	//첫줄을 받아옴
	fscanf_s(fp, "%c", &order, sizeof(order));
	//d이면 내림차순
	if (order == 'd')
	{
		fscanf_s(fp, "%d%d", &coef, &expon);
		while (!feof(fp))
		{
			findLast(*p, &last);
			x = last;
			insert(p, x, coef, expon);
			fscanf_s(fp, "%d%d", &coef, &expon);
		}
	}
	//a이면 오름차순
	else
	{
		fscanf_s(fp, "%d%d", &coef, &expon);
		while (!feof(fp))
		{
			insert(p, NULL, coef, expon);
			fscanf_s(fp, "%d%d", &coef, &expon);
		}
	}

	fclose(fp);
}

//first가 가리키는 체인의 마지막 노드를 찾는다
void findLast(polyPointer first, polyPointer* last)
{
	for (; first; first = first->link)
		*last = first;
}

//a, b 두 다항식의 정보를 출력
void printList(polyPointer first)
{
	for (; first; first = first->link)
		printf("%+4dx^%d ", first->coef, first->expon);
	printf("\n");
}

//a+b의 결과를 c에 저장하는 다항식 더하기 실행
polyPointer padd(polyPointer a, polyPointer b)
{
	polyPointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	c = rear;

	//a와 b모두 존재한다면 
	while (a && b)
	{
		switch (COMPARE(a->expon, b->expon))
		{
		case -1: 
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0: 
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link; 	b = b->link;
			break;
		case 1: 
			attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		}
	}

	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;

	
	temp = c; c = c->link; free(temp);
	return c;
}

//연결리스트에 노드 삽입
void attach(int coefficient, int exponent, polyPointer* ptr)
{
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

//다항식 삭제
void erase(polyPointer* ptr)
{
	polyPointer temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}


