//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�

/* 18(2) "������ �׷���" -> bfs
* ������ ���� ������׷���(undirected graph) �����͸� �Է¹޾� ��������Ʈ�� ����� bfs ����� ���
* "�����尡 ����Ű�� ù ���� ����"
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
* �� �׻� ��� ������ "ó�� ���"�� �Էµǰ� �� 
* �� dfs�� ��� ���
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
#define MAX_QUEUES 10
#define MAX_VERTICES 100
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

//queue
void addq(int item);
int deleteq();

//bfs 
void bfs(int v);


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

	//"������ �׷���" "ù ���" ����
	int v1, v2;
	while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
	{
		insert(&graph[v1], NULL, v2);
		insert(&graph[v2], NULL, v1);
	}


	//������ ��������Ʈ ���
	printf("<<<<<Adjacency List>>>>>\n");
	for (int i = 0; i < vertex; i++)
	{
		printf("graph[%d]: ", i);
		printlist(graph[i]);
	}
	printf("\n\n");


	//bfs����, ���
	printf("<<<<<Breath First Search>>>> > \n");
	for (int i = 0; i < vertex; i++)
	{
		printf("bfs<%d>: ", i);
		bfs(i);
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
		//list�� ���� ����ִٸ�(��������Ʈ�� �����尡 ����Ű�� ù ��忡 ����)
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

//��������Ʈ ���
void printlist(queuePointer list) {
	for (; list; list = list->link)
	{
		printf("%2d", list->vertex);
	}
	printf("\n");
}


//���� queue
void addq(int item) {
	queuePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->vertex = item;
	temp->link = NULL;

	//ť�� ������� ������ rear�� link�� ����Ű�� ���� temp�� ����
	if (front)
		rear->link = temp;
	//ť�� ��������� front�� temp�� ����
	else
		front = temp;

	//rear�� ����Ű�� ���� temp
	rear = temp;
}

int deleteq() {

	//front�� ���� temp�� ����
	queuePointer temp = front;
	int item;

	//temp�� ��������� -1�� ��ȯ
	if (!temp)
		return -1;

	item = temp->vertex;

	//front�� �� ��ĭ �ű��
	front = temp->link;

	free(temp);
	return item;
}


void bfs(int v)
{
	queuePointer w;
	front = rear = NULL;

	//�湮
	printf("%2d", v);
	visited[v] = TRUE;
	addq(v); //�湮�� ������ ť�� ����

	//front�� ������ ť�� ������� ����
	while (front)
	{
		v = deleteq(); //ť���� �ϳ��� ����
		//�� ���� ���� ����� �湮���� �ʾҴ� ��带 ť�� �־���
		for (w = graph[v]; w; w=w->link)
		{
			//�湮���� �ʾ����� �湮����
			if (!visited[w->vertex]) {
				printf("%2d", w->vertex);
				addq(w->vertex);
				visited[w->vertex] = TRUE;
			}
		}
	}
}