#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int size);
void fillRand1(int arr[], int size);
void fillRand3(int arr[], int size);
int checkRand1(int arr[], int size);
float meanValue(int arr[], int size);
int maxValue(int arr[], int size);
int meanIndex(int arr[], int size);
int maxIndex(int arr[], int size);
int maxOccurance(int arr[], int size);
int diff(int arr1[], int arr2[], int res[], int size);
void mult(int arr1[], int arr2[], int res[], int size);
int lt(int arr1[], int arr2[], int size);
void lor(int arr1[], int arr2[], int res[], int size);

int main()
{
    int size, status, maxval, indexmean, indexmax, freqval, identity, less;
    puts("==please, enter the size of arrays you want==");
    scanf("%i", &size);
    int arr1[size], arr2[size], arr3[size], arr4[size], resor[size], residentity[size], resmult[size];
    float meanval;

    srand(time(NULL));
    fillRand1(arr1, size);
    fillRand1(arr2, size);
    puts("array_1");
    printArray(arr1, size);
    puts("array_2");
    printArray(arr2, size);
    puts("");
    status = checkRand1(arr1, size);
    if (status=1) puts ("all elements of array_1 lay in range [0...99]");
    else puts ("NOT all elements of array_1 lay in range [0...99]");
    puts("");
    meanval = meanValue(arr1, size);
    printf ("mean value of array_1 is %f \n", meanval);
    puts("");
    maxval = maxValue(arr1, size);
    printf ("maximum value of array_1 is %i \n", maxval);
    puts("");
    indexmean = meanIndex(arr1, size);
    printf ("index of the first closest value to the mean value of array_1 is %i \n", indexmean);
    puts("");
    indexmax = maxIndex(arr1, size);
    printf ("index of the first max value of array_1 is %i \n", indexmax);
    puts("");
    freqval = maxOccurance(arr1, size);
    printf ("the most frequent element of array_1 is %i \n", freqval);
    puts("");
    identity = diff(arr1, arr2, residentity, size);
    if (identity==1) puts("arrays are equal");
    else puts ("arrays are NOT equal");
    puts("");
    mult(arr1, arr2, resmult, size);
    printf ("array_1 multiplied by array_2 = ");
    printArray(resmult, size);
    puts("");
    less = lt(arr1, arr2, size);
    if (less==1) puts ("all elements of array_1 are smaller than relative elemets of array_2");
    else puts ("NOT all elements of array_1 are smaller than relative elemets of array_2");
    puts ("");
    fillRand3(arr3, size);
    puts ("array_3");
    printArray(arr3, size);
    fillRand3(arr4, size);
    puts ("array_4");
    printArray(arr4, size);
    puts("");
    lor(arr3, arr4, resor, size);
    printf("array_3 OR array_4 = ");
    printArray(resor, size);

    return 0;
}


void printArray(int arr[], int size){
    int i;
    printf("{");
    for (i = 0; i < size; i++){
        if (i==(size - 1)){
            printf("%5i ", arr[i]);
        }
        else{
        printf("%5i, ", arr[i]);
        }
    }
    printf("}\n");
}

void fillRand1(int arr[], int size){
    int i;
    for (i = 0; i < size; i++){
        arr[i]= rand() % 99 + 1;
    }
}

void fillRand3(int arr[], int size){
    int i;
    for (i = 0; i < size; i++){
        arr[i]= rand() % 2 + 0;
    }
}

int checkRand1(int arr[], int size){
    int i, status;
    for (i=0; i<size; i++){
        if ((arr[i]<=99)&&(arr[i]>=1)){
            status = 1;
        }
        else {
        status = 0;
        break;
        }
    }
    return status;
}

float meanValue(int arr[], int size){
    int i;
    float result, sum = 0, amount = 0, num;

    for (i=0; i<size; i++){
        amount += 1;
        num = arr[i];
        sum = sum + num;
    }
    result = sum/amount;
    return result;
}

int maxValue(int arr[], int size){
    int i, max;
    for (i = 0; i < size; i++){
        if (i==0){
            max = arr[i];
        }
        else {
        if (arr[i] > max){
            max = arr[i];
                 }
             }
    }
    return max;
}

int meanIndex(int arr[], int size){
    int i, index;
    float meanval, d1, d2, num;

    meanval = meanValue(arr, size);
    for (i = 0; i < size; i++){
        num = arr[i];
        if (i == 0){
            d1 = abs(meanval - num);
            index = i;
        }
        else {
        d2 = abs(meanval - num);
        if (d1>d2) {
        d1 = abs (meanval - num);
        index = i;
        }
        }
        }
    return index;
}

int maxIndex(int arr[], int size){
    int i, max, index;

    for (i = 0; i < size; i++){
        if (i==0){
            max = arr[i];
            index = i;
        }
        else {
        if (arr[i] > max){
            max = arr[i];
            index = i;
                 }
             }
    }
    return index;
}

int maxOccurance(int arr[], int size){
int i, j, f, maxfreq, maxind, freqelement;
int freq[size];
for (i=0; i<size; i++){
        f = 0;
        for (j=0; j<size; j++){
            if (arr[i]==arr[j]){
                f += 1;
            }
        freq[i] = f;
        }
}
for (i=0; i<size; i++){
        if (i==0){
            maxfreq = freq[i];
            maxind = i;
            }
        else {
        if (freq[i] > maxfreq){
            maxfreq = freq[i];
            maxind = i;
            }
                else {
                if ((freq[i] == maxfreq)&&(arr[i]>arr[maxind])){
                        maxfreq = freq[i];
                        maxind = i;
                        }
                    }
        }
        }
freqelement = arr[maxind];
return freqelement;
}

int diff(int arr1[], int arr2[], int res[], int size){
    int i, status=0;
    for (i=0; i<size; i++){
        res[i]=abs(arr1[i]-arr2[i]);
    }
    for (i=0; i<size; i++){
        if (res[i]==0){
            status = 1;
        }
        else {
            status = 0;
            i = size;
        }
    }
    return status;
}

void mult(int arr1[], int arr2[], int res[], int size){
    int i;
    for (i=0; i<size; i++){
        res[i]=arr1[i]*arr2[i];
    }
}

int lt(int arr1[], int arr2[], int size){
    int i, status;
    for (i=0; i<size; i++){
        if (arr1[i]<arr2[i])
        status = 1;
        else
        {
            status = 0;
            i = size;
        }
    }
    return status;
}

void lor(int arr1[], int arr2[], int res[], int size){
    int i;
    for (i = 0; i < size; i++){
        if ((arr1[i]==0)&&(arr2[i]==0))
        res[i]=0;
        else
        res[i]=1;
    }
}





