//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 19(4). Quick sort
* �� 3�� �Է¸���Ʈ�� �����͸� ���Ϸ� �Է¹޾� ������ ������ �� quickSort �Լ�ȣ�� ȸ���� ���Ͽ� ���
* ��, �� ���ڵ�� �ϳ��� int�� key �ʵ�� �����Ǿ� �ִ�. (3��)
* 
* (1) �Է�����(input.txt) 
* 
* (2) �������
* �� �Է�����(input.txt)�κ��� �����͸� �о� �鿩 ����ü �迭 a�� �����Ѵ�.
* �� �� ���ڵ��� key�� ���� �������� �����Ѵ�. 
* �� ���ĵ� key�� �� quickSort �Լ�ȣ�� ȸ���� ȭ�鿡 ����϶�. 
* �� ���İ���� ����(output.txt)�� �����Ѵ�.
* 
*/

#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))


typedef struct element {
	int key;
}element;
element e[20];

int cnt =0; //�Լ��� ȣ��Ǵ� ��
int q=0; //������ ��
void quickSort(element a[], int left, int right);

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
	fscanf(fp, "%d", &q);

	for (int m = 0; m < q; m++)
	{
		fscanf(fp, "%d", &e[m].key);
	}
	
	
	printf("<<<<<Input List>>>>>\n");
	for (int i = 0; i < q; i++)
	{
		printf("%3d", e[i].key);
	}

	printf("\n\n");


	printf("executive of quick sort...\n");
	for (int i = 1; i < q+1; i++)
	{
		printf(" [%2d] ", i);
	}
	printf(" [left right] \n");


	quickSort(e, 0, q-1 );

	printf("calls of quick sort: %d", cnt);


	FILE* fout = fopen("output.txt", "w");

	fprintf(fout, "%2d\n", q);
	for (int k = 0; k < q ; k++)
	{
		fprintf(fout, "%3d", e[k].key);
	}
	fclose(fout);

	return 0;
}

void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;


	cnt++; //��� �Լ��� ȣ��Ǿ����� ������

	//quickSort�� �Ҷ����� ������ �������
	for (int k = 0; k < q; k++)
	{
		printf("%6d", a[k]);
	}
	printf(": %3d %3d ", left+1, right+1);
	printf("\n");
	
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = a[left].key;
		do {
			do i++; while (a[i].key < pivot); //key���� �� Ŭ������
			do j--; while (a[j].key > pivot); //key���� �� ����������
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}

}