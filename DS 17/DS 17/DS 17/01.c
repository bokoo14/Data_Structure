//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 17(1) Graph: Adjacency List "��������Ʈ"
*  ���� �Է��� ���� ������ �׷���(undirected graph)�� ���� �׷���(directed graph)�� ��������Ʈ(adjacency-list)�� �����ϴ� ���α׷�
* 
* ��������Ʈ�� "�����尡 ����Ű�� ù���"�� ����
* 
* �������
* �� �׷��� ����, ����, ������ ���� �Է¹���
* �� �׷��� ������ ���� ������ �ϳ��� �Է¹����鼭 ��������Ʈ�� ������
* �� �׻� �����尡 ����Ű�� ù ���� �Էµǰ� ��
* �� �� ������ ���� �μӵ� ����(edges incident to a vertex v)�� ����ϱ�
*/


#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
	if( !( (p) = malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

//adjacency list
typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;
listPointer *adjLists;

void insert(listPointer* first, listPointer list, int data);
void printlist(listPointer list);

#include<stdio.h>
#include <stdlib.h>


int main()
{
	FILE* fp = fopen("input.txt", "r");

	if ((fp=fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open file");
		exit(EXIT_FAILURE);
	}


	char ud; //uȤ�� d�� ���Ϸκ��� ����
	int vertex, edge;
	//u, d vertex��, edge���� ����(ù ���� �о��)
	fscanf(fp, "%c %d %d", &ud, &vertex, &edge);

	//���� ����Ʈ�� vertex����ŭ ����
	MALLOC(adjLists, sizeof(*adjLists)*vertex);
	for (int i = 0; i < vertex; i++)
	{
		adjLists[i] = NULL;
	}

	int v1, v2;
	//������ �׷����϶�
	if (ud=='u')
	{
		while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
		{
			insert(&adjLists[v1], NULL, v2);
			insert(&adjLists[v2], NULL, v1);
		}
	}
	//���� �׷����϶�
	else
	{
		while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
		{
			insert(&adjLists[v1], NULL, v2);
		}
	}
	
	printf("<<<<<Adjacency List>>>>>\n");
	for (int i = 0; i < vertex; i++)
	{
		printf("adjLists[%d]: ", i);
		printlist(adjLists[i]);
	}


	fclose(fp);

	return 0;
}

//���� ����Ʈ �����
void insert(listPointer* first, listPointer list, int data) {
	listPointer node;
	MALLOC(node, sizeof(*node));

	node->data = data;

	//adjLists[]�� ����Ű�� ���� ������
	if (*first == NULL)
	{
		node->link = NULL;
		*first = node;
	}
	else 
	{
		//list�� ���� NULL�̶��-> ��������Ʈ�� ù ���� ����
		if (list == NULL)
		{
			node->link = *first;
			*first = node;
		}
		//list�� ���� ����Ʈ�� ������ ���-> ��������Ʈ�� ������ ���� ����
		else
		{
			node->link = list->link;
			list->link = node;
		}
	}

}

//���Ḯ��Ʈ�� ���
void printlist(listPointer list) {
	for (; list; list = list->link)
	{
		printf("%2d", list->data);
	}
	printf("\n");
}