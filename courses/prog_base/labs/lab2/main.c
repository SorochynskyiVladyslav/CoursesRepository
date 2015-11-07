#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr1[6] = {16, 26, 26, 8, 206, 8};
	int arr2[6] = {-7, -7, -7, -7, -7, -7};
	int a = 6, b = 6;
	int c = run(arr1, a, arr2, b);
	for (a = 0; a < b; a++)
		printf(" %d ", arr2[a]);
	printf("\n %d ", c);
    return 0;
}
