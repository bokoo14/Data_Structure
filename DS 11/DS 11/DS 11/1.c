//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�. 

/*���Ḯ��Ʈ: ���׽� ����
ü���� �̿��� ���׽� ���ϱ� ���α׷�
a�̸� ��������, d�̸� ������������ �Է�
���׽��� ǥ���ϴ� ü���� ���������̾�� ��
-> ������������ �ԷµǴ� �� ���� ü���� ù ���� ����
-> ������������ �ԷµǴ� �� ���� ü���� ������ ���� ����
*/

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if( !( (p) = (polyPointer)malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)

// ��� ����
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
	//�� ���� ���׽� ������ ���Ϸκ��� �Է¹޾Ƽ� �� ���׽��� ü�� ���·� ����
	inputPoly("a.txt", &a);
	inputPoly("b.txt", &b);

	//���׽� a�� ���
	printf("a :");	
	printList(a);

	//���׽� b�� ���
	printf("b :");
	printList(b);

	//���׽� a�� b�� ������
	c = padd(a, b);

	//���׽� c�� ���
	printf("a+b=c: ");	
	printList(c);

	//���׽� a, b, c�� ����
	erase(&a);
	erase(&b);
	erase(&c);

	return 0;
}

void insert(polyPointer* first, polyPointer x, int coef, int expon)
{
	//���ο� ��带 �ϳ� ����
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coef;
	temp->expon = expon;

	//�տ� ������ ������ �����Ѵٸ� (first�� ������� ������)
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

	//������ ����
	FILE* fp;
	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	//ù���� �޾ƿ�
	fscanf_s(fp, "%c", &order, sizeof(order));
	//d�̸� ��������
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
	//a�̸� ��������
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

//first�� ����Ű�� ü���� ������ ��带 ã�´�
void findLast(polyPointer first, polyPointer* last)
{
	for (; first; first = first->link)
		*last = first;
}

//a, b �� ���׽��� ������ ���
void printList(polyPointer first)
{
	for (; first; first = first->link)
		printf("%+4dx^%d ", first->coef, first->expon);
	printf("\n");
}

//a+b�� ����� c�� �����ϴ� ���׽� ���ϱ� ����
polyPointer padd(polyPointer a, polyPointer b)
{
	polyPointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	c = rear;

	//a�� b��� �����Ѵٸ� 
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

//���Ḯ��Ʈ�� ��� ����
void attach(int coefficient, int exponent, polyPointer* ptr)
{
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

//���׽� ����
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

