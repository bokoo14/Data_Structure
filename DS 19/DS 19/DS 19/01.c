//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 19(2). Insertion sort
* 2. ������ ���� ����ڷκ��� �����͸� �Է¹޾Ƽ� "��������(insertion sort)"�� ������ ����� ��� 
* �� ���ڵ�� (key, name, grade)�� �ʵ�� �����ȴ�. (3��)
* 
* (1) �Է�����(input.txt)
* 
* (2) �������
* �� �Է����Ϸκ��� �����͸� �о� �鿩 ����ü �迭�� �����Ѵ�. 
* �� key�� ���� ���������� �����Ѵ�. 
* �� ���ĵ� ������� (key, name, grade)�� ȭ�鿡 ����Ѵ�. 
* �� ���İ���� ����(output.txt)�� �����Ѵ�.
*/


#define _CRT_SECURE_NO_WARNINGS

typedef struct element {
	int key;
	char name[10];
	int grade;
}element;
element e[100]; //����ü�迭


void insert(element e, element a[], int i);
void insertionSort(element a[], int n);

#include<stdio.h>
#include<stdlib.h>
int main()
{

	FILE* fp = NULL;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open file");
		exit(EXIT_FAILURE);
	}
	

	//������ �Է¹��� 
	int a;
	fscanf(fp, "%d", &a);


	//key, name, grade������ �Է¹ޱ� (�迭�� 1���� ����, 0�� ����ֱ�)
	int i = 1;
	while (fscanf(fp, "%d %s %d", &e[i].key, e[i].name, &e[i].grade) != EOF) {
		i++;
	}

	//�Էµ� �� ��� (�迭�� 1���� ����, 0�� ����ֱ�)
	printf("<<<<<Input List>>>>>\n");
	for (int i = 1; i < a+1; i++)
	{
		printf("<%d, %s, %d>\n", e[i].key, e[i].name, e[i].grade);
	}

	printf("\n");


	//����ü �迭, ����ü �迭�� ����(������ ������ ����) key���� �������� ����
	insertionSort(e, a);

	//���� �� ��� (�迭�� 1���� ����, 0�� ����ֱ�)
	printf("<<<<<Sorted List>>>>>\n");
	for (int i = 1; i < a+1; i++)
	{
		printf("<%d, %s, %d>\n", e[i].key, e[i].name, e[i].grade);
	}

	//���Ͽ� ���� (�迭�� 1���� ����, 0�� ����ֱ�)
	FILE* fout = fopen("output.txt", "w");
	for (int k = 1; k < a+1; k++)
	{
		fprintf(fout, "( %d, %s, %d)\n", e[k].key, e[k].name, e[k].grade);
	}
	fclose(fout);

	return 0;
}


//key�� ���� ��������
void insert(element e, element a[], int i) {
	//������ �� �ӽ� ����
	a[0] = e;
	//������ ���� �� ������ ��ġ �̵������� "<-����"���� �̵�
	while (e.key < a[i].key)
	{
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

//���� ����
void insertionSort(element a[], int n) {
	int j;

	//2~n���� �ܰ������� �������� "->����"���� �̵�
	for (j = 2; j <= n; j++)
	{
		element temp = a[j]; //�� �ܰ迡�� ������ ��(j��° ����)
		insert(temp, a, j - 1);
	}

}