//"selection.h"에는 SWAP 매크로 정의문, sort 함수원형을 작성

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void sort(int list[], int n);
