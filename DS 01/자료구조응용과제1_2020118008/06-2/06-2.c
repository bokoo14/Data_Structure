//2020118008박보경 
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
//06-2
#include <stdio.h>
#include <stdlib.h>

//매크로를 이용한 동적 메모리 할당
#define MALLOC(p,s) if(!((p)=malloc(s))) { fprintf(stderr, "Insuffient memory"); exit(EXIT_FAILURE); }

int main(void)
{
	int i, *pi;
	float f, *pf;

	//매크로를 이용한 동적 메모리 할당
	MALLOC(pi, sizeof(int*));
	MALLOC(pf, sizeof(float*));

	*pi = 1024;
	*pf = 3.14;
	printf("an integer = %d, a float %f \n", *pi, *pf);
	free(pi);
	free(pf);


	i = 1;
	f = 1.12;
	printf("i: %d  f: %f", i, f);

	return 0;

}