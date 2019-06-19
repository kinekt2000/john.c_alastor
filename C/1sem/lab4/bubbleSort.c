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
