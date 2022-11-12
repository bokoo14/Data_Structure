//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
//06-1

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i, * pi;
	float f, * pf;
	pi = (int*)malloc(sizeof(int));
	pf = (float*)malloc(sizeof(float));

	//역참조 연산으로 값을 대입
	*pi = 1024;
	*pf = 3.14;

	//역참조 연산으로 값을 참조하기
	printf("an integer = %d, a float %f \n", *pi, *pf);

	free(pi);
	free(pf);


	i = 1;
	f = 1.12;
	printf("i: %d  f: %f", i, f);

	/*
	if ((pi = (int*)malloc(sizeof(int))) == NULL || (pf = (float*)malloc(sizeof(float))) == NULL)
	{
		fprintf(stderr, "Insuffient memory");
		exit(EXIT_FAILURE);
	}
	*/
	if (!(pi = malloc(sizeof(int))) || !(pf = malloc(sizeof(float))))
	{
		fprintf(stderr, "Inefficient memory!");
		exit(EXIT_FAILURE);
	}

	return 0;

}

