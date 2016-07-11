#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr1[6] = {8, 206, 16, 8, 206, 8};
	int arr2[6] = {-7, -7, -7, -7, -7, -7};
	int a = 6, b = 6, i;

    printf("{");
    for (i = 0; i < a;i++){
        if (i==(a - 1)){
            printf("%5i ", arr1[i]);
        }
        else{
        printf("%5i, ", arr1[i]);
        }
    }
    printf("}\n");

	int c = run(arr1, a, arr2, b);
	printf (" result arr = ");
	for (a = 0; a < b; a++){
		printf(" %d ", arr2[a]);
	}
	printf("\n result =  %d ", c);
    return 0;
}
