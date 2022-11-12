//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다 

/* 18(3) connected component출력 => dfs
*  입력된 "무방향그래프"의 connected component를 출력하는 프로그램을 작성
* "무방향 그래프" "dfs -> 헤더노드가 가리키는 첫 노드 삽입"
* 
* !!!!!!!!!!!방향 그래프, 마지막 노드로 삽입하려면 ds17참고!!!!!!!!!!!!!
* 
* ※ 입력파일의 첫 줄은 정점(vertex) 수와 간선(edge)의 수를 나타냄
* ※ 그래프의 정점 인덱스는 0부터 시작됨
* ※ 주의: 파일로부터 구성된 인접리스트의 노드 순서가 그림(graph)과 동일하지는 않음
* 
* (2) 실행순서
* ① 정점(vertex)과 간선(edge)의 수를 입력받음
* ② 그래프를 구성하는 간선을 하나씩 입력받으면서 인접리스트를 구성함
* ※ 같은 간선이 두 번 입력되지 않음을 가정함
* ※ 항상 헤더 다음인 처음 노드로 입력되게 함
* ③ 연결된 그래프를 출력
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


//연결리스트
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


	//vertex수, edge수를 받음(첫 줄을 읽어옴)
	int vertex, edge;
	fscanf(fp, "%d %d", &vertex, &edge);


	//인접 리스트를 vertex수만큼 생성
	MALLOC(graph, sizeof(*graph) * vertex);
	for (int i = 0; i < vertex; i++)
	{
		graph[i] = NULL;
	}


	//무방항 그래프 삽입
	int v1, v2;
	while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
	{
		insert(&graph[v1], NULL, v2);
		insert(&graph[v2], NULL, v1);
	}


	//인접 리스트 출력
	printf("<<<<<Adjacency List>>>>>\n");
	for (int i = 0; i < vertex; i++)
	{
		printf("graph[%d]: ", i);
		printlist(graph[i]);
	}
	printf("\n\n");

	//연결된 그래프 출력
	printf("<<<<<Connected Componets>>>>> \n");
	connected(vertex);

	return 0;
}

//인접 리스트 만들기
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
		//list의 값이 비어있다면
		if (list == NULL)
		{
			node->link = *first;
			*first = node;
		}
		//list의 값이 비어있지 않다면
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

//connected -> dfs를 하면서 연결된 그래프들의 node들은 모두 출력
//이미 방문된 node들은 다시 dfs안해줌 
void connected(int n) {
	int i;
	int cnt = 1;
	for (i = 0; i < n; i++)
	{
		//방문하지 않았으면
		if (!visited[i])
		{
			printf("connected component %d: ", cnt);
			dfs(i);
			printf("\n");
			cnt++;
		}
	}
}
