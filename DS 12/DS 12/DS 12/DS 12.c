//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/*�����带 ���� ���Ͽ��� ȯ������Ʈ�� �̿��� ���׽� ���ϱ� ���α׷�
* ���α׷� ���� �� �� �̻� ������� �ʴ� ��带 �����ϴ� ü�� ������ ���Ǯ(noed pool or available space list)�� ���� ����
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)
#define MALLOC(p, s) \
	if( !( (p) = malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;

//��� ��带 ���� ���׽�(���Ͽ��� ȯ������Ʈ)
polyPointer a = NULL, b = NULL, c = NULL;
//���׽� a�� b�� ���� last������
polyPointer lastA, lastB;
//���Ǯ(ü��)
polyPointer avail = NULL;

void erase(polyPointer* first);
polyPointer getNode(polyPointer* avail);
void retNode(polyPointer node, polyPointer* avail);
void cerase(polyPointer* ptr, polyPointer* avail);
polyPointer cpadd(polyPointer a, polyPointer b, polyPointer avail);
void attach(int coefficient, int exponent, polyPointer* ptr, polyPointer avail);
void insertFront(polyPointer* last, polyPointer node);
void insertLast(polyPointer* last, polyPointer node);
void printCList(polyPointer header);
void inputPolyCL(char* filename, polyPointer* header, polyPointer* last, polyPointer avail);


int main()
{
	polyPointer a = NULL, b = NULL, c = NULL;
	polyPointer lastA, lastB;
	polyPointer avail = NULL;

	inputPolyCL("a.txt", &a, &lastA, avail);
	inputPolyCL("b.txt", &b, &lastB, avail);

	//�� ���׽��� ������ ���
	printf("%9s", "a : ");	printCList(a);
	printf("%9s", "b : ");	printCList(b);

	//a+b�� ����� c�� �����ϴ� ���׽� ���ϱ� ����
	c = cpadd(a, b, avail);
	//���׽� c�� ���
	printf("%9s", "a+b=c : "); printCList(c);

	//���׽�a, b, c�� ����
	cerase(&a, &avail);
	cerase(&b, &avail);
	cerase(&c, &avail);
	//printf("%9s", "avail : \n");	printCList(avail);

	//avail����
	erase(&avail);

	return 0;
}

//�ϳ��� �����Է����� "�����带 ���� ���Ͽ��� ȯ������Ʈ"�� ������ �ϳ��� ���׽� ����
//���� ���� ��� ��常���� ������ ���� ���׽��� ������ ��, ���� �Է����κ��� �ϳ��� ��带 ���� �� �� ����Ʈ�� �߰�
void inputPolyCL(char* filename, polyPointer* header, polyPointer* last, polyPointer avail)
{
	polyPointer node;
	char order;				// a: ascending order(��������), d: descending order (��������)
	FILE* fp;
	int tp;

	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	//��� ��常���� ������ ���� ���׽� ����
	*header = getNode(&avail);
	(*header)->expon = -1;
	*last = NULL;


	fscanf_s(fp, "%c", &order, (int)sizeof(order));

	//���� �Է������� 'd'�̸� insertLastCL �Լ�-����Ʈ�� ������ ���� �߰�
	//'a'�̸� insertFrontCL �Լ�- ����Ʈ�� ù ���� �߰�
	if (order == 'd')
	{
		insertLast(last, *header);
		node = getNode(&avail);

		while (!feof(fp))
		{
			tp = fscanf_s(fp, "%d%d", &node->coef, &node->expon);
			if (tp > 0)
			{
				insertLast(last, node);
				node = getNode(&avail);
			}

		}
		retNode(node, &avail);
	}
	// 'a' �������� �� ���� ȯ������Ʈ�� ù ���� ����
	else
	{
		insertFront(last, *header);
		node = getNode(&avail);

		while (!feof(fp))
		{
			tp = fscanf_s(fp, "%d%d", &node->coef, &node->expon);
			if (tp > 0)
			{
				insertFront(last, node);
				node = getNode(&avail);
			}

		}
		retNode(node, &avail);
	}

	fclose(fp);
}

//��������->�� ���� ȯ������Ʈ�� ù ���� ����
void insertFront(polyPointer* last, polyPointer node)
{
	//������ ��带 ����Ű�� last�����Ͱ� null�϶� 
	if (!(*last))
	{
		*last = node;
		node->link = node;
	}
	//������ ��带 ����Ű�� last�����Ͱ� null�� �ƴҶ� 
	else
	{
		node->link = (*last)->link->link;
		(*last)->link->link = node;

		//ù ��� ���� �� lastA�� �����ϰ� ���Ĵ� lastA�� ���� ����
		if ((*last)->expon == -1)
			*last = node;
	}
}

//��������->�� ���� ȯ������Ʈ�� ������ ���� �߰�
void insertLast(polyPointer* last, polyPointer node)
{
	//������ ��带 ����Ű�� last�����Ͱ� null�϶� 
	if (!(*last))
	{
		*last = node;
		node->link = node;
	}
	//������ ��带 ����Ű�� last�����Ͱ� null�� �ƴҶ� 
	else
	{
		node->link = (*last)->link; //last�� ����Ű�� ������ ��� �ڿ� ����
		(*last)->link = node; //last�� ����Ű�� ������ ��� �ڿ� ����
		*last = node; //last�����ʹ� node�� ����Ŵ
	}
}

//ptr�� ����Ű�� ü���� ���� 
//avail����
//ü���� ó������ ���󰡸� ��� ��忡 ���� �޸������� ����
void erase(polyPointer* ptr)
{
	polyPointer temp;
	//ptr�� ������� ���� ��
	//temp�� ptr�� ����Ŵ-> ptr�� �̵�-> temp�� �ִ� node�� free
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
	return;
}

//ü������ ������ ���Ǯ�κ��� ��带 �ϳ� �����´�
polyPointer getNode(polyPointer* avail)
{
	polyPointer node;
	if (*avail)
	{
		node = *avail;
		*avail = (*avail)->link;
	}
	else
		MALLOC(node, sizeof(*node));
	return node;

}

//�� �̻� ������� �ʴ� ��� �ϳ��� ���Ǯ�� ��ȯ
void retNode(polyPointer node, polyPointer* avail)
{
	node->link = *avail;
	*avail = node;
}

//���׽� a, b, c�� avail�� �ݳ�
void cerase(polyPointer* ptr, polyPointer* avail)
{
	polyPointer temp;
	if (*ptr)
	{
		temp = (*ptr)->link;
		(*ptr)->link = *avail;
		*avail = temp;
		*ptr = NULL;
	}
}

//a+b�� ����� c�� �����ϴ� ���׽� ���ϱ� ����
//"�����带 ���� ���� ���� ȯ������Ʈ"�� ǥ���� �� ���׽� a, b�� ���� ���ϱ� ������ �����Ͽ� �� ��� ���׽��� ��ȯ
polyPointer cpadd(polyPointer a, polyPointer b, polyPointer avail)
{
	polyPointer startA, c, lastC;
	int sum, done = FALSE;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode(&avail);
	c->expon = -1; lastC = c;

	do
	{
		switch (COMPARE(a->expon, b->expon))
		{
		case -1: /* a->expon < b->expon */
			attach(b->coef, b->expon, &lastC, avail);
			b = b->link;
			break;

		case 0: /* a->expon = b->expon */
			if (startA == a)
			{
				done = TRUE;
			}
			else
			{
				sum = a->coef + b->coef;
				if (sum) attach(sum, a->expon, &lastC, avail);
				a = a->link; 	b = b->link;
			}
			break;

		case 1: /* a->expon > b->expon */
			attach(a->coef, a->expon, &lastC, avail);
			a = a->link;
		}
	} while (!done);

	lastC->link = c;

	return c;
}

void attach(int coefficient, int exponent, polyPointer* ptr, polyPointer avail)
{
	polyPointer temp;
	temp = getNode(&avail);
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

//a, b �� ���׽��� ������ ���
//���׽� C�� ���
void printCList(polyPointer header)
{
	polyPointer temp;

	if (header)
	{
		temp = header->link;
		//printf("%+4dx^%d ", header->coef, header->expon);
		while (temp != header)
		{
			if (temp->expon != 0) {
				printf(" %+4dx^%d ", temp->coef, temp->expon);
				temp = temp->link;
			}
			else
			{
				printf(" %+4d", temp->coef);
				temp = temp->link;
			}

		}
		printf("\n");
	}
}