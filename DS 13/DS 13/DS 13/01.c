//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/*
* 13. Trees: 이진트리 생성 및 순회(1)
* 이진트리를 생성하고 이진트리 순회방법 중 중위순회, 전위순회, 후위순회를 통해 출력하는 프로그램 작성
* 
* [실행순서]
* 1) 이진트리 생성 (개별적으로 노드를 생성한 후, 그림과 같은 형태의 이진트리가 되게 링크를 연결한다)
* 2) 이진트리 중위순회를 통해 데이터 출력
* 3) 이진트리 전위순회를 통해 데이터 출력
* 4) 이진트리 후위순회를 통해 데이터 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }

#include<stdio.h>
#include<stdlib.h>

//이진 트리 노드 생성
typedef struct node* treePointer;
typedef struct node {
	char data; //문자출력을 위해 char형으로 지정
	treePointer leftChild, rightChild;
}node;

treePointer root;

//binary tree
treePointer createNode(char data); //노드 생성 함수이므로 링크 필드는 NULL로 지정
treePointer createBinTree(); //이진트리 생성 함수

//binary tree traversals
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);



int main()
{
	treePointer tree = NULL;
	
	printf("creating a binary tree\n \n");
	tree=createBinTree();

	printf("three binary tree traversals\n");
	printf("inorder traversal    : ");
	inorder(tree);
	printf("\n");

	printf("preorder traversal   : ");
	preorder(tree);
	printf("\n");

	printf("postorder traversal  : ");
	postorder(tree);
	printf("\n");

	return 0;
}

//binary tree
//노드 생성 함수, 링크 필드는 NULL로 지정
treePointer createNode(char data) {

	treePointer p = NULL;
	MALLOC(p, sizeof(*p));

	p->data = data;
	p->leftChild = NULL; //링크 필드 NULL로 지정
	p->rightChild = NULL; //링크 필드 NULL로 지정

	return p;
}

/*
* 이진트리 생성
* 개별적으로 노드를 생성한 후, 그림과 같은 형태의 이진트리가 되게 링크를 연결한다
*/
treePointer createBinTree() {
	
	treePointer A = createNode('A');
	treePointer B = createNode('B');
	treePointer C = createNode('C');
	treePointer D = createNode('D');
	treePointer E = createNode('E');

	A->leftChild = B;
	A->rightChild = C;

	B->leftChild = D;
	B->rightChild = E;

	//루트노드를 return
	return A;
}

//binary tree traversals
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
