//2020118008 �ں���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

//�����Ҵ� �迭�� �̿��� �̷�Ž�� 
//maze search function�� ����ϴ� �̷� Ž�� ���α׷�

#define _CRT_SECURE_NO_WARNINGS
#define FALSE 0
#define TRUE 1
#define MAX_STACK_SIZE 100

#include<stdio.h>
#include<stdlib.h>

//���� 
typedef struct
{
	short int row; //��
	short int col; //��
	short int dir; //�̵� ����
}element;
element stack[MAX_STACK_SIZE];

//�̷� �̵� ����
typedef struct
{
	short int vert; //����
	short int horiz; //�¿�
}offsets;

//�̷ο��� �̵� ����
offsets move[8] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };

int top = -1; //������ ��������� top�� -1
int EXIT_ROW, EXIT_COL; //��, ��
int maze[10][10], mark[10][10]; //�̷�, �湮�� ���� mark

void path();
void stackFull();
element stackEmpty();
void push(element item);
element pop();


int main()
{
	//���� ����
	FILE* fp = fopen("input.txt", "r");

	//ù ���� �̷��� ��� ���� ũ��
	fscanf(fp, "%d %d", &EXIT_ROW, &EXIT_COL);

	//EXIT_ROW, EXIT_COL�� ����ŭ ���Ͽ��� �Է¹ޱ�
	for(int i=0; i<EXIT_ROW; i++)
		for (int j = 0; j < EXIT_COL; j++)
		{
			fscanf(fp, "%d", &maze[i + 1][j + 1]);
		}

	//�̷��� �����ڸ��� ��� 1�� �������
	for (int k = 0; k < EXIT_COL+2; k++)
		maze[0][k] = 1;

	for (int k = 0; k < EXIT_COL+2; k++)
		maze[EXIT_ROW+1][k] = 1;

	for (int k = 0; k < EXIT_ROW+2; k++)
		maze[k][0] = 1;

	for (int k = 0; k < EXIT_ROW+2; k++)
		maze[k][EXIT_COL+1] = 1;
	
	path();

	return 0;
}


void path()
{
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	//�̷��� entrance�� ����(1�� 1��)
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;

	//������ ���� �ʾҰ� found=FALSE�϶� 
	while (top > -1 && !found)
	{
		position = pop();
		row = position.row; col = position.col;
		dir = position.dir;
		while (dir < 8 && !found)
		{
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			//���Ա��� ã������ found=TRUE�� �ٲپ���
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
			{
				found = TRUE;
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
			{
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else
			{
				++dir;
			}
		}
	}
	//found=TRUE�̸� (���Ա��� ã������)
	if (found)
	{
		printf("The Path is:\n");
		printf("row col\n");
		for (i = 0; i <= top; i++)
		{
			printf("%2d%2d", stack[i].row, stack[i].col);
			printf("\n");
		}
		printf("%2d%2d\n", row, col);
		printf("%2d%2d\n", EXIT_ROW, EXIT_COL);
	}
	//���Ա��� ã�� �������� 
	else
	{
		printf("The maze does not have a path\n");
	}
}


//----------------����--------------------
//������ ���� á����
void stackFull()
{
	fprintf(stderr, "Stack is full, cannot add element\n");
	printf("current stack elements :\n");
	exit(EXIT_FAILURE);
}

//������ �������
element stackEmpty()
{
	fprintf(stderr, "Stack is empty, add element\n");
	exit(EXIT_FAILURE);
}

//���ÿ��� push
void push(element item)
{
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}

//���ÿ��� pop
element pop()
{
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}
//----------------����--------------------