//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

//두 다항식 정보를 파일로부터 입력받아 다항식 더하기를 수행한 후 그 결과를 출력하는 프로그램

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

	//두 다항식을 더해줌
	padd(startA, finishA, startB, finishB, &startD, &finishD);
	printf("the result of polynomial addition ...\n");
	printf("D(x) = A(x) + B(x) = \n");
	printPoly(startD, finishD);
	return 0;
}

//파일로부터 데이터를 입력받아 2개의 다항식을 구성
void inputPoly(char* fname, int* startA, int* finishA, int* startB, int* finishB) 
{
	int Asize, Bsize, expp;
	float coeff;
	FILE* fp = fopen(fname, "r"); //파일을 읽기모드로 불러옴
	fscanf_s(fp, "%d %d", &Asize, &Bsize); //A와 B의 크기를 받음
	*startA = 0; 
	*finishA = Asize - 1; 
	*startB = Asize;
	*finishB = (Asize + Bsize)-1;
	avail = (Asize + Bsize); //전체 배열(다항식)의 크기

	for (int i = 0; i < avail; i++) //전체 다항식의 크기만큼 받음
	{
		fscanf_s(fp, "%f %d ", &coeff, &expp); //다항식의 계수와 차수를 파일에서 읽음
		terms[i].coef = coeff; //계수
		terms[i].exp = expp; //차수
	}
}

//두 다항식을 더해줌
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD)
{ /* A(x) + B(x) = D(x) */

	float coefficient;
	*startD = avail;

	//두개의 index(start, finish)가 역전되지 않으면
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

//배열에 새 항 추가하는 함수
void attach(float coefficient, int exponent) 
{
	if (avail >= MAX_TERMS)
	{
		fprintf(stderr, "Too may terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient; //더한 값의 coef를 배열에 추가
	terms[avail++].exp = exponent; //더한 값의 exp를 배열에 추가
}

//하나의 다항식을 전달받아 화면으로 출력
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

