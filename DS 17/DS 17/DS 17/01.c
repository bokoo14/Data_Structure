//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 17(1) Graph: Adjacency List "인접리스트"
*  파일 입력을 통해 무방향 그래프(undirected graph)나 방향 그래프(directed graph)를 인접리스트(adjacency-list)로 구성하는 프로그램
* 
* 인접리스트의 "헤더노드가 가리키는 첫노드"로 삽입
* 
* 실행순서
* ① 그래프 종류, 정점, 간선의 수를 입력받음
* ② 그래프 종류에 따라 간선을 하나씩 입력받으면서 인접리스트를 구성함
* ※ 항상 헤더노드가 가리키는 첫 노드로 입력되게 함
* ③ 각 정점에 대해 부속된 간선(edges incident to a vertex v)을 출력하기
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


	char ud; //u혹은 d를 파일로부터 받음
	int vertex, edge;
	//u, d vertex수, edge수를 받음(첫 줄을 읽어옴)
	fscanf(fp, "%c %d %d", &ud, &vertex, &edge);

	//인접 리스트를 vertex수만큼 생성
	MALLOC(adjLists, sizeof(*adjLists)*vertex);
	for (int i = 0; i < vertex; i++)
	{
		adjLists[i] = NULL;
	}

	int v1, v2;
	//무방항 그래프일때
	if (ud=='u')
	{
		while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
		{
			insert(&adjLists[v1], NULL, v2);
			insert(&adjLists[v2], NULL, v1);
		}
	}
	//방향 그래프일때
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

//인접 리스트 만들기
void insert(listPointer* first, listPointer list, int data) {
	listPointer node;
	MALLOC(node, sizeof(*node));

	node->data = data;

	//adjLists[]가 가리키는 것이 없을때
	if (*first == NULL)
	{
		node->link = NULL;
		*first = node;
	}
	else 
	{
		//list의 값이 NULL이라면-> 인접리스트의 첫 노드로 삽입
		if (list == NULL)
		{
			node->link = *first;
			*first = node;
		}
		//list의 값이 리스트의 마지막 노드-> 인접리스트의 마지막 노드로 삽입
		else
		{
			node->link = list->link;
			list->link = node;
		}
	}

}

//연결리스트를 출력
void printlist(listPointer list) {
	for (; list; list = list->link)
	{
		printf("%2d", list->data);
	}
	printf("\n");
}