//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

//�� ���׽� ������ ���Ϸκ��� �Է¹޾� ���׽� ���ϱ⸦ ������ �� �� ����� ����ϴ� ���α׷�

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define COMPARE(x,y) (((x)<(y))? -1 : ((x))==((y))? 0 : 1 ) 

#define MAX_TERMS 100 

typedef struct
{
	float coef;
	int exp;
}term;
term terms[MAX_TERMS];
int avail = 0;

void inputPoly(char* fname, int* startA, int* finishA, int* startB, int* finishB);
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
void attach(float coefficient, int exponent);
void printPoly(int start, int finish); 


int main()
{
	char* filename = "input.txt";

	int startA, startB, finishA, finishB, startD, finishD;

	inputPoly(filename, &startA, &finishA, &startB, &finishB);
	printf("two input polynomials ... \n");
	printf("A(x) = ");
	printPoly(startA, finishA);
	printf("\n");

	printf("B(x) = ");
	printPoly(startB, finishB);

	printf("  \n \n");

	//�� ���׽��� ������
	padd(startA, finishA, startB, finishB, &startD, &finishD);
	printf("the result of polynomial addition ...\n");
	printf("D(x) = A(x) + B(x) = \n");
	printPoly(startD, finishD);
	return 0;
}

//���Ϸκ��� �����͸� �Է¹޾� 2���� ���׽��� ����
void inputPoly(char* fname, int* startA, int* finishA, int* startB, int* finishB) 
{
	int Asize, Bsize, expp;
	float coeff;
	FILE* fp = fopen(fname, "r"); //������ �б���� �ҷ���
	fscanf_s(fp, "%d %d", &Asize, &Bsize); //A�� B�� ũ�⸦ ����
	*startA = 0; 
	*finishA = Asize - 1; 
	*startB = Asize;
	*finishB = (Asize + Bsize)-1;
	avail = (Asize + Bsize); //��ü �迭(���׽�)�� ũ��

	for (int i = 0; i < avail; i++) //��ü ���׽��� ũ�⸸ŭ ����
	{
		fscanf_s(fp, "%f %d ", &coeff, &expp); //���׽��� ����� ������ ���Ͽ��� ����
		terms[i].coef = coeff; //���
		terms[i].exp = expp; //����
	}
}

//�� ���׽��� ������
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD)
{ /* A(x) + B(x) = D(x) */

	float coefficient;
	*startD = avail;

	//�ΰ��� index(start, finish)�� �������� ������
	while (startA <= finishA && startB <= finishB)
	{
		switch (COMPARE(terms[startA].exp, terms[startB].exp))
		{
		case -1: /* a expon < b expon */
			attach(terms[startB].coef, terms[startB].exp);
			startB++;
			break;
		case 0: /* equal exponents */
			coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient)
				attach(coefficient, terms[startA].exp);
			startA++;
			startB++;
			break;
		case 1: /* a expon > b expon */
			attach(terms[startA].coef, terms[startA].exp);
			startA++;
		}
	}
	/* add in remaining terms of A(x) */
	for (; startA <= finishA; startA++)
		attach(terms[startA].coef, terms[startA].exp);

	/* add in remaining terms of B(x) */
	for (; startB <= finishB; finishB++)
		attach(terms[startB].coef, terms[startB].exp);
	*finishD = avail - 1;
}

//�迭�� �� �� �߰��ϴ� �Լ�
void attach(float coefficient, int exponent) 
{
	if (avail >= MAX_TERMS)
	{
		fprintf(stderr, "Too may terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient; //���� ���� coef�� �迭�� �߰�
	terms[avail++].exp = exponent; //���� ���� exp�� �迭�� �߰�
}

//�ϳ��� ���׽��� ���޹޾� ȭ������ ���
void printPoly(int start, int finish) 
{
	for (int i = start; i <= finish; i++)
	{
		if (i == finish)
		{
			if (terms[i].exp == 0)
			{
				printf("%.1f", terms[i].coef);
			}
			else
			{
				printf("%.1fx^%d ", terms[i].coef, terms[i].exp);
			}

		}
		else
		{
			printf("%.1fx^%d ", terms[i].coef, terms[i].exp);
			printf("+ ");
		}
	}
}
