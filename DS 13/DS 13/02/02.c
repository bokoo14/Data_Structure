//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 
* 13(2) ["큐"를 이용한 "완전이진트리 생성"]
* 파일입력을 받아 다음과 같은 완전이진트리를 구성하여, 중위순회, 전위순회, 후위순회를 통해 출력하는 프로그램
* 
* [실행순서]
* ① 입력파일(input.txt)로부터 다음과 같은 완전이진트리를 생성한다.
* ② 이진트리 중위순회를 통해 데이터를 출력한다. ※ inorder(root);
* ③ 이진트리 전위순회를 통해 데이터를 출력한다. ※ preorder(root);
* ④ 이진트리 후위순회를 통해 데이터를 출력한다. ※ postorder(root);
*/

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }
#define MAX_QUEUE_SIZE 100

#include<stdio.h>
#include <string.h>
#include<stdlib.h>

//트리 노드 정의 및 큐 선언
typedef struct node* treePointer;
typedef struct node {
	char data; //문자출력을 위해 char형으로 지정
	treePointer leftChild, rightChild;
}node;

treePointer root = NULL;
treePointer queue[MAX_QUEUE_SIZE];

//queue
int rear = -1;
int front = -1;

treePointer queueEmpty();
void queueFull();
void deleteq();
void addq(treePointer item);
treePointer getFront();


//binary tree
treePointer createNode(char data); //노드 생성 함수이므로 링크 필드는 NULL로 지정
treePointer createCompBinTree(FILE *fp);

//pRoot가 가리키는 완전이진트리에 pNode가 가리키는 새 노드를 추가한다
void insert(treePointer pNode);


//binary tree traversals
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);



int main()
{
	FILE* fp=fopen("input.txt","r");

	printf("creating a complete binary tree\n \n");
	root=createCompBinTree(fp);

	printf("three binary tree traversals\n");
	printf("inorder traversal        : ");
	inorder(root);
	printf("\n");

	printf("preorder traversal       : ");
	preorder(root);
	printf("\n");

	printf("postorder traversal      : ");
	postorder(root);
	printf("\n");

	return 0;
}


//------------------------큐-------------------------
//선형 큐가 비었을때
//간단한 메시지를 출력하고 NULL 포인터를 반환되도록 함
treePointer queueEmpty()
{
	fprintf(stderr, "queue is empty, cannot delete element.\n");
	return NULL;
}

//선형 큐가 가득 찼을때 간단한 메시지를 출력하고 프로그램을 종료함
//array shift를 구현하지 않음
void queueFull()
{
	printf(stderr, "queue is empty, cannot delete element.\n");
	exit(EXIT_FAILURE);
}

//선형큐에 enqueue()
void addq(treePointer item)
{
	//선형 큐에서 rear의 값이 queue의 마지막 index를 가리키면 가득차있음
	if (rear == MAX_QUEUE_SIZE - 1)
		queueFull();
	queue[++rear] = item;
}

//선형큐에 dequeue()
void deleteq()
{
	//선형 큐는 front와 rear의 값이 같으면 비어있음
	if (front == rear)
		queueEmpty();
	queue[++front];

}

//큐의 가장 선두항목 값을 반환하는 함수, 큐의 항목을 삭제하지 않음
treePointer getFront() {
	return queue[front+1];
}
//------------------------큐-------------------------


//--------------binary tree --------------
//노드 생성 함수, 링크 필드는 NULL로 지정
treePointer createNode(char data) {

	treePointer p = NULL;
	MALLOC(p, sizeof(*p));

	p->data = data;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}

//이진트리 생성
treePointer createCompBinTree(FILE *fp){
	char data;
	treePointer newNode;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	//data를 입력받을 때 마다 노드를 생성하여 insert 수행
	while (fscanf(fp, "%c", &data) != EOF) //end of file이 될때까지
	{
		newNode = createNode(data);
		insert(newNode);
	}
	
	return root;

}

//pRoot가 가리키는 완전이진트리에 pNode가 가리키는 새 노드를 추가
void insert(treePointer pNode)
{
	treePointer frontnode;

	if (!root) //if tree is empty
	{
		root = pNode; //initialize the root with the new node 
	}
	else //if tree is not empty
	{
		frontnode = getFront(); //get the front node of the queue
		if (!(frontnode->leftChild)) //if the left child of this front node doesn't exist
		{
			frontnode->leftChild = pNode; //set the left child as the new node
		}
		else if (!(frontnode->rightChild)) //if the right child of this front node doesn't exist
		{
			frontnode->rightChild = pNode; //set the right child as the new node
		}

		if ((frontnode->leftChild) && (frontnode->rightChild)) //if the front node has both children
		{
			deleteq();
		}
	}
	addq(pNode); //add the new node
}
//--------------binary tree--------------


//--------------binary tree traversals--------------
//중위순회
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}

}

//전위순회
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

//후위순회
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}
//--------------binary tree traversals--------------
