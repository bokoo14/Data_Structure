//2020118008 박보경
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct 
{
	char name[20];
	int age;
	float salary;
} humanBeing;

int humansEqual(humanBeing* person1, humanBeing* person2);

int main()
{
	humanBeing a = { 0, 0, 0 };
	humanBeing b = { 0, 0, 0 };

	printf("Input person1's name, age, salary:\n");
	gets(a.name); //공백을 포함한 이름을 입력
	scanf("%d", &a.age);
	scanf("%f", &a.salary);
	printf("  \n");
	getchar();


	printf("Input person2's name, age, salary:\n");
	gets(b.name);//공백을 포함한 이름을 입력
	scanf("%d", &b.age);
	scanf("%f", &b.salary);
	printf("  \n");
	getchar();


	int is_equal;
	is_equal = humansEqual(&a, &b);

	if(is_equal==0)
		printf("The two human beings are not the same");
	else
		printf("The two human beings are the same");


	return 0;
}


int humansEqual(humanBeing* person1, humanBeing* person2)
{
	if (strcmp(person1->name, person2->name))//다르면 0이 아닌 값을 반환
		return FALSE;
	if (person1->age != person2->age)
		return FALSE;
	if (person1->salary != person2->salary)
		return FALSE;
	return TRUE;
}