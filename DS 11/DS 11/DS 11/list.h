#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
	if( !( (p) = (polyPointer)malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)

// linked list
typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;


void findLast(polyPointer first, polyPointer* last);
void insert(polyPointer* first, polyPointer x, int coef, int expon);
void printList(polyPointer first);
polyPointer padd(polyPointer a, polyPointer b);
void attach(int coefficient, int exponent, polyPointer* ptr);
void erase(polyPointer* first);
void inputPoly(char* filename, polyPointer* p);		// create a polynomial from file


void findLast(polyPointer first, polyPointer* last)
{
	for (; first; first = first->link)
		*last = first;
}

void insert(polyPointer* first, polyPointer x, int coef, int expon)
{ /* insert a new node with a data into the chain first after node x */
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coef;
	temp->expon = expon;

	if (*first)
	{ // add to non-empty list
		if (!x)
		{ // as a first node
			temp->link = *first;
			*first = temp;
		}
		else
		{ // as an intermediate or last node
			temp->link = x->link;
			x->link = temp;
		}
	}
	else
	{ 	// add to empty list
		temp->link = NULL;
		*first = temp;
	}
}

void printList(polyPointer first)
{
	for (; first; first = first->link)
		printf("(%p : %+4dx^%d : %p)  \n", first, first->coef, first->expon, first->link);
	printf("\n");
}

polyPointer padd(polyPointer a, polyPointer b)
{
	polyPointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	c = rear;
	while (a && b)
	{
		switch (COMPARE(a->expon, b->expon))
		{
		case -1: /* a->expon < b->expon */
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0: /* a->expon = b->expon */
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link; 	b = b->link;
			break;
		case 1: /* a->expon > b->expon */
			attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		}
	}

	/* copy rest of list a and then list b */
	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;

	/* delete extra initial node */
	temp = c; c = c->link; free(temp);
	return c;
}

void attach(int coefficient, int exponent, polyPointer* ptr)
{/* create a new node with coef = coefficient and
	expon = exponent, attach it to the node pointed to by ptr.
	ptr is updated to point to this new node */
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

void erase(polyPointer* ptr)
{/* erase the polynomial pointed to by ptr */
	polyPointer temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}

void inputPoly(char* filename, polyPointer* p)
{
	int coef, expon;
	polyPointer x = NULL;		// insert position in chain
	polyPointer last = NULL;	// last position in chain
	char order;							// a : ascending order, d : descending order
	FILE* fp;

	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%c", &order, (unsigned int)sizeof(order));		// a or d
	if (order == 'd')
	{
		fscanf_s(fp, "%d%d", &coef, &expon);
		while (!feof(fp))
		{
			findLast(*p, &last);
			x = last;								// insert position
			insert(p, x, coef, expon);		// insert data first after node x. 
			fscanf_s(fp, "%d%d", &coef, &expon);
		}
	}
	else	//'a'
	{
		fscanf_s(fp, "%d%d", &coef, &expon);
		while (!feof(fp))
		{
			insert(p, NULL, coef, expon);		// insert data as a first node. 
			fscanf_s(fp, "%d%d", &coef, &expon);
		}
	}

	fclose(fp);
}
