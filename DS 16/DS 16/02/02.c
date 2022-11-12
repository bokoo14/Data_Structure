//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다

/* 16(2) 이진탐색트리
* 2. 다음과 같이 임의의 노드 n개로 구성된 이진탐색트리(binary search tree)를 생성하는 프로그램
* 
* (1) 실행순서
* ① 난수생성을 위한 seed와 이진탐색트리의 노드 개수(n)를 입력받음  ※ scanf
* ② 1~500 범위의 난수를 생성하여 노드의 key와 item 필드 값으로 동일하게 사용
* ※ 이진탐색트리의 key 값은 중복이 허용되지 않음을 주의
* ③ ②의 key, item을 사용하여 이진탐색트리에 노드를 하나 추가함 
* ※ Program 5.17. insert
* ※ Program 5.17에서 사용된 modifiedSearch함수는 Program 5.16을 수정함
* ④ ②~③ 과정을 n번 수행하여 이진탐색트리를 구성 ※ 난수발생 순서대로 노드를 추가해야 함
* ⑤ 탐색할 key를 입력받아서 이진탐색하여 그 결과를 출력한다. ※ Program 5.15 혹은 5.16
* ⑥ 이진탐색트리를 구성하고 있는 노드의 key값을 오름차순으로 정렬되도록 출력함
* ※ inorder traversal 사용
*/
#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) \
	if( !( (p) =malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define MAX_SIZE 500

typedef int iType;
typedef struct {
	int key;
	iType item;
}element;
typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
}node;
treePointer tree;

//recursion search of a binary search tree
element* search(treePointer root, int k);
//iterative search of a binary tree
element* iterSearch(treePointer tree, int k);
//inserting a dictionary pair into a binary search tree
void insert(treePointer* node, int k, iType theItem);

//program 5.16 iterSearch 수정
treePointer modifiedSearch(treePointer node, int k);

//중위 순회
void inorder(treePointer ptr);

#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n;
	int seed;
	int searchnum;
	printf("random number generation <1~500>\n");
	printf("the number of nodes in BST <less than and equal to 50> : ");
	scanf("%d", &n);
	printf("seed: ");
	scanf("%d", &seed);
	printf("\n");

	printf("creating a BST from random numbers \n");
	srand(seed);


	int cnt=0;
	int numbers[MAX_SIZE + 1] = { 0 };
	int key;
	while (cnt < n)
	{
		key = 1 + rand() % MAX_SIZE;
		if (!numbers[key]) // unique random number
		{
			numbers[key] ++;
			printf("%4d", key);
			insert(&tree, key, (iType)key);
			cnt++;
		}
	}
	printf("\n");


	printf("the key to search :");
	scanf("%d", &searchnum);
	element* ptr = search(tree, searchnum);
	if (search(tree, searchnum)) {
		printf("the element's item is %d\n",ptr->item); 
	}
	else {
		printf("there is no such an element \n\n");
	}
	printf("\n\n");


	printf("inorder traversal of the BST shows the sorted sequence\n");
	inorder(tree);

	return 0;
}


//recursion search of a binary search tree
element* search(treePointer root, int k) {
	if (!root) return NULL;
	if (k == root->data.key) return &(root->data);
	if (k < root->data.key) return search(root->leftChild, k);
	return  search(root->rightChild, k);
}


//iterative search of a binary tree
element* iterSearch(treePointer tree, int k) {
	while (tree)
	{
		if (k == tree->data.key) return &(tree->data);
		if (k < tree->data.key)
			tree = tree->leftChild;
		else
			tree = tree->rightChild;
	}
	return NULL;
}


//inserting a dictionary pair into a binary search tree
void insert(treePointer* node, int k, iType theItem)
{ 
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node))
	{
		
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*node)
		{
			if (k < temp->data.key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else
		{
			*node = ptr;
		}
	}
}

//program 5.16 iterSearch 수정 => 이진탐색트리 생성
treePointer modifiedSearch(treePointer node, int k){
	treePointer temp = NULL;
	if (!node) return NULL;
	while (node)
	{
		temp = node;
		if (k == node->data.key) return NULL;
		if (k < node->data.key)
			node = node->leftChild;
		else 
			node = node->rightChild;
	}
	return temp;
}

//중위 순회
//오름차순 출력
void inorder(treePointer ptr) {
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%4d", ptr->data.key);
		inorder(ptr->rightChild);
	}
}

