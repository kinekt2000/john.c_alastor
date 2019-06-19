#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SZ 1000

float bubbleSort(int* nums, int size);
float quickSort(int* nums, int first, int last);

int main(){
    int nums1[SZ];
    int nums2[SZ];
    for(size_t i = 0; i < SZ; i++){ scanf("%d", &nums1[i]); nums2[i] = nums1[i];}
    float bubbleTime = bubbleSort(nums1, SZ);
    float quickTime = quickSort(nums2, 0, SZ-1);
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

float quickSort(int *nums, int first, int last){
    clock_t start = clock();

    if (first < last){
        int left = first, right = last, middle = nums[(left + right) / 2];
        do{
            while (nums[left] < middle) left++;
            while (nums[right] > middle) right--;
            if (left <= right){
                int t = nums[left];
                nums[left] = nums[right];
                nums[right] = t;
                left++;
                right--;
            }
        } while (left <= right);
        quickSort(nums, first, right);
        quickSort(nums, left, last);
    }

    clock_t end = clock();
    return (float)(end - start) / CLOCKS_PER_SEC;
}














