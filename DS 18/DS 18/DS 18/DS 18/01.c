//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 18(1) "������׷���" -> dfs
* ������ ���� ������׷���(undirected graph) �����͸� �Է¹޾� ��������Ʈ�� ����� dfs ����� ���
* ��������Ʈ�� �����尡 ����Ű�� "ù ���"�� ����
* 
* �� �Է������� ù ���� ����(vertex) ���� ����(edge)�� ���� ��Ÿ��
* �� �׷����� ���� �ε����� 0���� ���۵�
* �� ����: ���Ϸκ��� ������ ��������Ʈ�� ��� ������ �׸�(graph)�� ���������� ����
* 
* (2) �������
* �� ����(vertex)�� ����(edge)�� ���� �Է¹���
* �� �׷����� �����ϴ� ������ �ϳ��� �Է¹����鼭 ��������Ʈ�� ������
* �� ���� ������ �� �� �Էµ��� ������ ������
* �� �׻� ��� ������ ó�� ���� �Էµǰ� ��
*  �� dfs�� ��� ���
* �� Program 6.1�� ����Լ�ȣ���� �̿���. �ý��� ������ ���
* �� dfs(0), dfs(1), ..., dfs(n)�� ���� ����� 
*/


#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
	if( !( (p) = malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100
short int visited[MAX_VERTICES];

//���� ����Ʈ
typedef struct qNode* queuePointer;
typedef struct qNode {
	int vertex;
	queuePointer link;
}tQNode;
queuePointer* graph; 


//ajacency list
void insert(queuePointer* first, queuePointer list, int data); //��������Ʈ�����
void printlist(queuePointer list); //��������Ʈ���


//dfs 
void dfs(int v);


#include<stdio.h>
#include <stdlib.h>
int main()
{
	FILE* fp = fopen("input.txt", "r");

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open file");
		exit(EXIT_FAILURE);
	}


	int vertex, edge;
	//vertex��, edge���� ����(ù ���� �о��)
	fscanf(fp, "%d %d", &vertex, &edge);

	//���� ����Ʈ�� vertex����ŭ ����
	MALLOC(graph, sizeof(*graph) * vertex);
	for (int i = 0; i < vertex; i++)
	{
		graph[i] = NULL;
	}

	/*
	* ������ �ι�° �ٺ��� ������ ������ ���� ����
	* "������ �׷���", "��� ��尡 ����Ű�� ù��° ���" ����
	* 
	* ���� �׷����� �ٲٷ��� ds17����!
	* ������ ��忡 �������� �ٲٷ��� ds17����!
	*/
	int v1, v2;
	while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
	{
		insert(&graph[v1], NULL, v2);
		insert(&graph[v2], NULL, v1);
	}
	
	//��������Ʈ�� ���
	printf("<<<<<Adjacency List>>>>>\n");
	for (int i = 0; i < vertex; i++)
	{
		printf("graph[%d]: ", i);
		printlist(graph[i]);
	}
	printf("\n\n");
	
	//dfs�� ���� (���� ���: 0~vertex-1���� ���ʴ�� dfs����)
	printf("<<<<<Depth First Search>>>>> \n");
	for (int i = 0; i < vertex; i++)
	{
		
		printf("dfs<%d>: ", i);
		dfs(i);
		printf("\n");

		//�湮�� �� �ʱ�ȭ
		for (int j = 0; j < 100; j++)
		{
			visited[j] = FALSE;
		}
	
	}
	fclose(fp);

	return 0;
}

//���� ����Ʈ ����� (�׻� ��� ������ ó�� ���� �Էµǰ� ��)
void insert(queuePointer* first, queuePointer list, int data) {
	queuePointer node;
	MALLOC(node, sizeof(*node));

	node->vertex = data;

	if (*first == NULL)
	{
		node->link = NULL;
		*first = node;
	}
	else
	{
		//list�� ���� ����ִٸ�(��������Ʈ�� ��� ��尡 ����Ű�� ù ��忡 ����)
		if (list == NULL)
		{
			node->link = *first;
			*first = node;
		}
		//list�� ���� ������� �ʴٸ�(��������Ʈ�� ������ ��忡 ����)
		else
		{
			node->link = list->link;
			list->link = node;
		}
	}
}

//��������Ʈ ��� -> �ϳ��� ���Ḯ��Ʈ �ϳ� ó������ ������ ���
void printlist(queuePointer list) {
	for (; list; list = list->link)
	{
		printf("%2d", list->vertex);
	}
	printf("\n");
}


//dfs 
void dfs(int v) {
	queuePointer w;

	//�湮
	visited[v] = TRUE;
	printf("%2d", v);

	//����Լ�ȣ���� �̿��� �ý��� ������ ���
	for (w = graph[v]; w; w = w->link)
	{
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}