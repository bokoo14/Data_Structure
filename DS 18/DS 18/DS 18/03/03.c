//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ� 

/* 18(3) connected component��� => dfs
*  �Էµ� "������׷���"�� connected component�� ����ϴ� ���α׷��� �ۼ�
* "������ �׷���" "dfs -> �����尡 ����Ű�� ù ��� ����"
* 
* !!!!!!!!!!!���� �׷���, ������ ���� �����Ϸ��� ds17����!!!!!!!!!!!!!
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
* �� ����� �׷����� ���
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
#define MAX_QUEUES 10
short int visited[MAX_VERTICES];


//���Ḯ��Ʈ
typedef struct qNode* queuePointer;
typedef struct qNode {
	int vertex;
	queuePointer link;
}tQNode;
queuePointer* graph;
queuePointer front, rear;


//adjacency list
void insert(queuePointer* first, queuePointer list, int data);
void printlist(queuePointer list);


//dfs 
void dfs(int v);

//connect
void connected(int n);



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


	//vertex��, edge���� ����(ù ���� �о��)
	int vertex, edge;
	fscanf(fp, "%d %d", &vertex, &edge);


	//���� ����Ʈ�� vertex����ŭ ����
	MALLOC(graph, sizeof(*graph) * vertex);
	for (int i = 0; i < vertex; i++)
	{
		graph[i] = NULL;
	}


	//������ �׷��� ����
	int v1, v2;
	while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
	{
		insert(&graph[v1], NULL, v2);
		insert(&graph[v2], NULL, v1);
	}


	//���� ����Ʈ ���
	printf("<<<<<Adjacency List>>>>>\n");
	for (int i = 0; i < vertex; i++)
	{
		printf("graph[%d]: ", i);
		printlist(graph[i]);
	}
	printf("\n\n");

	//����� �׷��� ���
	printf("<<<<<Connected Componets>>>>> \n");
	connected(vertex);

	return 0;
}

//���� ����Ʈ �����
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
		//list�� ���� ����ִٸ�
		if (list == NULL)
		{
			node->link = *first;
			*first = node;
		}
		//list�� ���� ������� �ʴٸ�
		else
		{
			node->link = list->link;
			list->link = node;
		}
	}

}
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

	visited[v] = TRUE;
	printf("%2d", v);

	for (w = graph[v]; w; w = w->link)
	{
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}

//connected -> dfs�� �ϸ鼭 ����� �׷������� node���� ��� ���
//�̹� �湮�� node���� �ٽ� dfs������ 
void connected(int n) {
	int i;
	int cnt = 1;
	for (i = 0; i < n; i++)
	{
		//�湮���� �ʾ�����
		if (!visited[i])
		{
			printf("connected component %d: ", cnt);
			dfs(i);
			printf("\n");
			cnt++;
		}
	}
}