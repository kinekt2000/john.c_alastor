#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SZ 1000

float bubbleSort(int* nums, int size);
float quickSort(int* nums, int size);
int comp(const void* int1, const void* int2);

int main(){
    int nums1[SZ];
    int nums2[SZ];
    for(size_t i = 0; i < SZ; i++){ scanf("%d", &nums1[i]); nums2[i] = nums1[i];}
    float bubbleTime = bubbleSort(nums1, SZ);
    float quickTime = quickSort(nums2, SZ);
    for(size_t i = 0; i < SZ; i++) printf("%d ", nums1[i]);
    printf("\n%f\n", bubbleTime);
    printf("%f\n", quickTime);
    return 0;
}


float bubbleSort(int* nums, int size){
    clock_t start = clock();

    for(int i = size - 1; i >= 0; i--)
        for(int j = 0; j < i; j++)
            if (nums[j] > nums[j+1]){
                int t = nums[j+1];
                nums[j+1] = nums[j];
                nums[j] = t;
            }

    clock_t end = clock();
    return (float)(end - start) / CLOCKS_PER_SEC;
}

float quickSort(int *nums, int size){
    clock_t start = clock();

    qsort(nums, size, sizeof(int), comp);

    clock_t end = clock();
    return (float)(end - start) / CLOCKS_PER_SEC;
}

int comp(const void* int1,const void* int2){
    return *(int*)int1 - *(int*)int2;
}















