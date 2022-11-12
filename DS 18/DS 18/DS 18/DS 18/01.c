//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 18(1) "무방향그래프" -> dfs
* 다음과 같이 무방향그래프(undirected graph) 데이터를 입력받아 인접리스트를 만들고 dfs 결과를 출력
* 인접리스트의 헤더노드가 가리키는 "첫 노드"에 삽입
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
*  ③ dfs의 결과 출력
* ※ Program 6.1의 재귀함수호출을 이용함. 시스템 스택의 사용
* ※ dfs(0), dfs(1), ..., dfs(n)를 각각 출력함 
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

//인접 리스트
typedef struct qNode* queuePointer;
typedef struct qNode {
	int vertex;
	queuePointer link;
}tQNode;
queuePointer* graph; 


//ajacency list
void insert(queuePointer* first, queuePointer list, int data); //인접리스트만들기
void printlist(queuePointer list); //인접리스트출력


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
	//vertex수, edge수를 받음(첫 줄을 읽어옴)
	fscanf(fp, "%d %d", &vertex, &edge);

	//인접 리스트를 vertex수만큼 생성
	MALLOC(graph, sizeof(*graph) * vertex);
	for (int i = 0; i < vertex; i++)
	{
		graph[i] = NULL;
	}

	/*
	* 파일의 두번째 줄부터 파일이 끝날때 까지 읽음
	* "무방항 그래프", "헤더 노드가 가리키는 첫번째 노드" 삽입
	* 
	* 방향 그래프로 바꾸려면 ds17참고!
	* 마지막 노드에 삽입으로 바꾸려면 ds17참고!
	*/
	int v1, v2;
	while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
	{
		insert(&graph[v1], NULL, v2);
		insert(&graph[v2], NULL, v1);
	}
	
	//인접리스트를 출력
	printf("<<<<<Adjacency List>>>>>\n");
	for (int i = 0; i < vertex; i++)
	{
		printf("graph[%d]: ", i);
		printlist(graph[i]);
	}
	printf("\n\n");
	
	//dfs를 실행 (시작 노드: 0~vertex-1까지 차례대로 dfs해줌)
	printf("<<<<<Depth First Search>>>>> \n");
	for (int i = 0; i < vertex; i++)
	{
		
		printf("dfs<%d>: ", i);
		dfs(i);
		printf("\n");

		//방문한 값 초기화
		for (int j = 0; j < 100; j++)
		{
			visited[j] = FALSE;
		}
	
	}
	fclose(fp);

	return 0;
}

//인접 리스트 만들기 (항상 헤더 다음인 처음 노드로 입력되게 함)
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
		//list의 값이 비어있다면(인접리스트의 헤더 노드가 가리키는 첫 노드에 삽입)
		if (list == NULL)
		{
			node->link = *first;
			*first = node;
		}
		//list의 값이 비어있지 않다면(인접리스트의 마지막 노드에 삽입)
		else
		{
			node->link = list->link;
			list->link = node;
		}
	}
}

//인접리스트 출력 -> 하나의 연결리스트 하나 처음부터 끝까지 출력
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

	//방문
	visited[v] = TRUE;
	printf("%2d", v);

	//재귀함수호출을 이용함 시스템 스택을 사용
	for (w = graph[v]; w; w = w->link)
	{
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}
